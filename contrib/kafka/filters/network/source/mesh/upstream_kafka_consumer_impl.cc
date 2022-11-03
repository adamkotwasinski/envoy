#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class LibRdKafkaUtils2Impl : public LibRdKafkaUtils2 {

  // LibRdKafkaUtils2
  RdKafka::Conf::ConfResult setConfProperty(RdKafka::Conf& conf, const std::string& name,
                                            const std::string& value,
                                            std::string& errstr) const override {
    return conf.set(name, value, errstr);
  }

  // LibRdKafkaUtils2
  std::unique_ptr<RdKafka::KafkaConsumer> createConsumer(RdKafka::Conf* conf,
                                                         std::string& errstr) const override {
    return std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(conf, errstr));
  }

public:
  static const LibRdKafkaUtils2& getDefaultInstance() {
    CONSTRUCT_ON_FIRST_USE(LibRdKafkaUtils2Impl);
  }
};

RichKafkaConsumer::RichKafkaConsumer(StoreCb& store_cb,
                                     Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration)
    : RichKafkaConsumer(store_cb, thread_factory, topic, partition_count, configuration,
                        LibRdKafkaUtils2Impl::getDefaultInstance()){};

RichKafkaConsumer::RichKafkaConsumer(StoreCb& store_cb,
                                     Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration,
                                     const LibRdKafkaUtils2& utils)
    : store_cb_{store_cb}, topic_{topic} {

  // Create consumer configuration object.
  std::unique_ptr<RdKafka::Conf> conf =
      std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));

  std::string errstr;

  // Setup consumer custom properties.
  for (const auto& e : configuration) {
    ENVOY_LOG(info, "Setting consumer property {}={}", e.first, e.second);
    if (utils.setConfProperty(*conf, e.first, e.second, errstr) != RdKafka::Conf::CONF_OK) {
      throw EnvoyException(absl::StrCat("Could not set consumer property [", e.first, "] to [",
                                        e.second, "]:", errstr));
    }
  }

  // XXX
  if (utils.setConfProperty(*conf, "queued.max.messages.kbytes", "10", errstr) != RdKafka::Conf::CONF_OK) {
    throw EnvoyException(errstr);
  }
  if (utils.setConfProperty(*conf, "fetch.message.max.bytes", "1000", errstr) != RdKafka::Conf::CONF_OK) {
    throw EnvoyException(errstr);
  }

  // Finally, we create the producer.
  consumer_ = utils.createConsumer(conf.get(), errstr);
  if (!consumer_) {
    throw EnvoyException(absl::StrCat("Could not create consumer:", errstr));
  }
  
  for (auto pt = 0; pt < partition_count; ++pt) {
    RdKafkaTopicPartitionRawPtr topic_partition =
        RdKafka::TopicPartition::create(topic, pt, 0); // XXX (AK) initial offset???
    assignment_.push_back(topic_partition);
  }
  // XXX (AK) abstract out.
  consumer_->assign(assignment_);

  ENVOY_LOG(info, "Starting poller for topic [{}]", topic_);
  poller_thread_active_ = true;
  std::function<void()> thread_routine = [this]() -> void { pollContinuously(); };
  poller_thread_ = thread_factory.createThread(thread_routine);
}

RichKafkaConsumer::~RichKafkaConsumer() {
  ENVOY_LOG(info, "Closing Kafka consumer [{}]", topic_);

  poller_thread_active_ = false;
  poller_thread_->join();

  consumer_->unassign();
  consumer_->close();
  RdKafka::TopicPartition::destroy(assignment_);

  ENVOY_LOG(info, "Kafka consumer [{}] closed succesfully", topic_);
}

void RichKafkaConsumer::pollContinuously() {
  while (poller_thread_active_) {

    bool can_poll = store_cb_.waitUntilInterest(topic_, 2345); // XXX same problem as kafka-producer
    if (!can_poll) {
      // There is nothing to do, so we keep checking again - also we happen to check if we were closed.
      continue;
    }

    std::vector<InboundRecordSharedPtr> kafka_messages = receiveMessageBatch();
    if (0 != kafka_messages.size()) {
      for (auto& kafka_message : kafka_messages) {
        store_cb_.receive(kafka_message);
      }
    }

  }
  ENVOY_LOG(info, "Poller thread for consumer [{}] finished", topic_);
}

const static int32_t BUFFER_DRAIN_VOLUME = 4;

static InboundRecordSharedPtr copy(const RdKafka::Message& arg) {
  auto topic = arg.topic_name();
  auto partition = arg.partition();
  auto offset = arg.offset();
  return std::make_shared<InboundRecord>(topic, partition, offset);
}

std::vector<InboundRecordSharedPtr> RichKafkaConsumer::receiveMessageBatch() {
  // This message kicks off librdkafka consumer's Fetch requests and delivers a message.
  auto message = std::unique_ptr<RdKafka::Message>(consumer_->consume(1000)); // XXX what value should we pass here?
  switch (message->err()) {
    case RdKafka::ERR_NO_ERROR: {
      ENVOY_LOG(info, "Received message: {}-{}, offset={}", message->topic_name(), message->partition(), message->offset());
      std::vector<InboundRecordSharedPtr> result;
      result.push_back(copy(*message));

      // We got a message, there could be something left in the buffer, so we try to drain it by
      // consuming without waiting. See: https://github.com/edenhill/librdkafka/discussions/3897
      while (result.size() < BUFFER_DRAIN_VOLUME) {
        auto buffered_message = std::unique_ptr<RdKafka::Message>(consumer_->consume(0));
        if (RdKafka::ERR_NO_ERROR == buffered_message->err()) {
          // There was a message in the buffer.
          ENVOY_LOG(info, "Received buffered message: {}-{}, offset={}", buffered_message->topic_name(), buffered_message->partition(), buffered_message->offset());
          result.push_back(copy(*buffered_message));
        } else {
          // Buffer is empty / consumer is failing - there is nothing more to consume.
          break;
        }
      }
      return result;
    }
    case RdKafka::ERR__TIMED_OUT: {
      ENVOY_LOG(info, "Timed out in [{}]", topic_);
      return {};
    }
    default: {
      ENVOY_LOG(info, "Received other error: {} / {}", message->err(), RdKafka::err2str(message->err()));
      return {};
    }
  }
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
