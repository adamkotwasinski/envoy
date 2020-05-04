#include "extensions/filters/network/kafka/mesh/upstream_kafka_facade.h"

#include <thread>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class ThreadLocalKafkaFacade: public ThreadLocal::ThreadLocalObject, private Logger::Loggable<Logger::Id::kafka> {
public:
  ThreadLocalKafkaFacade(UpstreamKafkaFacade&, Event::Dispatcher& dispatcher, Thread::ThreadFactory& thread_factory);

  KafkaProducerWrapper& getProducer(const std::string& cluster_name);

private:
  // Mutates 'cluster_to_kafka_client_'.
  KafkaProducerWrapper& registerNewProducer(const std::string& cluster_name);

  Event::Dispatcher& dispatcher_;
  Thread::ThreadFactory& thread_factory_;

  std::map<std::string, KafkaProducerWrapperPtr> cluster_to_kafka_client_;
};

ThreadLocalKafkaFacade::ThreadLocalKafkaFacade(UpstreamKafkaFacade&, Event::Dispatcher& dispatcher, Thread::ThreadFactory& thread_factory):
    dispatcher_{dispatcher}, thread_factory_{thread_factory} {

  ENVOY_LOG(warn, "ThreadLocalKafkaFacade - ctor");
}

KafkaProducerWrapper& ThreadLocalKafkaFacade::getProducer(const std::string& cluster_name) {
  const auto it = cluster_to_kafka_client_.find(cluster_name);
  // Return client already present or create new one and register it.
  return (cluster_to_kafka_client_.end() == it) ? registerNewProducer(cluster_name) : *(it->second);
}

std::string bootstrap(const std::string& cluster_name) {
  if (cluster_name.rfind("localkafka_m1", 0) == 0) {
    return "127.0.0.1:9092";
  } else {
    return "127.0.0.1:9093";
  }
}

KafkaProducerWrapper& ThreadLocalKafkaFacade::registerNewProducer(const std::string& cluster_name) {
  ENVOY_LOG(warn, "KafkaUpstreamProducerWrapper - Register new producer for cluster [{}] in thread [{}]", cluster_name, std::this_thread::get_id());
  KafkaProducerWrapperPtr new_producer = std::make_unique<KafkaProducerWrapper>(dispatcher_, thread_factory_, bootstrap(cluster_name));
  auto result = cluster_to_kafka_client_.emplace(cluster_name, std::move(new_producer));
  return *(result.first->second);
}

UpstreamKafkaFacade::UpstreamKafkaFacade(ThreadLocal::SlotAllocator& tls_allocator, Thread::ThreadFactory& thread_factory): tls_{tls_allocator.allocateSlot()} {
  ENVOY_LOG(warn, "ProducerFacade - ctor");
  ThreadLocal::Slot::InitializeCb cb =
    [this, &thread_factory](Event::Dispatcher& dispatcher) -> ThreadLocal::ThreadLocalObjectSharedPtr {
    return std::make_shared<ThreadLocalKafkaFacade>(*this, dispatcher, thread_factory);
  };
  tls_->set(cb);
}

// Return Producer instance that is local to given thread, via ThreadLocalKafkaFacade.
KafkaProducerWrapper& UpstreamKafkaFacade::getProducer(const std::string& cluster_name) {
  return tls_->getTyped<ThreadLocalKafkaFacade>().getProducer(cluster_name);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
