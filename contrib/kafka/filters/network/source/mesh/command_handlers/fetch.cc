#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch.h"

#include "contrib/kafka/filters/network/source/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FetchRequestHolder::FetchRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<FetchRequest>> request): BaseInFlightRequest{filter}, request_{request} {}

void FetchRequestHolder::startProcessing() { notifyFilter(); }

bool FetchRequestHolder::finished() const { return true; }

AbstractResponseSharedPtr FetchRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int32_t throttle_time_ms = 0;
  const std::vector<FetchableTopicResponse> responses; // No data for now.
  const FetchResponse data = { throttle_time_ms, responses };
  return std::make_shared<Response<FetchResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
