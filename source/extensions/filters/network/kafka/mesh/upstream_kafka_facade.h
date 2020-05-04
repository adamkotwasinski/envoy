#pragma once

#include "envoy/thread/thread.h"
#include "common/common/logger.h"
#include "envoy/thread_local/thread_local.h"
#include "extensions/filters/network/kafka/mesh/upstream_kafka_client.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Provides thread-safe access to upstream Kafka clients.
 */
class UpstreamKafkaFacade: private Logger::Loggable<Logger::Id::kafka> {
public:
  UpstreamKafkaFacade(ThreadLocal::SlotAllocator& slot_allocator, Thread::ThreadFactory& thread_factory);

  KafkaProducerWrapper& getProducer(const std::string& cluster_name);

private:
  ThreadLocal::SlotPtr tls_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
