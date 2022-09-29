#include "contrib/kafka/filters/network/source/mesh/config.h"

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"
#include "envoy/stats/scope.h"

#include "envoy/event/dispatcher.h"
#include "envoy/event/timer.h"

#include <iostream>

#ifndef WIN32
#include "contrib/kafka/filters/network/source/mesh/fetch_purger.h"
#include "contrib/kafka/filters/network/source/mesh/fetch_purger_impl.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager_impl.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_config.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_facade.h"
#include "contrib/kafka/filters/network/source/mesh/filter.h"
#else
#include "envoy/common/exception.h"
#endif

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// The mesh filter doesn't do anything special, it just sets up the shared entities.
// Any extra configuration validation is done in UpstreamKafkaConfiguration constructor.
Network::FilterFactoryCb KafkaMeshConfigFactory::createFilterFactoryFromProtoTyped(
    const KafkaMeshProtoConfig& config, Server::Configuration::FactoryContext& context) {

#ifdef WIN32
  throw EnvoyException("Kafka mesh filter is not supported on Windows");
#else
  // Shared configuration (tells us where the upstream clusters are).
  const UpstreamKafkaConfigurationSharedPtr configuration =
      std::make_shared<UpstreamKafkaConfigurationImpl>(config);

  // Shared upstream facade (connects us to upstream Kafka clusters).
  const UpstreamKafkaFacadeSharedPtr upstream_kafka_facade =
      std::make_shared<UpstreamKafkaFacadeImpl>(*configuration, context.threadLocal(),
                                                context.api().threadFactory());

  // Manager for consumers shared across downstream connections
  // (connects us to upstream Kafka clusters).
  const SharedConsumerManagerSharedPtr shared_consumer_manager =
      std::make_shared<SharedConsumerManagerImpl>(*configuration, context.api().threadFactory());

  // Manages fetch request timeouts.
  const FetchPurgerSharedPtr fetch_purger = std::make_shared<FetchPurgerImpl>(context.threadLocal());

  // threadlocalX ma dostep do dispatchera
  // czyli dispatcher/worker thread
  // i w takim przypadku ten dispatcher tez jest skalowany per --concurrency
  // czyli my zarzadzamy cleaningiem

  return [configuration, upstream_kafka_facade,
          shared_consumer_manager, fetch_purger](Network::FilterManager& filter_manager) -> void {
    Network::ReadFilterSharedPtr filter = std::make_shared<KafkaMeshFilter>(
        *configuration, *upstream_kafka_facade, *shared_consumer_manager, *fetch_purger);
    filter_manager.addReadFilter(filter);
  };
#endif
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
