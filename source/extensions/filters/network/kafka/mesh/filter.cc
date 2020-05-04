#include "extensions/filters/network/kafka/mesh/filter.h"
#include "extensions/filters/network/kafka/external/requests.h"
#include <thread>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class RequestHandler : public RequestCallback, private Logger::Loggable<Logger::Id::kafka> {

  void onMessage(AbstractRequestSharedPtr arg) override {
    const int16_t api_key = arg->request_header_.api_key_;
    if (18 == api_key) {
      const std::shared_ptr<Request<MetadataRequest>> cast = std::dynamic_pointer_cast<Request<MetadataRequest>>(arg);
      ENVOY_LOG(info, "cast ok: {}", cast == nullptr);
    } else {
      ENVOY_LOG(info, "unknown request: {} / {}", arg->request_header_.api_key_, arg->request_header_.api_version_);
    }


  }

  void onFailedParse(RequestParseFailureSharedPtr ) override {
    ENVOY_LOG(info, "got failure");
  }

};

KafkaMeshFilter::KafkaMeshFilter():
    response_decoder_{new ResponseDecoder({})},
    request_decoder_{new RequestDecoder({  std::make_shared<RequestHandler>()  })}
{
};

Network::FilterStatus KafkaMeshFilter::onNewConnection() {
  return Network::FilterStatus::Continue;
}

void KafkaMeshFilter::initializeReadFilterCallbacks(Network::ReadFilterCallbacks&) {}

Network::FilterStatus KafkaMeshFilter::onData(Buffer::Instance& data, bool) {
  std::thread::id this_id = std::this_thread::get_id();
  ENVOY_LOG(warn, "REQUEST COMING [{} request bytes] IN {}", data.length(), this_id);
  return Network::FilterStatus::StopIteration;

  /*
  try {
    request_decoder_->onData(data);
    return Network::FilterStatus::StopIteration;
  } catch (const EnvoyException& e) {
    ENVOY_LOG(info, "could not process data from Kafka client: {}", e.what());
    request_decoder_->reset();
    return Network::FilterStatus::StopIteration;
  }
  */
}

RequestDecoderSharedPtr KafkaMeshFilter::getRequestDecoderForTest() {
  return request_decoder_;
}

ResponseDecoderSharedPtr KafkaMeshFilter::getResponseDecoderForTest() {
  return response_decoder_;
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
