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

  virtual RdKafka::Conf::ConfResult setConfDeliveryCallback(RdKafka::Conf& conf,
                                                            RdKafka::DeliveryReportCb* dr_cb,
                                                            std::string& errstr) const PURE;

  virtual std::unique_ptr<RdKafka::Producer> createProducer(RdKafka::Conf* conf,
                                                            std::string& errstr) const PURE;

  virtual std::unique_ptr<RdKafka::KafkaConsumer> createConsumer(RdKafka::Conf*,
                                                                 std::string& errstr) const PURE;

  // Returned type is a raw pointer, as librdkafka does the deletion on successful produce call.
  virtual RdKafka::Headers* convertHeaders(
      const std::vector<std::pair<absl::string_view, absl::string_view>>& headers) const PURE;

  // In case of produce failures, we need to dispose of headers manually.
  virtual void deleteHeaders(RdKafka::Headers* librdkafka_headers) const PURE;
};

using RawKafkaConfig = std::map<std::string, std::string>;

using RdKafkaTopicPartitionRawPtr = RdKafka::TopicPartition*;

using RdKafkaMessagePtr = std::unique_ptr<RdKafka::Message>;

class Store : private Logger::Loggable<Logger::Id::kafka> {
public:
  bool hasInterest() const;

  void registerInterest(RecordCbSharedPtr callback, const std::vector<int32_t>& partitions);

  void processNewDeliveries(std::vector<RdKafkaMessagePtr> messages);

private:
  void processNewDelivery(RdKafkaMessagePtr message);

  void eraseCallback(RecordCbSharedPtr callback);

  mutable absl::Mutex callbacks_mutex_;
  std::map<int32_t, std::vector<RecordCbSharedPtr>> partition_to_callbacks_ ABSL_GUARDED_BY(callbacks_mutex_);

  mutable absl::Mutex data_mutex_;
  std::map<int32_t, std::vector<RdKafkaMessagePtr>> messages_waiting_for_interest_ ABSL_GUARDED_BY(data_mutex_);
  std::vector<int32_t> paused_partitions_ ABSL_GUARDED_BY(data_mutex_);
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
  // ???
  ~RichKafkaConsumer() override;

  // ???
  void registerInterest(RecordCbSharedPtr callback,
                        const std::vector<int32_t>& partitions) override;

  // ???
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
