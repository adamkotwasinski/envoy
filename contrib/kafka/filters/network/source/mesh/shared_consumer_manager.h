#pragma once

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_client.h"

#include <map>
#include <vector>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// Topic name to topic partitions.
using FetchSpec = std::map<std::string, std::vector<int32_t>>;

/**
 * ???
 */
class SharedConsumerManager {
public:
    virtual ~SharedConsumerManager() = default;

    virtual int64_t listOffsets(std::string topic, int32_t partition) PURE;

    virtual void processFetches(RecordCbSharedPtr callback, FetchSpec fetches) PURE; //const& ?
};

using SharedConsumerManagerSharedPtr = std::shared_ptr<SharedConsumerManager>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy