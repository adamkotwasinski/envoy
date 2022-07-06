#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager_impl.h"

#include <functional>

#include "source/common/common/fmt.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

SharedConsumerManagerImpl::SharedConsumerManagerImpl(
    const UpstreamKafkaConfiguration& configuration, Thread::ThreadFactory& thread_factory)
    : configuration_{configuration}, thread_factory_{thread_factory} {
  ENVOY_LOG(info, "SCM ctor");
}

SharedConsumerManagerImpl::~SharedConsumerManagerImpl() { ENVOY_LOG(info, "SCM dtor"); }

int64_t SharedConsumerManagerImpl::listOffsets(std::string topic, int32_t partition) { return 0; }

void SharedConsumerManagerImpl::processFetches(RecordCbSharedPtr callback, FetchSpec fetches) {
  // For every fetch topic, figure out the upstream cluster, create consumer if needed, and put it
  // all aggregated.
  for (const auto& f : fetches) {
    const std::string& topic = f.first;
    KafkaConsumer& consumer = getOrCreateConsumer(topic);
    const std::vector<int32_t>& partitions = f.second;
    consumer.registerInterest(callback, partitions);
  }
}

// XXX this needs to be thread safe
KafkaConsumer& SharedConsumerManagerImpl::getOrCreateConsumer(const std::string& topic) {
  const auto it = topic_to_consumer_.find(topic);
  // Return consumer already present or create new one and register it.
  return (topic_to_consumer_.end() == it) ? registerNewConsumer(topic) : *(it->second);
}

KafkaConsumer& SharedConsumerManagerImpl::registerNewConsumer(const std::string& topic) {
  // Compute which upstream cluster corresponds to the topic.
  const absl::optional<ClusterConfig> cluster_config =
      configuration_.computeClusterConfigForTopic(topic);
  if (!cluster_config) {
    throw EnvoyException(
        fmt::format("Could not compute upstream cluster configuration for topic [{}]", topic));
  }
  // Create the consumer and register it.
  KafkaConsumerPtr new_consumer =
      std::make_unique<RichKafkaConsumer>(thread_factory_, topic, cluster_config->partition_count_,
                                          cluster_config->upstream_consumer_properties_);
  ENVOY_LOG(info, "Registering new Kafka consumer for topic [{}], consuming from cluster [{}]",
            topic, cluster_config->name_);
  auto result = topic_to_consumer_.emplace(topic, std::move(new_consumer));
  return *(result.first->second);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy