#pragma once

#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FilterProducerManager: private Logger::Loggable<Logger::Id::kafka> {
public:
  FilterProducerManager();

private:
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
