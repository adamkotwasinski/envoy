#include "kafka_cluster.h"

namespace Envoy {
namespace Extensions {
namespace Clusters {
namespace Kafka {

KafkaCluster::KafkaCluster(
    const envoy::config::cluster::v3::Cluster &cluster,
    const envoy::config::cluster::kafka::KafkaClusterConfig& proto_config,
    Upstream::ClusterFactoryContext &cluster_factory_context,
    Server::Configuration::TransportSocketFactoryContextImpl &transport_socket_factory_context,
    Stats::ScopePtr &&stats_scope):
      Upstream::BaseDynamicClusterImpl{cluster, cluster_factory_context.runtime(), transport_socket_factory_context, std::move(stats_scope), cluster_factory_context.addedViaApi() },
      proto_config_{proto_config}
{
  // envoy magic
  const bool has_load_assignment = cluster.has_load_assignment();
  const auto locality_load_assignment =
      has_load_assignment ?
          cluster.load_assignment() :
          Config::Utility::translateClusterHosts(cluster.hidden_envoy_deprecated_hosts());
  const auto &locality_endpoints = locality_load_assignment.endpoints();

  for (const auto &locality_endpoint : locality_endpoints) {
    for (const auto &endpoint : locality_endpoint.lb_endpoints()) {
      const auto &host = endpoint.endpoint().address();
      const std::string hostname = host.socket_address().address();
      const uint32_t port = host.socket_address().port_value();
      ENVOY_LOG(warn, "host-port [{}] {}:{}", cluster.name(), hostname, port);
    }
  }
  // envoy magic end
}

KafkaCluster::InitializePhase KafkaCluster::initializePhase() const {
  return InitializePhase::Primary;
}

void KafkaCluster::startPreInit() {
  ENVOY_LOG(info, "KafkaCluster - startPreInit");
  onPreInitComplete();
}

std::pair<Upstream::ClusterImplBaseSharedPtr, Upstream::ThreadAwareLoadBalancerPtr>
KafkaClusterFactory::createClusterWithConfig(
    const envoy::config::cluster::v3::Cluster& cluster,
    const envoy::config::cluster::kafka::KafkaClusterConfig& proto_config,
    Upstream::ClusterFactoryContext& cluster_factory_context,
    Server::Configuration::TransportSocketFactoryContextImpl& transport_socket_factory_context,
    Stats::ScopePtr&& stats_scope) {

  if (!cluster.has_cluster_type() || Extensions::Clusters::ClusterTypes::get().Kafka != cluster.cluster_type().name()) {
    throw EnvoyException("Kafka cluster can only created with kafka cluster type.");
  }

  ENVOY_LOG(info, "KafkaClusterFactory - createClusterWithConfig: {}", cluster.name());
  std::shared_ptr<KafkaCluster> result = std::make_shared<KafkaCluster>(
      cluster, proto_config, cluster_factory_context, transport_socket_factory_context, std::move(stats_scope));
  return std::make_pair(result, nullptr);
}

REGISTER_FACTORY(KafkaClusterFactory, Upstream::ClusterFactory);

} // namespace Kafka
} // namespace Clusters
} // namespace Extensions
} // namespace Envoy
