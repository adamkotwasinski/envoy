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

// Topic name to topic partitions.
using TopicToPartitionsMap = std::map<std::string, std::vector<int32_t>>;

enum class Reply {
  REJECTED,
  ACCEPTED_AND_WANT_MORE,
  ACCEPTED_AND_FINISHED,
};

// XXX rename
// Callback for objects that want to be notified that new Kafka record has been received.
class RecordCb {
public:
  virtual ~RecordCb() = default;

  // Notify the callback that with a message.
  // @return whether the callback could accept the message
  virtual Reply receive(RdKafkaMessagePtr message) PURE;

  virtual TopicToPartitionsMap interest() const PURE;

  virtual std::string debugId() const PURE;
};

using RecordCbSharedPtr = std::shared_ptr<RecordCb>;

// ========================================================================================

// XXX rename
class StoreCb {
public:
  virtual ~StoreCb() = default;

  virtual void receive(RdKafkaMessagePtr message) PURE;

  virtual bool waitUntilInterest(const std::string& topic, const int32_t timeout_ms) const PURE;
};

using StoreCbPtr = std::unique_ptr<StoreCb>;

/**
 * Kafka consumer pointing to some upstream Kafka cluster.
 * Provides records to callbacks (immediately or after some delay).
 */
class KafkaConsumer {
public:
  virtual ~KafkaConsumer() = default;
};

using KafkaConsumerPtr = std::unique_ptr<KafkaConsumer>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
