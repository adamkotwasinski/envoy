#include "extensions/filters/network/kafka/mesh/config.h"

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"
#include "envoy/stats/scope.h"

#include "extensions/filters/network/kafka/mesh/filter.h"

#include <typeinfo>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

Network::FilterFactoryCb KafkaMeshConfigFactory::createFilterFactoryFromProtoTyped(
    const KafkaMeshProtoConfig&, Server::Configuration::FactoryContext& context) {

  const auto cl = context.clusterManager().get("localkafka");
  ENVOY_LOG(warn, "cl {}", cl == nullptr);
  ENVOY_LOG(warn, "cl2 {}", typeid(cl).name());

  return [](Network::FilterManager& filter_manager) -> void {
    Network::ReadFilterSharedPtr filter = std::make_shared<KafkaMeshFilter>();
    filter_manager.addReadFilter(filter);
  };
}

/**
 * Static registration for the Kafka filter. @see RegisterFactory.
 */
REGISTER_FACTORY(KafkaMeshConfigFactory, Server::Configuration::NamedNetworkFilterConfigFactory);

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
