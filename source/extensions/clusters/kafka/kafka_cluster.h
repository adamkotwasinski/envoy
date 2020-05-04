#pragma once

#include "envoy/config/cluster/kafka/kafka_cluster.pb.h"
#include "envoy/config/cluster/kafka/kafka_cluster.pb.validate.h"

#include "envoy/event/dispatcher.h"
#include "envoy/event/timer.h"
#include "envoy/stats/scope.h"

#include "envoy/network/connection.h"
#include "envoy/upstream/cluster_manager.h"
#include "envoy/upstream/upstream.h"

#include "common/network/address_impl.h"
#include "common/network/utility.h"
#include "common/upstream/cluster_factory_impl.h"
#include "common/upstream/upstream_impl.h"
#include "common/common/logger.h"

#include "common/config/well_known_names.h"
#include "extensions/clusters/well_known_names.h"

#include "extensions/filters/network/kafka/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace Clusters {
namespace Kafka {

/// woooo

using namespace NetworkFilters::Kafka;

/// end

using NodeAddress = std::pair<std::string, uint32_t>;

class KafkaCluster;
class BootstrapListener;

using BootstrapServers = std::vector<NodeAddress>;

// ==== WORK =======================================================================================

class EnvoyDeps;
using EnvoyDepsSharedPtr = std::shared_ptr<EnvoyDeps>;

class Context;

class TopologyMonitor;
using TopologyMonitorSharedPtr = std::shared_ptr<TopologyMonitor>;

class NodeWorker;
using NodeWorkerSharedPtr = std::shared_ptr<NodeWorker>;

class EnvoyDeps {
public:

  EnvoyDeps(Upstream::ClusterInfoConstSharedPtr info, Event::Dispatcher &dispatcher): info_{info}, dispatcher_{dispatcher} {
  }

  Upstream::ClusterInfoConstSharedPtr info_;
  Event::Dispatcher &dispatcher_;
};

// ==== REAL THINGS ================================================================================

class Context: private Logger::Loggable<Logger::Id::kafka> {
public:

  Context(EnvoyDepsSharedPtr deps, BootstrapServers bootstrap_servers): deps_{deps}, bootstrap_servers_{bootstrap_servers} {
    ENVOY_LOG(warn, "Context ctor");
  }

  ~Context() {
    ENVOY_LOG(warn, "Context dtor");
  }

  void init();

  // MetadataResponseBroker fields, unless we are at bootstrap phase.
  void registerBroker(const int32_t node_id, const std::string host, const int32_t port);

  NodeAddress getLeastUsedNode() const;

  // === fields

  EnvoyDepsSharedPtr deps_;

  const BootstrapServers bootstrap_servers_;
  absl::Mutex node_workers_mutex_;
  // All workers - including those from 'bootstrap_servers' who are not used for real Kafka operations.
  std::vector<NodeWorkerSharedPtr> all_workers_ GUARDED_BY(node_workers_mutex_);
  // Proper workers - the ones returned by brokers via Metadata calls.
  std::map<int32_t, NodeWorkerSharedPtr> real_workers_ GUARDED_BY(node_workers_mutex_);

  TopologyMonitorSharedPtr topology_monitor_;

  // Where the topics are.
//  absl::Mutex topic_metadata_mutex_;
//  std::map<std::string, int> topic_metadata_ GUARDED_BY(partition_metadata_mutex_);
};

class NodeWorker: private Logger::Loggable<Logger::Id::kafka> {
public:

  NodeWorker(Context& context, EnvoyDepsSharedPtr deps, int32_t id, std::string host, int32_t port);

  ~NodeWorker();

  void init();

  void doWork();

  Context& context_;
  EnvoyDepsSharedPtr deps_;

  const int32_t id_;
  const std::string host_;
  const int32_t port_;

  Event::TimerPtr timer_; // initializable
  Network::ClientConnectionPtr connection_; // mutable
};

class TopologyMonitor: private Logger::Loggable<Logger::Id::kafka> {
public:

  TopologyMonitor(Context& context, EnvoyDepsSharedPtr deps): context_{context}, deps_{deps} {
  }

  ~TopologyMonitor() {
    ENVOY_LOG(warn, "disposing TopologyMonitor");
  }

  void init();

  void updateTopology();

  Context& context_;
  EnvoyDepsSharedPtr deps_;

  Event::TimerPtr timer_; // initializable
  Upstream::HostImpl::CreateConnectionData connection_; // mutable
};

// === CLUSTER =====================================================================================

class KafkaCluster: public Upstream::BaseDynamicClusterImpl {
public:

  KafkaCluster(const envoy::config::cluster::v3::Cluster &cluster,
      Upstream::ClusterFactoryContext &cluster_factory_context,
      Server::Configuration::TransportSocketFactoryContextImpl &transport_socket_factory_context,
      Stats::ScopePtr &&stats_scope) :

      Upstream::BaseDynamicClusterImpl { cluster, cluster_factory_context.runtime(),
          transport_socket_factory_context, std::move(stats_scope), cluster_factory_context.addedViaApi() },
      //    cluster_factory_context_{cluster_factory_context},
      //    transport_socket_factory_context_{transport_socket_factory_context},
      dispatcher_ { transport_socket_factory_context.dispatcher() }

  {
    // envoy magic
    const bool has_load_assignment = cluster.has_load_assignment();
    ENVOY_LOG(warn, "cluster ctor; load assignment present={}", has_load_assignment);
    const auto locality_load_assignment =
        has_load_assignment ?
            cluster.load_assignment() :
            Config::Utility::translateClusterHosts(cluster.hidden_envoy_deprecated_hosts());
    const auto &locality_endpoints = locality_load_assignment.endpoints();

    BootstrapServers bootstrap_servers;
    for (const auto &locality_endpoint : locality_endpoints) {
      for (const auto &endpoint : locality_endpoint.lb_endpoints()) {
        const auto &host = endpoint.endpoint().address();
        const std::string hostname = host.socket_address().address();
        const uint32_t port = host.socket_address().port_value();
        bootstrap_servers.emplace_back(hostname, port);
      }
    }
    // envoy magic end

    deps_ = std::make_shared<EnvoyDeps>(info(), dispatcher_);

    context_ = std::make_unique<Context>(deps_, bootstrap_servers);
    context_->init();
  }

  InitializePhase initializePhase() const override {
    return InitializePhase::Primary;
  }

  void startPreInit() override;

private:

  // remove
//  Upstream::ClusterFactoryContext& cluster_factory_context_;
//  Server::Configuration::TransportSocketFactoryContextImpl& transport_socket_factory_context_;

  // final
  Event::Dispatcher &dispatcher_;

  EnvoyDepsSharedPtr deps_;
  std::unique_ptr<Context> context_;
//  Upstream::HostImpl::CreateConnectionData connection_;
};

class KafkaClusterFactory: public Upstream::ConfigurableClusterFactoryBase<
    envoy::config::cluster::kafka::KafkaClusterConfig>, private Logger::Loggable<Logger::Id::kafka> {

public:
  KafkaClusterFactory() :
      ConfigurableClusterFactoryBase(Extensions::Clusters::ClusterTypes::get().Kafka) {
  }

private:
  std::pair<Upstream::ClusterImplBaseSharedPtr, Upstream::ThreadAwareLoadBalancerPtr>
  createClusterWithConfig(const envoy::config::cluster::v3::Cluster &cluster,
      const envoy::config::cluster::kafka::KafkaClusterConfig &proto_config,
      Upstream::ClusterFactoryContext &context,
      Server::Configuration::TransportSocketFactoryContextImpl &socket_factory_context,
      Stats::ScopePtr &&stats_scope) override;
};

} // namespace Kafka
} // namespace Clusters
} // namespace Extensions
} // namespace Envoy
