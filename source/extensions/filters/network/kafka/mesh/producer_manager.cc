#include "extensions/filters/network/kafka/mesh/producer_manager.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FilterProducerManager::FilterProducerManager() {
  ENVOY_LOG(warn, "FilterProducerManager - ctor");
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
