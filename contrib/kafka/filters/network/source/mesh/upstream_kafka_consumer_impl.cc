#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// AAA!!!1111
std::string stringify(const std::vector<int32_t> arg) {
  std::ostringstream oss;
  oss << "[";
  if (!arg.empty()) {
    std::copy(arg.begin(), arg.end() - 1, std::ostream_iterator<int32_t>(oss, ","));
    oss << arg.back();
  }
  oss << "]";
  return oss.str();
}

class LibRdKafkaUtilsImpl2 : public LibRdKafkaUtils2 {

  // LibRdKafkaUtils
  RdKafka::Conf::ConfResult setConfProperty(RdKafka::Conf& conf, const std::string& name,
                                            const std::string& value,
                                            std::string& errstr) const override {
    return conf.set(name, value, errstr);
  }

  // LibRdKafkaUtils
  RdKafka::Conf::ConfResult setConfDeliveryCallback(RdKafka::Conf& conf,
                                                    RdKafka::DeliveryReportCb* dr_cb,
                                                    std::string& errstr) const override {
    return conf.set("dr_cb", dr_cb, errstr);
  }

  // LibRdKafkaUtils
  std::unique_ptr<RdKafka::Producer> createProducer(RdKafka::Conf* conf,
                                                    std::string& errstr) const override {
    return std::unique_ptr<RdKafka::Producer>(RdKafka::Producer::create(conf, errstr));
  }

  // LibRdKafkaUtils
  std::unique_ptr<RdKafka::KafkaConsumer> createConsumer(RdKafka::Conf* conf,
                                                         std::string& errstr) const override {
    return std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(conf, errstr));
  }

  // LibRdKafkaUtils
  RdKafka::Headers* convertHeaders(
      const std::vector<std::pair<absl::string_view, absl::string_view>>& headers) const override {
    RdKafka::Headers* result = RdKafka::Headers::create();
    for (const auto& header : headers) {
      const RdKafka::Headers::Header librdkafka_header = {
          std::string(header.first), header.second.data(), header.second.length()};
      const auto ec = result->add(librdkafka_header);
      // This should never happen ('add' in 1.7.0 does not return any other error codes).
      if (RdKafka::ERR_NO_ERROR != ec) {
        delete result;
        return nullptr;
      }
    }
    return result;
  }

  // LibRdKafkaUtils
  void deleteHeaders(RdKafka::Headers* librdkafka_headers) const override {
    delete librdkafka_headers;
  }

public:
  static const LibRdKafkaUtils2& getDefaultInstance() {
    CONSTRUCT_ON_FIRST_USE(LibRdKafkaUtilsImpl2);
  }
};

RichKafkaConsumer::RichKafkaConsumer(Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration)
    : RichKafkaConsumer(thread_factory, topic, partition_count, configuration,
                        LibRdKafkaUtilsImpl2::getDefaultInstance()){};

RichKafkaConsumer::RichKafkaConsumer(Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration,
                                     const LibRdKafkaUtils2& utils)
    : topic_{topic} {

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

  // Finally, we create the producer.
  consumer_ = utils.createConsumer(conf.get(), errstr);
  if (!consumer_) {
    throw EnvoyException(absl::StrCat("Could not create consumer:", errstr));
  }

  // XXX (AK) abstract out.
  for (auto pt = 0; pt < partition_count; ++pt) {
    RdKafkaTopicPartitionRawPtr topic_partition =
        RdKafka::TopicPartition::create(topic, pt, 0); // XXX (AK) initial offset???
    assignment_.push_back(topic_partition);
  }

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

void RichKafkaConsumer::registerInterest(RecordCbSharedPtr callback,
                                         const std::vector<int32_t>& partitions) {
  store_.registerInterest(callback, partitions);
}

void RichKafkaConsumer::pollContinuously() {
  while (poller_thread_active_) {
    if (store_.hasInterest()) { /* this should change 'what partitions are we interested in' */
      std::vector<RdKafkaMessagePtr> batch = receiveMessageBatch();
      if (0 != batch.size()) {
        store_.processNewDeliveries(batch);
      }
    } else {
      // There's no interest in any messages, just sleep for now.
      std::this_thread::sleep_for(std::chrono::seconds(1)); // XXX break on interest
    }
  }
  ENVOY_LOG(info, "Poller thread for consumer [{}] finished", topic_);
}

//const static int32_t BUFFER_DRAIN_VOLUME = 5;

std::vector<RdKafkaMessagePtr> RichKafkaConsumer::receiveMessageBatch() {
  // This message kicks off librdkafka consumer's Fetch requests and delivers a message.
  RdKafkaMessagePtr first_message = std::shared_ptr<RdKafka::Message>(consumer_->consume(1000));
  if (RdKafka::ERR_NO_ERROR == first_message->err()) {
    ENVOY_LOG(info, "Received message: {}-{}, offset={}", first_message->topic_name(), first_message->partition(), first_message->offset());
    std::vector<RdKafkaMessagePtr> result;
    result.push_back(first_message);

    /*
    // We got a message, there could be something left in the buffer, so we try to drain it by
    // consuming without waiting. See: https://github.com/edenhill/librdkafka/discussions/3897
    while (result.size() < BUFFER_DRAIN_VOLUME) {
      RdKafkaMessagePtr buffered_message = std::unique_ptr<RdKafka::Message>(consumer_->consume(0));
      if (RdKafka::ERR_NO_ERROR == buffered_message->err()) {
        // There was a message in the buffer.
        ENVOY_LOG(info, "received buffered message: pt={}, o={}", buffered_message->partition(),
                  buffered_message->offset());
        result.push_back(buffered_message);
      } else {
        // Buffer is empty / consumer is failing - there is nothing more to consume.
        break;
      }
    }
    */

    return result;
  } else {
    ENVOY_LOG(info, "Received error: {}", first_message->err());
    return {};
  }
}

bool Store::hasInterest() const {
  for (const auto& e : partition_to_callbacks_) {
    if (!e.second.empty()) {
      return true;
    }
  }
  return false;
}

void Store::registerInterest(RecordCbSharedPtr callback, const std::vector<int32_t>& partitions) {
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  ENVOY_LOG(info, "Registering callback {} for partitions {} in thread [{}]", callback->debugId(), stringify(partitions), oss.str());

  // drain 'messages_waiting_for_interest_' here???
  for (const int32_t partition : partitions) {
  }

  for (const int32_t partition : partitions) {
    auto& partition_callbacks = partition_to_callbacks_[partition];
    partition_callbacks.push_back(callback);
  }
}

void Store::processNewDeliveries(std::vector<RdKafkaMessagePtr> messages) {
  for (auto& message : messages) {
    processNewDelivery(message);
  }
}

void Store::processNewDelivery(RdKafkaMessagePtr message) {
  const int32_t partition = message->partition();
  auto& matching_callbacks = partition_to_callbacks_[partition];
  if (!matching_callbacks.empty()) {
    // Typical case: there is some interest in messages for given partition. Notify the callback and remove it.
    const auto callback = matching_callbacks[0];
    ENVOY_LOG(info, "Notifying callback {} about delivery for partition {}", callback->debugId(), partition);
    bool callback_accepted = callback->receive(message);
    if (callback_accepted) {
      ENVOY_LOG(info, "Callback {} accepted message, notifying and removing", callback->debugId());
      eraseCallback(callback); // XXX ???
    } else {
      ENVOY_LOG(info, "Callback {} rejected message", callback->debugId());
    }
  } 

  // We consume from all partitions, but there is noone interested in records present in this one.
  // Keep it for now.
  // ENVOY_LOG(info, "storing message (offset={}) for partition {}", message->offset(), partition);
  // message can be null now b/c of callback :(
  /*
  {
    absl::MutexLock lock(&data_mutex_);
    auto& stored_messages = messages_waiting_for_interest_[partition];
    stored_messages.push_back(message);
    // XXX if size() > x block OR throw ???
  }
  */

}

void Store::eraseCallback(RecordCbSharedPtr callback) {
  int removed = 0;
  for (auto& e : partition_to_callbacks_) {
    auto& partition_callbacks = e.second;
    int old_size = partition_callbacks.size();
    partition_callbacks.erase(std::remove(partition_callbacks.begin(), partition_callbacks.end(), callback), partition_callbacks.end());
    int new_size = partition_callbacks.size();
    removed += (old_size - new_size);
  }

  int remaining = 0;
  for (auto& e : partition_to_callbacks_) {
    remaining += e.second.size();
  }
  ENVOY_LOG(info, "Removed {} callback(s), there are {} left", removed, remaining);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
