#pragma once

#include <map>
#include <tuple>
#include <vector>

#include "envoy/thread/thread.h"

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/kafka_types.h"

#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_config.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// =============================================================================================================

/**
 * Meaningful state for upstream-pointing consumer.
 * Keeps messages received so far that nobody was interested in.
 * Keeps callbacks that are interested in messages.
 *
 * Mutex locking order:
 * 1. store's consumer list mutex (consumers_mutex_)
 * 2. message's data mutex (data_mutex_)
 */
class Store : public StoreCb, private Logger::Loggable<Logger::Id::kafka> {
public:

  // StoreCb
  bool waitUntilInterest(const std::string& topic, const int32_t timeout_ms) const override;

  // StoreCb
  void receive(InboundRecordSharedPtr message) override;

  // XXX
  void getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback);

  // XXX
  void removeCallback(const RecordCbSharedPtr& callback);

private:

  // XXX
  bool hasInterest(const std::string& topic) const;

  // HAX!
  void removeCallbackWithoutLocking(const RecordCbSharedPtr& callback, std::map<KafkaPartition, std::vector<RecordCbSharedPtr>>& partition_to_callbacks);

  /**
   * Invariant: for every i: KafkaPartition, the following holds:
   * !(partition_to_callbacks_[i].size() >= 0 && messages_waiting_for_interest_[i].size() >= 0)
   */

  mutable absl::Mutex callbacks_mutex_;
  std::map<KafkaPartition, std::vector<RecordCbSharedPtr>> partition_to_callbacks_ ABSL_GUARDED_BY(callbacks_mutex_);

  mutable absl::Mutex messages_mutex_;
  std::map<KafkaPartition, std::vector<InboundRecordSharedPtr>> messages_waiting_for_interest_ ABSL_GUARDED_BY(messages_mutex_);
};

// =============================================================================================================

/**
 * Implements SCM interface by maintaining a collection of Kafka consumers on per-topic basis.
 * Maintains a message cache for messages that had no interest but might be requested later.
 */
// XXX the whole thing needs to be thread-safe
class SharedConsumerManagerImpl : public SharedConsumerManager,
                                  private Logger::Loggable<Logger::Id::kafka> {
public:
  SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration, Thread::ThreadFactory& thread_factory);

  ~SharedConsumerManagerImpl() override;

  /**
   * Registers a callback that is interested in messages for particular partitions.
   */
  void getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback) override;

  void removeCallback(const RecordCbSharedPtr& callback) override;

private:
  KafkaConsumer& getOrCreateConsumer(const std::string& topic);
  // Mutates 'topic_to_consumer_'.
  KafkaConsumer& registerNewConsumer(const std::string& topic);

  Store store_;

  const UpstreamKafkaConfiguration& configuration_;
  Thread::ThreadFactory& thread_factory_;

  mutable absl::Mutex consumers_mutex_;
  std::map<std::string, KafkaConsumerPtr> topic_to_consumer_ ABSL_GUARDED_BY(consumers_mutex_);
};

// =============================================================================================================

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy