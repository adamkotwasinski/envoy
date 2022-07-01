#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager_impl.h"

#include <functional>

#include "source/common/common/fmt.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

SharedConsumerManagerImpl::SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration): configuration_{configuration} {
    ENVOY_LOG(info, "SCM ctor");
}

SharedConsumerManagerImpl::~SharedConsumerManagerImpl() {
    ENVOY_LOG(info, "SCM dtor");
}

int64_t SharedConsumerManagerImpl::listOffsets(std::string topic, int32_t partition) {
    return 0;
}

void SharedConsumerManagerImpl::requestFetches(std::vector<FetchSpec> fetches_requested) {
    // For every fetch topic, figure out the upstream cluster, create consumer if needed, and put it all aggregated.
    for (const FetchSpec spec : fetches_requested) {
        const std::string topic = std::get<0>(spec);
        KafkaConsumer& consumer = getOrCreateConsumer(topic);
        consumer.submitPoll(spec);
    }
}

KafkaConsumer& SharedConsumerManagerImpl::getOrCreateConsumer(const std::string& topic) {
  const auto it = topic_to_consumer_.find(topic);
  // Return consumer already present or create new one and register it.
  return (topic_to_consumer_.end() == it) ? registerNewConsumer(topic) : *(it->second);
}

KafkaConsumer& SharedConsumerManagerImpl::registerNewConsumer(const std::string& topic) {
  // Compute which upstream cluster corresponds to the topic.
  const absl::optional<ClusterConfig> cluster_config = configuration_.computeClusterConfigForTopic(topic);
  if (!cluster_config) {
      throw EnvoyException(fmt::format("Could not compute upstream cluster configuration for topic [{}]", topic));
  }
  // Create the consumer and register it.
  KafkaConsumerPtr new_consumer = std::make_unique<RichKafkaConsumer>(cluster_config->upstream_consumer_properties_);
  ENVOY_LOG(info, "Registering new Kafka consumer for topic [{}], consuming from cluster [{}]", topic, cluster_config->name_);
  auto result = topic_to_consumer_.emplace(topic, std::move(new_consumer));
  return *(result.first->second);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy