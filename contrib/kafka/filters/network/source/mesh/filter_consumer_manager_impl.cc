#include "contrib/kafka/filters/network/source/mesh/filter_consumer_manager_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FilterConsumerManagerImpl::FilterConsumerManagerImpl() {
    ENVOY_LOG(info, "FCM ctor");
}

int64_t FilterConsumerManagerImpl::listOffsets(std::string topic, int32_t partition) {
    return 0;
}

void FilterConsumerManagerImpl::fetchRecords(std::string topic, int32_t partition, int64_t offset) {
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy