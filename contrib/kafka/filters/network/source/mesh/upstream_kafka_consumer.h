#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "envoy/common/pure.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// Callback for objects that want to be notified that new Kafka record has been received.
class RecordCb {
public:
  virtual ~RecordCb() = default;

  // ???
  virtual void accept() PURE;
};

using RecordCbSharedPtr = std::shared_ptr<RecordCb>;

class KafkaConsumer {
public:
  virtual ~KafkaConsumer() = default;

  virtual void registerInterest(RecordCbSharedPtr callback,
                                const std::vector<int32_t>& partitions) PURE;
};

using KafkaConsumerPtr = std::unique_ptr<KafkaConsumer>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
