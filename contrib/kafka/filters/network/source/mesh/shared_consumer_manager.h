#pragma once

#include <map>
#include <vector>

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"

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

  virtual void registerFetchCallback(RecordCbSharedPtr callback, FetchSpec fetches) PURE; // const& ?

  //virtual void unregisterFetchCallback(RecordCbSharedPtr callback) PURE; // const& ?
};

using SharedConsumerManagerSharedPtr = std::shared_ptr<SharedConsumerManager>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy