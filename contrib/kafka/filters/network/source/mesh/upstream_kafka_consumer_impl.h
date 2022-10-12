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

/**
 * Meaningful state for upstream-pointing consumer.
 * Keeps messages received so far that nobody was interested in.
 * Keeps callbacks that are interested in messages.
 */
class Store : private Logger::Loggable<Logger::Id::kafka> {
public:

  bool hasCallbacks() const;

  void getRecordsOrRegisterCallback(RecordCbSharedPtr callback, const std::vector<int32_t>& partitions);

  void removeCallback(RecordCbSharedPtr callback);

  void processNewDelivery(RdKafkaMessagePtr message);

private:

  /**
   * Invariant: for every i, the following holds:
   * !(partition_to_callbacks_[i].size() >= 0 && messages_waiting_for_interest_[i].size() >= 0)
   */

  mutable absl::Mutex callbacks_mutex_;
  std::map<int32_t, std::vector<RecordCbSharedPtr>> partition_to_callbacks_ ABSL_GUARDED_BY(callbacks_mutex_);

  mutable absl::Mutex data_mutex_;
  std::map<int32_t, std::vector<RdKafkaMessagePtr>> messages_waiting_for_interest_ ABSL_GUARDED_BY(data_mutex_);
  // XXX paused_partitions_ field
};

class RichKafkaConsumer : public KafkaConsumer, private Logger::Loggable<Logger::Id::kafka> {
public:
  // Main constructor.
  RichKafkaConsumer(Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration);

  // Visible for testing (allows injection of LibRdKafkaUtils).
  RichKafkaConsumer(Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration,
                    const LibRdKafkaUtils2& utils);

  // More complex than usual - closes the real Kafka consumer.
  ~RichKafkaConsumer() override;

  // KafkaConsumer
  void getRecordsOrRegisterCallback(RecordCbSharedPtr callback, const std::vector<int32_t>& partitions) override;

  // XXX private?
  void pollContinuously();

private:
  std::vector<RdKafkaMessagePtr> receiveMessageBatch();

  // The topic we are consuming from.
  std::string topic_;

  // Real Kafka consumer (NOT thread-safe).
  // All access to this thing happens in ???.
  std::unique_ptr<RdKafka::KafkaConsumer> consumer_;

  // Consumer's assignment.
  std::vector<RdKafkaTopicPartitionRawPtr> assignment_;

  // Flag controlling poller threads's execution.
  std::atomic<bool> poller_thread_active_;

  // Real worker thread.
  // Responsible for polling for records with consumer, and passing these records to awaiting
  // requests.
  Thread::ThreadPtr poller_thread_;

  // Stores interest in polled messages and messages that had no interest.
  Store store_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
