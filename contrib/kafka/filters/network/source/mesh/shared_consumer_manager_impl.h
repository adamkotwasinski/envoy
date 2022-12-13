#pragma once

#include <map>
#include <vector>

#include "envoy/server/lifecycle_notifier.h"
#include "envoy/thread/thread.h"

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/kafka_types.h"
#include "contrib/kafka/filters/network/source/mesh/librdkafka_utils.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_config.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Meaningful state for upstream-pointing consumer.
 * Keeps messages received so far that nobody was interested in.
 * Keeps callbacks that are interested in messages.
 *
 * Mutex locking order:
 * 1. store's consumer list mutex (consumers_mutex_)
 * 2. message's data mutex (data_mutex_)
 */
class RecordDistributor : public InboundRecordProcessor,
                          private Logger::Loggable<Logger::Id::kafka> {
public:
  // InboundRecordProcessor
  bool waitUntilInterest(const std::string& topic, const int32_t timeout_ms) const override;

  // InboundRecordProcessor
  void receive(InboundRecordSharedPtr message) override;

  // XXX
  void getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback);

  // XXX
  void removeCallback(const RecordCbSharedPtr& callback);

private:
  // XXX
  bool hasInterest(const std::string& topic) const ABSL_EXCLUSIVE_LOCKS_REQUIRED(callbacks_mutex_);

  // HAX!
  void removeCallbackWithoutLocking(
      const RecordCbSharedPtr& callback,
      std::map<KafkaPartition, std::vector<RecordCbSharedPtr>>& partition_to_callbacks);

  /**
   * Invariant: for every i: KafkaPartition, the following holds:
   * !(partition_to_callbacks_[i].size() >= 0 && messages_waiting_for_interest_[i].size() >= 0)
   */

  mutable absl::Mutex callbacks_mutex_;
  std::map<KafkaPartition, std::vector<RecordCbSharedPtr>>
      partition_to_callbacks_ ABSL_GUARDED_BY(callbacks_mutex_);

  mutable absl::Mutex messages_mutex_;
  std::map<KafkaPartition, std::vector<InboundRecordSharedPtr>>
      messages_waiting_for_interest_ ABSL_GUARDED_BY(messages_mutex_);
};

using RecordDistributorPtr = std::unique_ptr<RecordDistributor>;

/**
 * Injectable for tests.
 */
class KafkaConsumerFactory {
public:
  virtual ~KafkaConsumerFactory() = default;

  // Create a Kafka consumer.
  virtual KafkaConsumerPtr createConsumer(InboundRecordProcessor& record_processor,
                                          Thread::ThreadFactory& thread_factory,
                                          const std::string& topic, const int32_t partition_count,
                                          const RawKafkaConfig& configuration) const PURE;
};

/**
 * Maintains a collection of Kafka consumers (one per topic).
 * Implements SCM interface by maintaining a collection of Kafka consumers on per-topic basis.
 * Maintains a message cache for messages that had no interest but might be requested later.
 * ???
 */
class SharedConsumerManagerImpl : public SharedConsumerManager,
                                  private Logger::Loggable<Logger::Id::kafka> {
public:
  // Main constructor.
  SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration,
                            Thread::ThreadFactory& thread_factory,
                            Server::ServerLifecycleNotifier& lifecycle_notifier);

  // Visible for testing.
  SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration,
                            Thread::ThreadFactory& thread_factory,
                            Server::ServerLifecycleNotifier& lifecycle_notifier,
                            const KafkaConsumerFactory& consumer_factory);

  ~SharedConsumerManagerImpl() override;

  /**
   * Registers a callback that is interested in messages for particular partitions.
   */
  void getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback) override;

  void removeCallback(const RecordCbSharedPtr& callback) override;

  void registerConsumerIfAbsent(const std::string& topic) override;

  size_t getConsumerCountForTest() const;

private:
  // Mutates 'topic_to_consumer_'.
  void registerNewConsumer(const std::string& topic)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(consumers_mutex_);

  // Disables this instance (so it can no longer be used by requests).
  // After this method finishes, no requests (RecordCbSharedPtr) are ever held by this object (what
  // means they are held only by originating filter).
  void doShutdown();

  RecordDistributorPtr distributor_;

  const UpstreamKafkaConfiguration& configuration_;
  Thread::ThreadFactory& thread_factory_;
  const KafkaConsumerFactory& consumer_factory_;

  mutable absl::Mutex consumers_mutex_;
  std::map<std::string, KafkaConsumerPtr> topic_to_consumer_ ABSL_GUARDED_BY(consumers_mutex_);

  // Hooks 'doShutdown'.
  Server::ServerLifecycleNotifier::HandlePtr shutdown_callback_handle_;
  mutable absl::Mutex active_mutex_;
  bool active_ ABSL_GUARDED_BY(active_mutex_) = true;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
