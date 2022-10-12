#pragma once

#include <atomic>
#include <list>
#include <vector>

#include "envoy/event/dispatcher.h"
#include "envoy/thread/thread.h"

#include "contrib/kafka/filters/network/source/mesh/librdkafka_utils.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"
<<<<<<< HEAD
=======
#include "contrib/kafka/filters/network/source/mesh/librdkafka_utils.h"
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

using RdKafkaPartitionRawPtr = RdKafka::TopicPartition*;
using RdKafkaPartitionVector = std::vector<RdKafkaPartitionRawPtr>;

<<<<<<< HEAD
/**
 * Combines the librdkafka consumer and its dedicated thread.
 * The thread receives the records, and pushes them to the processor.
 */
class RichKafkaConsumer : public KafkaConsumer, private Logger::Loggable<Logger::Id::kafka> {
public:
  // Main constructor.
  RichKafkaConsumer(InboundRecordProcessor& record_processor, Thread::ThreadFactory& thread_factory,
                    const std::string& topic, int32_t partition_count,
                    const RawKafkaConfig& configuration);

  // Visible for testing (allows injection of LibRdKafkaUtils).
  RichKafkaConsumer(InboundRecordProcessor& record_processor, Thread::ThreadFactory& thread_factory,
                    const std::string& topic, int32_t partition_count,
                    const RawKafkaConfig& configuration, const LibRdKafkaUtils& utils);
=======
class RichKafkaConsumer : public KafkaConsumer, private Logger::Loggable<Logger::Id::kafka> {
public:
  // Main constructor.
  RichKafkaConsumer(StoreCb& store_cb, Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration);

  // Visible for testing (allows injection of LibRdKafkaUtils2).
  RichKafkaConsumer(StoreCb& store_cb, Thread::ThreadFactory& thread_factory, const std::string& topic,
                    int32_t partition_count, const RawKafkaConfig& configuration,
                    const LibRdKafkaUtils& utils);
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)

  // More complex than usual - closes the real Kafka consumer and disposes of the assignment object.
  ~RichKafkaConsumer() override;

<<<<<<< HEAD
private:
  // This method continuously fetches new records and passes them to processor.
  // Does not finish until this object gets destroyed.
  // Executed in the dedicated thread.
  void pollContinuously();

  // Uses internal consumer to receive records from upstream.
  std::vector<InboundRecordSharedPtr> receiveRecordBatch();

  // The record processor (provides info whether it wants records and consumes them).
  InboundRecordProcessor& record_processor_;
=======
  // XXX private?
  void pollContinuously();

private:

  // XXX
  std::vector<RdKafkaMessagePtr> receiveMessageBatch();
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)

  // XXX
  StoreCb& store_cb_;

  // The topic we are consuming from.
  std::string topic_;

  // Real Kafka consumer (NOT thread-safe).
  // All access to this thing happens in the poller thread.
  std::unique_ptr<RdKafka::KafkaConsumer> consumer_;

  // Consumer's assignment.
  // These are raw librdkafka pointers that need to be freed manually in the destructor.
  RdKafkaPartitionVector assignment_;

  // XXX paused_partitions_ field

  // Flag controlling poller threads's execution.
  std::atomic<bool> poller_thread_active_;

  // Real worker thread.
  // Responsible for polling for records with consumer,
  // and passing these records to awaiting requests.
  Thread::ThreadPtr poller_thread_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
