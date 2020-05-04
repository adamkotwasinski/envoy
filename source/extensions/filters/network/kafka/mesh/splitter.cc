#include "extensions/filters/network/kafka/mesh/splitter.h"

#include <map>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

RequestInFlightFactory::RequestInFlightFactory(AbstractRequestListener& origin): origin_{origin} {
}

AbstractInFlightRequestSharedPtr RequestInFlightFactory::create(const std::shared_ptr<Request<ProduceRequest>> request) const {
  ENVOY_LOG(warn, "RequestInFlightFactory - create(Produce) for {}", request->request_header_.correlation_id_);
  return std::make_shared<ProduceRequestHolder>(origin_, request);
}

AbstractInFlightRequestSharedPtr RequestInFlightFactory::create(const std::shared_ptr<Request<MetadataRequest>> request) const {
  ENVOY_LOG(warn, "RequestInFlightFactory - create(Metadata) for {}", request->request_header_.correlation_id_);
  return std::make_shared<MetadataRequestHolder>(origin_, request);
}

AbstractInFlightRequestSharedPtr RequestInFlightFactory::create(const std::shared_ptr<Request<ApiVersionsRequest>> request) const {
  ENVOY_LOG(warn, "RequestInFlightFactory - create(ApiVersions) for {}", request->request_header_.correlation_id_);
  return std::make_shared<ApiVersionsRequestHolder>(origin_, request);
}


} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
