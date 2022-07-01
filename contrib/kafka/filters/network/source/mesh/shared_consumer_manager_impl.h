#pragma once

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_config.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_client.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_client_impl.h" // FIXME ?

#include <vector>
#include <map>
#include <tuple>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Implements SCM interface by maintaining a collection of Kafka consumers on per-topic basis.
 * Maintains a message cache for messages that had no interest but might be requested later.
 */
class SharedConsumerManagerImpl: public SharedConsumerManager, private Logger::Loggable<Logger::Id::kafka> {
public:

    SharedConsumerManagerImpl(const UpstreamKafkaConfiguration& configuration);

    ~SharedConsumerManagerImpl() override;

    /**
     * Provides current position of consumer.
     */
    int64_t listOffsets(std::string topic, int32_t partition) override;

    /**
     *
     */
    void requestFetches(std::vector<FetchSpec> fetches_requested) override;

private:
    KafkaConsumer& getOrCreateConsumer(const std::string& topic);
    // Mutates 'topic_to_consumer_'.
    KafkaConsumer& registerNewConsumer(const std::string& topic);

    const UpstreamKafkaConfiguration& configuration_;
    std::map<std::string, KafkaConsumerPtr> topic_to_consumer_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy