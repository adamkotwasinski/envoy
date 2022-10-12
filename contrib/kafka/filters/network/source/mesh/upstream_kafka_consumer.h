#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "envoy/common/pure.h"

#include "contrib/kafka/filters/network/source/mesh/inbound_record.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

<<<<<<< HEAD
/**
 * An entity that is interested in inbound records delivered by Kafka consumer.
 */
class InboundRecordProcessor {
=======
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
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
public:
  virtual ~InboundRecordProcessor() = default;

  /**
   * Passes the record to the processor.
   */
  virtual void receive(InboundRecordSharedPtr message) PURE;

<<<<<<< HEAD
  /**
   * Blocks until there is interest in records in a given topic, or timeout expires.
   * Conceptually a thick condition variable.
   * @return true if there was interest.
   */
  virtual bool waitUntilInterest(const std::string& topic, const int32_t timeout_ms) const PURE;
=======
  virtual TopicToPartitionsMap interest() const PURE;

  virtual std::string debugId() const PURE;
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
};

using InboundRecordProcessorPtr = std::unique_ptr<InboundRecordProcessor>;

// ========================================================================================

// XXX rename
class StoreCb {
public:
  virtual ~StoreCb() = default;

  virtual void receive(RdKafkaMessagePtr message) PURE;

  virtual bool hasInterest(const std::string& topic) const PURE;
};

/**
 * Kafka consumer pointing to some upstream Kafka cluster.
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
