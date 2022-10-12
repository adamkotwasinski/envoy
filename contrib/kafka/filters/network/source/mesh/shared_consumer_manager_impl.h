#pragma once

#include <map>
#include <tuple>
#include <vector>

#include "envoy/thread/thread.h"

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_config.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Implements SCM interface by maintaining a collection of Kafka consumers on per-topic basis.
 * Maintains a message cache for messages that had no interest but might be requested later.
 */
// XXX the whole thing needs to be thread-safe
class SharedConsumerManagerImpl : public SharedConsumerManager,
                                  private Logger::Loggable<Logger::Id::kafka> {
public:
  SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration,
                            Thread::ThreadFactory& thread_factory);

  ~SharedConsumerManagerImpl() override;

  /**
   * Registers a callback that is interested in messages for particular partitions.
   */
  void registerFetchCallback(RecordCbSharedPtr callback, FetchSpec fetches) override;

  //void unregisterFetchCallback(RecordCbSharedPtr callback) override;

private:
  KafkaConsumer& getOrCreateConsumer(const std::string& topic);
  // Mutates 'topic_to_consumer_'.
  KafkaConsumer& registerNewConsumer(const std::string& topic);

  const UpstreamKafkaConfiguration& configuration_;
  Thread::ThreadFactory& thread_factory_;

  mutable absl::Mutex consumers_mutex_;
  std::map<std::string, KafkaConsumerPtr> topic_to_consumer_ ABSL_GUARDED_BY(consumers_mutex_);
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy