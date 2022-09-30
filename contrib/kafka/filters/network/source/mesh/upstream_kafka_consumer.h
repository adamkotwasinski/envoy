#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "envoy/common/pure.h"

// FIXME
#include "librdkafka/rdkafkacpp.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// FIXME duplicate of _impl.h
using RdKafkaMessagePtr = std::shared_ptr<RdKafka::Message>;

enum class Reply {
  REJECTED,
  ACCEPTED_AND_WANT_MORE,
  ACCEPTED_AND_FINISHED,
};

// Callback for objects that want to be notified that new Kafka record has been received.
class RecordCb {
public:
  virtual ~RecordCb() = default;

  // Notify the callback that with a message.
  // @return whether the callback could accept the message
  virtual Reply receive(RdKafkaMessagePtr message) PURE;

  virtual std::string debugId() const PURE;
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
