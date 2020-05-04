#include "kafka_cluster.h"

#include "common/network/utility.h"
#include "common/buffer/buffer_impl.h"

#include "extensions/filters/network/kafka/external/requests.h"
#include "extensions/filters/network/kafka/request_codec.h"
#include "extensions/filters/network/kafka/response_codec.h"

namespace Envoy {
namespace Extensions {
namespace Clusters {
namespace Kafka {

///====== COMMUNICATION ============================================================================

class NodeWorkerMessageListener : public ResponseCallback, private Logger::Loggable<Logger::Id::kafka> {
public:

  NodeWorkerMessageListener(NodeWorker& node_worker): node_worker_{node_worker} {
  };

  void onMessage(AbstractResponseSharedPtr data) override {
    ENVOY_LOG(trace, "onMessage {}", data->metadata_.api_key_);
    switch (data->metadata_.api_key_) {
    case 3: {
      const auto metadata_response = std::dynamic_pointer_cast<Response<MetadataResponse>>(data);
      if (nullptr != metadata_response) {
        for (const auto& broker: metadata_response->data_.brokers_) {
          node_worker_.context_.registerBroker(broker.node_id_, broker.host_, broker.port_);
        }
      }
      break;
    }
    default:
      break;
    }

    node_worker_.connection_->close(Network::ConnectionCloseType::NoFlush);
  }

  void onFailedParse(ResponseMetadataSharedPtr) override {
  }

  NodeWorker& node_worker_;
};

using NodeWorkerMessageListenerSharedPtr = std::shared_ptr<NodeWorkerMessageListener>;

class NodeWorkerConnectionFilter : public Network::Filter, private Logger::Loggable<Logger::Id::kafka> {
public:

  NodeWorkerConnectionFilter(NodeWorker& owner) {
    auto listener = std::make_shared<NodeWorkerMessageListener>(owner);
    response_decoder_ = std::shared_ptr<ResponseDecoder>(new ResponseDecoder({ listener }));
  };

  Network::FilterStatus onNewConnection() override {
    return Network::FilterStatus::Continue;
  }

  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks&) override {
  }

  Network::FilterStatus onData(Buffer::Instance& data, bool) override {
    response_decoder_->onData(data);
    return Network::FilterStatus::Continue;
  }

  Network::FilterStatus onWrite(Buffer::Instance&, bool) override {
    return Network::FilterStatus::Continue;
  }

  ResponseDecoderSharedPtr response_decoder_;
};

using NodeWorkerConnectionFilterSharedPtr = std::shared_ptr<NodeWorkerConnectionFilter>;

// === CONTEXT =====================================================================================

void Context::init() {
  absl::WriterMutexLock lock(&node_workers_mutex_); // move to ctor!
  ENVOY_LOG(trace, "Context - init start");
  int32_t mock_id = -1;

  // Initialize workers for bootstrap servers.
  // These folks are going to be used only for figuring out the current Kafka cluster topology.
  // They are not going to be used for real (produce/fetch/etc.) communication.
  for (const auto& bootstrap_server : bootstrap_servers_) {
    auto worker = std::make_shared<NodeWorker>(*this, deps_, mock_id, bootstrap_server.first, bootstrap_server.second);
    worker->init();
    all_workers_.push_back(worker);
    mock_id--;
  }

  // Start monitoring topology.
  topology_monitor_ = std::make_shared<TopologyMonitor>(*this, deps_);
  topology_monitor_->init();
  ENVOY_LOG(trace, "Context - init end");
}

void Context::registerBroker(const int32_t node_id, const std::string host, const int32_t port) {
  {
    absl::WriterMutexLock lock(&node_workers_mutex_);
    const auto it = real_workers_.find(node_id);
    if (real_workers_.end() != it) {
      // All right, this might be some black magic.
      // What if we get weird results from one of the brokers, indicating that host has moved?
      const auto worker = it->second;
      if (host != worker->host_ || port != worker->port_) {
        ENVOY_LOG(trace, "Context - strange box: {} = {}:{} vs {}:{}", node_id, host, port, worker->host_, worker->port_);
      }
    } else {
      ENVOY_LOG(trace, "Context - starting new worker: {} = {}:{}", node_id, host, port);
      const auto new_worker = std::make_shared<NodeWorker>(*this, deps_, node_id, host, port);
      new_worker->init();
      real_workers_[node_id] = new_worker;
      all_workers_.push_back(new_worker);
    }
  }
}

NodeAddress Context::getLeastUsedNode() const {
  return bootstrap_servers_[0];
}

// === NODE WORKER =================================================================================

NodeWorker::NodeWorker(Context& context, EnvoyDepsSharedPtr deps, int32_t id, std::string host, int32_t port): context_{context}, deps_{deps}, id_{id}, host_{host}, port_{port} {
}

NodeWorker::~NodeWorker() {
  ENVOY_LOG(trace, "NodeWorker {} {} {} - dtor", id_, host_, port_);
}

void NodeWorker::init() {
  if (!timer_) {
    ENVOY_LOG(trace, "NodeWorker {} {} {} - init", id_, host_, port_);
    const Event::TimerCb cb = [this]() -> void {
      doWork();
    };
    timer_ = deps_->dispatcher_.createTimer(cb);
    timer_->enableTimer(std::chrono::seconds(5));
  }
}

// Helper function.
template <typename T> void sendRequest(T request, Network::ClientConnectionPtr& connection) {
  Buffer::OwnedImpl buffer;
  RequestEncoder encoder = RequestEncoder{buffer};
  encoder.encode(request);
  connection->write(buffer, false);
}

void NodeWorker::doWork() {
  ENVOY_LOG(trace, "NodeWorker {} {} {} - working", id_, host_, port_);

  auto address = Network::Utility::parseInternetAddress(host_, port_, false);
  Upstream::HostSharedPtr host = std::make_shared<Upstream::HostImpl>(
      deps_->info_,
      address->logicalName(),
      address,
      nullptr,
      1,
      envoy::config::core::v3::Locality().default_instance(),
      envoy::config::endpoint::v3::Endpoint::HealthCheckConfig().default_instance(),
      0,
      envoy::config::core::v3::UNKNOWN);

  auto options = nullptr;
  auto transport_socket_options = nullptr;
  auto result = host->createConnection(deps_->dispatcher_, options, transport_socket_options);
  connection_ = std::move(result.connection_);

  NodeWorkerConnectionFilterSharedPtr filter = std::make_shared<NodeWorkerConnectionFilter>(*this);
  connection_->addFilter(filter);
  connection_->connect();

  const RequestHeader header = {3, 1, 0, "client-inside-envoy"};
  const MetadataRequest data = { absl::nullopt };
  using RequestUnderTest = Request<MetadataRequest>;

  const RequestUnderTest request = {header, data};
  filter->response_decoder_->expectResponse(0, 3, 1);

  sendRequest(request, connection_);

  timer_->enableTimer(std::chrono::seconds(5));
}

// === TOPOLOGY WORKER =============================================================================

void TopologyMonitor::init() {
  if (!timer_) {
    ENVOY_LOG(trace, "TopologyMonitor init");
    const Event::TimerCb cb = [this]() -> void {
      updateTopology();
    };
    timer_ = deps_->dispatcher_.createTimer(cb);
    timer_->enableTimer(std::chrono::seconds(5));
  }
}

void TopologyMonitor::updateTopology() {

  const NodeAddress node_address = context_.getLeastUsedNode();

  ENVOY_LOG(trace, "TopologyMonitor - {}", node_address.second);

  auto address = Network::Utility::parseInternetAddress(node_address.first, node_address.second, false);
  Upstream::HostSharedPtr host = std::make_shared<Upstream::HostImpl>(
      deps_->info_,
      address->logicalName(),
      address,
      nullptr,
      1,
      envoy::config::core::v3::Locality().default_instance(),
      envoy::config::endpoint::v3::Endpoint::HealthCheckConfig().default_instance(),
      0,
      envoy::config::core::v3::UNKNOWN);

  auto options = nullptr;
  auto transport_socket_options = nullptr;
  connection_ = host->createConnection(deps_->dispatcher_, options, transport_socket_options);

  auto& raw = connection_.connection_;
//  std::shared_ptr<ConnectionFilter> filter = std::make_shared<ConnectionFilter>(*this);
//  raw->addFilter(filter);
//  raw->addConnectionCallbacks(*this);
//  ENVOY_LOG(info, "connecting {}", node_address.second);
  raw->connect();
//  ENVOY_LOG(info, "connected {}: {}", node_address.second, raw->state());

//  const RequestHeader header = {3, 1, 0, "client-inside-envoy"};
//  const MetadataRequest data = { absl::nullopt };
//  using RequestUnderTest = Request<MetadataRequest>;

//  const RequestUnderTest request = {header, data};
//  filter->response_decoder_->expectResponse(0, 3, 1);

//  RequestWriter rw{raw};
//  rw.send(request);
  raw->close(Network::ConnectionCloseType::NoFlush);

  timer_->enableTimer(std::chrono::seconds(5));
}

///====== OLD THINGSSSS ============================================================================

void KafkaCluster::startPreInit() {
  ENVOY_LOG(info, "KafkaCluster - startPreInit");
  onPreInitComplete();
}

std::pair<Upstream::ClusterImplBaseSharedPtr, Upstream::ThreadAwareLoadBalancerPtr>
KafkaClusterFactory::createClusterWithConfig(
    const envoy::config::cluster::v3::Cluster& cluster,
    const envoy::config::cluster::kafka::KafkaClusterConfig& /* proto_config */,
    Upstream::ClusterFactoryContext& context,
    Server::Configuration::TransportSocketFactoryContextImpl& socket_factory_context,
    Stats::ScopePtr&& stats_scope) {

  if (!cluster.has_cluster_type() || Extensions::Clusters::ClusterTypes::get().Kafka != cluster.cluster_type().name()) {
    throw EnvoyException("Kafka cluster can only created with kafka cluster type.");
  }

  ENVOY_LOG(info, "KafkaClusterFactory - createClusterWithConfig");
  return std::make_pair(
      std::make_shared<KafkaCluster>(cluster, context, socket_factory_context, std::move(stats_scope)),
      nullptr
  );
}

REGISTER_FACTORY(KafkaClusterFactory, Upstream::ClusterFactory);

} // namespace Kafka
} // namespace Clusters
} // namespace Extensions
} // namespace Envoy
