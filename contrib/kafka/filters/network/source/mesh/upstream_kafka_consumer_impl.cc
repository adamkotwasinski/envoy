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

RichKafkaConsumer::RichKafkaConsumer(Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration)
    : RichKafkaConsumer(thread_factory, topic, partition_count, configuration,
                        LibRdKafkaUtils2Impl::getDefaultInstance()){};

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

void RichKafkaConsumer::getRecordsOrRegisterCallback(RecordCbSharedPtr callback,
                                                     const std::vector<int32_t>& partitions) {

  store_.getRecordsOrRegisterCallback(callback, partitions);
}

void RichKafkaConsumer::pollContinuously() {
  while (poller_thread_active_) {
    if (store_.hasCallbacks()) { // There should be a partition check here.
      std::vector<RdKafkaMessagePtr> kafka_messages = receiveMessageBatch();
      if (0 != kafka_messages.size()) {
        for (auto& kafka_message : kafka_messages) {
          store_.processNewDelivery(kafka_message);
        }
      }
    } else {
      // There's no interest in any messages, just sleep for now.
      std::this_thread::sleep_for(std::chrono::seconds(1)); // XXX this should not be a sleep, we should sleep on condition "there are callbacks"
    }
  }
  ENVOY_LOG(info, "Poller thread for consumer [{}] finished", topic_);
}

const static int32_t BUFFER_DRAIN_VOLUME = 5;

std::vector<RdKafkaMessagePtr> RichKafkaConsumer::receiveMessageBatch() {
  // This message kicks off librdkafka consumer's Fetch requests and delivers a message.
  RdKafkaMessagePtr message = std::shared_ptr<RdKafka::Message>(consumer_->consume(1000));
  switch (message->err()) {
    case RdKafka::ERR_NO_ERROR: {
      ENVOY_LOG(info, "Received message: {}-{}, offset={}", message->topic_name(), message->partition(), message->offset());
      std::vector<RdKafkaMessagePtr> result;
      result.push_back(message);

      // We got a message, there could be something left in the buffer, so we try to drain it by
      // consuming without waiting. See: https://github.com/edenhill/librdkafka/discussions/3897
      while (result.size() < BUFFER_DRAIN_VOLUME) {
        RdKafkaMessagePtr buffered_message = std::unique_ptr<RdKafka::Message>(consumer_->consume(0));
        if (RdKafka::ERR_NO_ERROR == buffered_message->err()) {
          // There was a message in the buffer.
          ENVOY_LOG(info, "Received buffered message: {}-{}, offset={}", buffered_message->topic_name(), buffered_message->partition(), buffered_message->offset());
          result.push_back(buffered_message);
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

// === STORE =================================================================================================

bool Store::hasCallbacks() const {
  for (const auto& e : partition_to_callbacks_) {
    if (!e.second.empty()) {
      return true;
    }
  }
  return false;
}

void Store::getRecordsOrRegisterCallback(RecordCbSharedPtr callback, const std::vector<int32_t>& partitions) {
  ENVOY_LOG(info, "Registering callback {} for partitions {}", callback->debugId(), stringify(partitions));

  bool fulfilled_at_startup = false;

  {
    absl::MutexLock lock(&data_mutex_);
    for (const int32_t partition : partitions) {

      auto& stored_messages = messages_waiting_for_interest_[partition];

      if (0 != stored_messages.size()) {
        ENVOY_LOG(info, "Early notification for callback {}, as there are {} messages ready", callback->debugId(), stored_messages.size());
      }

      for (auto it = stored_messages.begin(); it != stored_messages.end();) {
        Reply callback_status = callback->receive(*it);
        bool callback_finished;
        switch (callback_status) {
          case Reply::ACCEPTED_AND_FINISHED: {
            callback_finished = true;
            it = stored_messages.erase(it);
            break;
          }
          case Reply::ACCEPTED_AND_WANT_MORE: {
            callback_finished = false;
            it = stored_messages.erase(it);
            break;
          }
          case Reply::REJECTED: {
            callback_finished = true;
            break;
          }
        } /* switch */
        if (callback_finished) {
          fulfilled_at_startup = true;
          break; // Callback does not want any messages anymore.
        }
      } /* for-messages */

    }
  }

  if (!fulfilled_at_startup) {
    // Usual path: the request was not fulfilled at receive time (there were no buffered messages).
    // So we just register the callback.
    absl::MutexLock lock(&callbacks_mutex_);
    for (const int32_t partition : partitions) {
      auto& partition_callbacks = partition_to_callbacks_[partition];
      partition_callbacks.push_back(callback);
    }
  } else {
    ENVOY_LOG(info, "No registration for callback {} due to successful early processing", callback->debugId());
  }
}

void Store::processNewDelivery(RdKafkaMessagePtr message) {
  const int32_t partition = message->partition();
  auto& matching_callbacks = partition_to_callbacks_[partition];
  bool consumed = false;

  // Typical case: there is some interest in messages for given partition. Notify the callback and remove it.
  if (!matching_callbacks.empty()) {
    const auto callback = matching_callbacks[0]; // FIXME this should be a for loop across all callbacks, otherwise we are not multithreaded
    Reply callback_status = callback->receive(message);
    switch (callback_status) {
      case Reply::ACCEPTED_AND_FINISHED: {
        consumed = true;
        // A callback is finally satisfied, it will never want more messages.
        // XXX do we need to do this here? or maybe CB should unregister itself?
        removeCallback(callback);
        break;
      }
      case Reply::ACCEPTED_AND_WANT_MORE: {
        consumed = true;
        break;
      }
      case Reply::REJECTED: {
        break;
      }
    }
  }

  // Noone is interested in our message, so we are going to store it in a local cache.
  if (!consumed) {
    absl::MutexLock lock(&data_mutex_);
    auto& stored_messages = messages_waiting_for_interest_[partition];
    stored_messages.push_back(message); // XXX there should be buffer limits here

    // debug: count all present
    int total = 0;
    for (auto& e : messages_waiting_for_interest_) {
      total += e.second.size();
    }

    ENVOY_LOG(info, "Stored message [{}] for partition {}, there are now {} messages stored", message->offset(), partition, total);
  }
}

void Store::removeCallback(RecordCbSharedPtr callback) {
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
