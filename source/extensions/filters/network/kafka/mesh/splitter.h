#pragma once

#include "common/common/logger.h"

#include "extensions/filters/network/kafka/mesh/command.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class RequestInFlightFactory: private Logger::Loggable<Logger::Id::kafka> {
public:

  RequestInFlightFactory(AbstractRequestListener& origin);

  AbstractInFlightRequestSharedPtr create(const std::shared_ptr<Request<ProduceRequest>> request) const;

  AbstractInFlightRequestSharedPtr create(const std::shared_ptr<Request<MetadataRequest>> request) const;

  AbstractInFlightRequestSharedPtr create(const std::shared_ptr<Request<ApiVersionsRequest>> request) const;


private:

  AbstractRequestListener& origin_;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
