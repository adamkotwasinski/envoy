#pragma once

#include <vector>
#include <tuple>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// Topic name, topic partition, partition offset.
using FetchSpec = std::tuple<std::string, int32_t, int64_t>;

/**
 * Thing that holds Kafka consumers pointing upstream.
 */
class SharedConsumerManager {
public:
    virtual ~SharedConsumerManager() = default;

    virtual int64_t listOffsets(std::string topic, int32_t partition) PURE;

    virtual void requestFetches(std::vector<FetchSpec> fetches_requested) PURE;
};

using SharedConsumerManagerSharedPtr = std::shared_ptr<SharedConsumerManager>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy