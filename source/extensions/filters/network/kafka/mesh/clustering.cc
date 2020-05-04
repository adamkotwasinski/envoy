#include "extensions/filters/network/kafka/mesh/clustering.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

ClusteringLogic::ClusteringLogic() {}

std::string ClusteringLogic::computeClusterForTopic(const std::string& topic) const {
  if (topic.rfind("apples", 0) == 0) {
    return "localkafka_m1";
  } else {
    return "localkafka_m2";
  }
}

using ForwardingRule = envoy::extensions::filters::network::kafka_mesh::v3::ForwardingRule;

Magic::Magic(const KafkaMeshProtoConfig& config) {
  ENVOY_LOG(warn, "advertised: {}", config.advertised_listener());

  auto forwarding_rules = config.forwarding_rules();
  ASSERT(!forwarding_rules.empty());

  for (const auto& rule : forwarding_rules) {
    const std::string& target_cluster = rule.target_cluster();
    ASSERT(rule.trigger_case() == ForwardingRule::TriggerCase::kTopicPrefix);
    ENVOY_LOG(warn, "rule: {} -> {}", rule.topic_prefix(), target_cluster);
  }
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
