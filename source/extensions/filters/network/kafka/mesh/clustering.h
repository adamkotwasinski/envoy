#pragma once

#include "envoy/extensions/filters/network/kafka_mesh/v3alpha/kafka_mesh.pb.h"
#include "envoy/extensions/filters/network/kafka_mesh/v3alpha/kafka_mesh.pb.validate.h"

#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

using KafkaMeshProtoConfig = envoy::extensions::filters::network::kafka_mesh::v3alpha::KafkaMesh;

// Minor helper structure that contains information about upstream Kafka clusters.
struct ClusterConfig {

  // Cluster name, as it appears in configuration input.
  std::string name_;

  // How many partitions do we expect for every one of the topics present in given upstream cluster.
  // Impl note: this could be replaced with creating (shared?) AdminClient and having it reach out
  // upstream to get configuration (or we could just send a correct request via codec). The response
  // would need to be cached (as this data is frequently requested).
  int32_t partition_count_;

  // The configuration that will be passed to upstream client for given cluster.
  // This allows us to reference different clusters with different configs (e.g. linger.ms).
  // This map always contains entry with key 'bootstrap.servers', as this is the only mandatory
  // producer property.
  std::map<std::string, std::string> upstream_producer_properties_;

  bool operator==(const ClusterConfig& rhs) const {
    return name_ == rhs.name_ && partition_count_ == rhs.partition_count_ &&
           upstream_producer_properties_ == rhs.upstream_producer_properties_;
  }
};

/**
 * Keeps the configuration related to upstream Kafka clusters.
 * Impl note: current matching from topic to cluster is based on prefix matching but more complex
 * rules could be added.
 */
class ClusteringConfiguration {
public:
  virtual ~ClusteringConfiguration() = default;
  virtual absl::optional<ClusterConfig>
  computeClusterConfigForTopic(const std::string& topic) const PURE;
  virtual std::pair<std::string, int32_t> getAdvertisedAddress() const PURE;
};

using ClusteringConfigurationSharedPtr = std::shared_ptr<const ClusteringConfiguration>;

class ClusteringConfigurationImpl : public ClusteringConfiguration,
                                    private Logger::Loggable<Logger::Id::kafka> {
public:
  ClusteringConfigurationImpl(const KafkaMeshProtoConfig& config);
  absl::optional<ClusterConfig>
  computeClusterConfigForTopic(const std::string& topic) const override;
  std::pair<std::string, int32_t> getAdvertisedAddress() const override;

private:
  const std::pair<std::string, int32_t> advertised_address_;
  std::map<std::string, ClusterConfig> topic_prefix_to_cluster_config_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
