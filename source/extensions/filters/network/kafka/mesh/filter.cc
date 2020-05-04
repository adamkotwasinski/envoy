#include "extensions/filters/network/kafka/mesh/filter.h"
#include "extensions/filters/network/kafka/response_codec.h"
#include "extensions/filters/network/kafka/external/requests.h"
#include "extensions/filters/network/kafka/external/responses.h"

#include "envoy/network/connection.h"
#include "common/buffer/buffer_impl.h"

#include <thread>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::string stringify(const Bytes& arg) {
  std::ostringstream os;
  os << "[";
  for (auto iter = arg.begin(); iter != arg.end(); iter++) {
    if (iter != arg.begin()) {
      os << ", ";
    }
    os << *iter;
  }
  os << "]";
  return os.str();
}

class RequestHandler: public RequestCallback, private Logger::Loggable<Logger::Id::kafka> {
public:

  RequestHandler(KafkaMeshFilter& filter): filter_{filter} {
  }

  void onMessage(AbstractRequestSharedPtr arg) override {
    switch (arg->request_header_.api_key_) {
    case /* Produce */ 0: {
      const std::shared_ptr<Request<ProduceRequest>> cast = std::dynamic_pointer_cast<Request<ProduceRequest>>(arg);
      ENVOY_LOG(trace, "Produce request OK: {}", *cast);
      filter_.respondToProduce(cast);
      break;
    }
    case /* Metadata */ 3: {
      const std::shared_ptr<Request<MetadataRequest>> cast = std::dynamic_pointer_cast<Request<MetadataRequest>>(arg);
      ENVOY_LOG(trace, "Metadata request OK: {}", *cast);
      filter_.respondToMetadata(cast);
      break;
    }
    case /* ApiVersions */ 18: {
      const std::shared_ptr<Request<ApiVersionsRequest>> cast = std::dynamic_pointer_cast<Request<ApiVersionsRequest>>(arg);
      ENVOY_LOG(trace, "ApiVersions request OK: {}", *cast);
      filter_.respondToApiVersions(cast);
      break;
    }
    default: {
      ENVOY_LOG(warn, "unknown request: {}/{}", arg->request_header_.api_key_, arg->request_header_.api_version_);
      break;
    }
    }
  }

  void onFailedParse(RequestParseFailureSharedPtr) override {
    ENVOY_LOG(warn, "got parse failure");
    // kill connection.
  }

private:

  KafkaMeshFilter& filter_;

};

// === KAFKA MESH FILTER ===========================================================================

KafkaMeshFilter::KafkaMeshFilter(UpstreamKafkaFacade& upstream_kafka_facade):
    request_decoder_{new RequestDecoder({std::make_shared<RequestHandler>(*this)})},
    request_in_flight_factory_{*this},
    upstream_kafka_facade_{upstream_kafka_facade}
{
}

KafkaMeshFilter::~KafkaMeshFilter() {
  ENVOY_LOG(trace, "KafkaMeshFilter - dtor");
}

Network::FilterStatus KafkaMeshFilter::onNewConnection() {
  ENVOY_LOG(trace, "KafkaMeshFilter - onNewConnection");
  return Network::FilterStatus::Continue;
}

void KafkaMeshFilter::initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) {
  ENVOY_LOG(trace, "KafkaMeshFilter - initializeReadFilterCallbacks");
  read_filter_callbacks_ = &callbacks;
}

Network::FilterStatus KafkaMeshFilter::onData(Buffer::Instance &data, bool) {
  const std::thread::id tid = std::this_thread::get_id();
  ENVOY_LOG(trace, "KafkaMeshFilter - onData [{} request bytes] IN {}", data.length(), tid);

  try {
    request_decoder_->onData(data);
    data.drain(data.length()); // All the bytes have been copied to decoder.
    return Network::FilterStatus::StopIteration;
  }
  catch (const EnvoyException& e) {
    ENVOY_LOG(info, "could not process data from Kafka client: {}", e.what());
    request_decoder_->reset();
    return Network::FilterStatus::StopIteration;
  }
}

void KafkaMeshFilter::respondToProduce(const std::shared_ptr<Request<ProduceRequest>> request) {
  AbstractInFlightRequestSharedPtr split_request = request_in_flight_factory_.create(request);
  requests_in_flight_.push_back(split_request);
  split_request->invoke(upstream_kafka_facade_, clustering_logic_);
}

void KafkaMeshFilter::respondToApiVersions(const std::shared_ptr<Request<ApiVersionsRequest>> request) {
  AbstractInFlightRequestSharedPtr split_request = request_in_flight_factory_.create(request);
  requests_in_flight_.push_back(split_request);
  split_request->invoke(upstream_kafka_facade_, clustering_logic_);
}

void KafkaMeshFilter::respondToMetadata(const std::shared_ptr<Request<MetadataRequest>> request) {
  AbstractInFlightRequestSharedPtr split_request = request_in_flight_factory_.create(request);
  requests_in_flight_.push_back(split_request);
  split_request->invoke(upstream_kafka_facade_, clustering_logic_);
}

void KafkaMeshFilter::onRequestReadyForAnswer() {
  while (!requests_in_flight_.empty()) {
    AbstractInFlightRequestSharedPtr& rq = requests_in_flight_.front();
    if (rq->finished()) {
      // Drop the request.
      requests_in_flight_.erase(requests_in_flight_.begin());
      AbstractResponseSharedPtr response = rq->computeAnswer();

      // And write it downstream.
      Buffer::OwnedImpl buffer;
      ResponseEncoder encoder{buffer};
      encoder.encode(*response);
      read_filter_callbacks_->connection().write(buffer, false);
    } else {
      break;
    }
  }
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
