#pragma once

#include <atomic>
#include <list>
#include <vector>

#include "envoy/event/dispatcher.h"
#include "envoy/thread/thread.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"
#include "librdkafka/rdkafkacpp.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Helper class responsible for creating librdkafka entities, so we can have mocks in tests.
 */
class LibRdKafkaUtils2 {
public:
  virtual ~LibRdKafkaUtils2() = default;

  virtual RdKafka::Conf::ConfResult setConfProperty(RdKafka::Conf& conf, const std::string& name,
                                                    const std::string& value,
                                                    std::string& errstr) const PURE;

  virtual std::unique_ptr<RdKafka::KafkaConsumer> createConsumer(RdKafka::Conf*,
                                                                 std::string& errstr) const PURE;

};

using RawKafkaConfig = std::map<std::string, std::string>;

using RdKafkaTopicPartitionRawPtr = RdKafka::TopicPartition*;

using RdKafkaMessagePtr = std::shared_ptr<RdKafka::Message>;

class RichKafkaConsumer : public KafkaConsumer, private Logger::Loggable<Logger::Id::kafka> {
public:
  // Main constructor.
  RichKafkaConsumer(StoreCb& store_cb, Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration);

  // Visible for testing (allows injection of LibRdKafkaUtils2).
  RichKafkaConsumer(StoreCb& store_cb, Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration,
                    const LibRdKafkaUtils2& utils);

  // More complex than usual - closes the real Kafka consumer.
  ~RichKafkaConsumer() override;

  // XXX private?
  void pollContinuously();

private:

  // XXX
  std::vector<RdKafkaMessagePtr> receiveMessageBatch();

  // XXX
  StoreCb& store_cb_;

  // The topic we are consuming from.
  std::string topic_;

  // Real Kafka consumer (NOT thread-safe).
  // All access to this thing happens in ???.
  std::unique_ptr<RdKafka::KafkaConsumer> consumer_;

  // Consumer's assignment.
  std::vector<RdKafkaTopicPartitionRawPtr> assignment_;

  // XXX paused_partitions_ field

  // Flag controlling poller threads's execution.
  std::atomic<bool> poller_thread_active_;

  // Real worker thread.
  // Responsible for polling for records with consumer, and passing these records to awaiting
  // requests.
  Thread::ThreadPtr poller_thread_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
