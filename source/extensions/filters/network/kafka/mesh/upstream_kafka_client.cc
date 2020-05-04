#include "extensions/filters/network/kafka/mesh/upstream_kafka_client.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

KafkaProducerWrapper::KafkaProducerWrapper(
    Event::Dispatcher& dispatcher, Thread::ThreadFactory& thread_factory, const std::string& bootstrap_servers):
        dispatcher_{dispatcher} {

  std::unique_ptr<RdKafka::Conf> conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
  std::string errstr;
  if (conf->set("bootstrap.servers", bootstrap_servers, errstr) != RdKafka::Conf::CONF_OK) {
    ENVOY_LOG(warn, "set", errstr);
  }

  if (conf->set("dr_cb", this, errstr) != RdKafka::Conf::CONF_OK) {
    ENVOY_LOG(warn, "dr_cb", errstr);
  }

  producer_ = std::unique_ptr<RdKafka::Producer>(RdKafka::Producer::create(conf.get(), errstr));
  if (!producer_) {
    ENVOY_LOG(warn, "producer", errstr);
  }

  std::function<void()> thread_routine = [this]() -> void {
    checkDeliveryReports();
  };
  poller_thread_ = thread_factory.createThread(thread_routine);
}

RdKafka::ErrorCode KafkaProducerWrapper::send(
    const ProduceFinishCbSharedPtr origin, const std::string& topic, const int32_t partition, const absl::string_view key, const absl::string_view value) {
  {
    ENVOY_LOG(warn, "Sending {} value-bytes to [{}/{}] (data = {})", value.size(), topic, partition, reinterpret_cast<long>(value.data()));
    // No flags, we leave all the memory management to Envoy, as we will use address of value data in message callback to tell apart the requests.
    const int flags = 0;
    const void* key_data = key.data();
    void* value_data = const_cast<char*>(value.data());
    RdKafka::ErrorCode ec = producer_->produce(topic, partition, flags, value_data, value.size(), key_data, key.size(), 0, NULL, NULL);
    if (RdKafka::ERR_NO_ERROR == ec) {
      // We have succeeded with submitting data to producer, so we register a callback.
      unfinished_produce_requests_.push_back(origin);
    } else {
      ENVOY_LOG(debug, "Produce failure [{}] while sending {} value-bytes to [{}/{}]", ec, value.size(), topic, partition);
    }
    return ec;
  }
}

void KafkaProducerWrapper::checkDeliveryReports() {
  for (;;) {
    producer_->poll(-1); // We are going to wait indefinitely, returning when an event (message delivery) happens or producer is closed.
  }
}

void KafkaProducerWrapper::dr_cb(RdKafka::Message &message) {
  ENVOY_LOG(warn, "KafkaProducerWrapper - dr_cb: [{}] {}/{} -> {} (data = {})", message.err(), message.topic_name(), message.partition(), message.offset(), reinterpret_cast<long>(message.payload()));
  const DeliveryMemento memento = { message.payload(), message.err(), message.offset() };
  const Event::PostCb callback = [this, memento]() -> void {
    processDelivery(memento);
  };
  dispatcher_.post(callback);
}

void KafkaProducerWrapper::processDelivery(const DeliveryMemento& memento) {
  for (auto it = unfinished_produce_requests_.begin(); it != unfinished_produce_requests_.end(); ) {
    bool accepted = (*it)->accept(memento);
    if (accepted) {
      unfinished_produce_requests_.erase(it);
      break; // This is important - a single request can be mapped into multiple callbacks here.
    } else {
      ++it;
    }
  }
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
