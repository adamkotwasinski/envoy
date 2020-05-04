#pragma once

#include "envoy/config/cluster/kafka/kafka_cluster.pb.h"
#include "envoy/config/cluster/kafka/kafka_cluster.pb.validate.h"

#include "envoy/stats/scope.h"

#include "envoy/upstream/cluster_manager.h"
#include "envoy/upstream/upstream.h"

#include "common/network/address_impl.h"
#include "common/network/utility.h"
#include "common/upstream/cluster_factory_impl.h"
#include "common/upstream/upstream_impl.h"

#include "common/common/logger.h"

#include "common/config/well_known_names.h"
#include "extensions/clusters/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace Clusters {
namespace Kafka {

class KafkaCluster: public Upstream::BaseDynamicClusterImpl {
public:

  KafkaCluster(
      const envoy::config::cluster::v3::Cluster &cluster,
      const envoy::config::cluster::kafka::KafkaClusterConfig& proto_config,
      Upstream::ClusterFactoryContext &cluster_factory_context,
      Server::Configuration::TransportSocketFactoryContextImpl &transport_socket_factory_context,
      Stats::ScopePtr &&stats_scope);

  InitializePhase initializePhase() const override;

  void startPreInit() override;

private:

  const envoy::config::cluster::kafka::KafkaClusterConfig proto_config_;

};

class KafkaClusterFactory: public Upstream::ConfigurableClusterFactoryBase<
    envoy::config::cluster::kafka::KafkaClusterConfig>, private Logger::Loggable<Logger::Id::kafka> {

public:

  KafkaClusterFactory():
    ConfigurableClusterFactoryBase(Extensions::Clusters::ClusterTypes::get().Kafka)
  {
  }

private:
  std::pair<Upstream::ClusterImplBaseSharedPtr, Upstream::ThreadAwareLoadBalancerPtr>
  createClusterWithConfig(const envoy::config::cluster::v3::Cluster &cluster,
      const envoy::config::cluster::kafka::KafkaClusterConfig &proto_config,
      Upstream::ClusterFactoryContext &cluster_factory_context,
      Server::Configuration::TransportSocketFactoryContextImpl &transport_socket_factory_context,
      Stats::ScopePtr &&stats_scope) override;
};

} // namespace Kafka
} // namespace Clusters
} // namespace Extensions
} // namespace Envoy
