#pragma once

#include <memory>
#include <string>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

struct InboundRecord {

  std::string topic_;
  int32_t partition_;
  int64_t offset_;

  // DATA!

  std::string topic_name() {
    return topic_;
  }

  int32_t partition() {
    return partition_;
  }

  int64_t offset() {
    return offset_;
  }

  InboundRecord(std::string topic, int32_t partition, int64_t offset): topic_{topic}, partition_{partition}, offset_{offset} {};
};

using InboundRecordSharedPtr = std::shared_ptr<InboundRecord>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
