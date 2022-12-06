#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager_impl.h"

#include <functional>

#include "source/common/common/fmt.h"

#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::string str(const KafkaPartition& arg) {
  std::ostringstream oss;
  oss << arg.first;
  oss << "-";
  oss << arg.second;
  return oss.str();
}

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

std::string stringify(const TopicToPartitionsMap& arg) {
  std::ostringstream oss;
  oss << "[";
  for (const auto& e : arg) {
    oss << e.first;
    oss << "=";
    oss << stringify(e.second);
    oss << ", ";
  }
  oss << "]";
  return oss.str();
}

SharedConsumerManagerImpl::SharedConsumerManagerImpl(
    const UpstreamKafkaConfiguration& configuration, Thread::ThreadFactory& thread_factory)
    : configuration_{configuration}, thread_factory_{thread_factory} {
}

SharedConsumerManagerImpl::~SharedConsumerManagerImpl() {
}

void SharedConsumerManagerImpl::getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback) {
  // For every fetch topic, figure out the upstream cluster,
  // create consumer if needed ...
  const TopicToPartitionsMap interest = callback->interest(); 
  for (const auto& fetch : interest) {
    const std::string& topic = fetch.first;
    getOrCreateConsumer(topic); // XXX this method should not be named 'get...'
  }
  // ... and start processing.
  store_.getRecordsOrRegisterCallback(callback);
}

KafkaConsumer& SharedConsumerManagerImpl::getOrCreateConsumer(const std::string& topic) {
  absl::MutexLock lock(&consumers_mutex_);
  const auto it = topic_to_consumer_.find(topic);
  // Return consumer already present or create new one and register it.
  return (topic_to_consumer_.end() == it) ? registerNewConsumer(topic) : *(it->second);
}

KafkaConsumer& SharedConsumerManagerImpl::registerNewConsumer(const std::string& topic) {
  ENVOY_LOG(info, "Creating consumer for topic [{}]", topic);
  // Compute which upstream cluster corresponds to the topic.
  const absl::optional<ClusterConfig> cluster_config =
      configuration_.computeClusterConfigForTopic(topic);
  if (!cluster_config) {
    throw EnvoyException(
        fmt::format("Could not compute upstream cluster configuration for topic [{}]", topic));
  }
  // Create the consumer and register it.
  KafkaConsumerPtr new_consumer =
      std::make_unique<RichKafkaConsumer>(store_, thread_factory_, topic, cluster_config->partition_count_,
                                          cluster_config->upstream_consumer_properties_);
  ENVOY_LOG(info, "Registering new Kafka consumer for topic [{}], consuming from cluster [{}]",
            topic, cluster_config->name_);
  auto result = topic_to_consumer_.emplace(topic, std::move(new_consumer));
  return *(result.first->second);
}

void SharedConsumerManagerImpl::removeCallback(const RecordCbSharedPtr& callback) {
  store_.removeCallback(callback);
}

// =============== STORE ==========================================================================================

bool Store::waitUntilInterest(const std::string& topic, const int32_t timeout_ms) const {
  auto store_has_interest = [this, &topic]() { return hasInterest(topic); };

  // Effectively this means "has an interest appeared within timeout".
  // If not, we let the user know so they could do something else instead of being infinitely blocked.
  bool can_poll = callbacks_mutex_.LockWhenWithTimeout(absl::Condition(&store_has_interest), absl::Milliseconds(timeout_ms));
  callbacks_mutex_.Unlock();
  return can_poll;
}

bool Store::hasInterest(const std::string& topic) const {
  for (const auto& e : partition_to_callbacks_) { // XXX to ma beznadziejny warning
    if (topic == e.first.first && !e.second.empty()) {
      return true;
    }
  }
  return false;
}

void Store::getRecordsOrRegisterCallback(const RecordCbSharedPtr& callback) {

  TopicToPartitionsMap requested = callback->interest();
  ENVOY_LOG(info, "Registering callback {} for {}", callback->debugId(), stringify(requested));

  bool fulfilled_at_startup = false;

  {
    absl::MutexLock lock(&messages_mutex_);
    for (const auto& topic_and_partitions : requested) {
      const std::string topic = topic_and_partitions.first;
      for (const int32_t partition : topic_and_partitions.second) {
        const KafkaPartition kp = { topic, partition };

        auto& stored_messages = messages_waiting_for_interest_[kp];
        if (0 != stored_messages.size()) {
          ENVOY_LOG(info, "Early notification for callback {}, as there are {} messages ready for {}", callback->debugId(), stored_messages.size(), str(kp));
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
      } /* for-partitions */
    } /* for-topic_and_partitions */
  } /* lock */

  if (!fulfilled_at_startup) {
    // Usual path: the request was not fulfilled at receive time (there were no buffered messages).
    // So we just register the callback.
    absl::MutexLock lock(&callbacks_mutex_);

    for (const auto& topic_and_partitions : requested) {
      const std::string topic = topic_and_partitions.first;
      for (const int32_t partition : topic_and_partitions.second) {
        const KafkaPartition kp = { topic, partition };
        auto& partition_callbacks = partition_to_callbacks_[kp];
        partition_callbacks.push_back(callback);
      }
    }
  } else {
    ENVOY_LOG(info, "No registration for callback {} due to successful early processing", callback->debugId());
  }
}

void Store::receive(InboundRecordSharedPtr message) { // XXX this api is inefficient, as we acquire lock PER MESSAGE (instead of batch)

  const KafkaPartition kafka_partition = {message->topic_name(), message->partition()};

  // Whether this message has been consumed by any of the callbacks.
  // Because then we can safely throw it away instead of storing.
  bool consumed_by_callback = false;

  {
    absl::MutexLock lock(&callbacks_mutex_);
    auto& callbacks = partition_to_callbacks_[kafka_partition];

    // Typical case: there is some interest in messages for given partition. Notify the callback and remove it.
    for (const auto& callback : callbacks) {
      Reply callback_status = callback->receive(message);
      switch (callback_status) {
        case Reply::ACCEPTED_AND_FINISHED: {
          consumed_by_callback = true;
          // A callback is finally satisfied, it will never want more messages.
          // XXX ouch ouch ouch removing while iterating over
          removeCallbackWithoutLocking(callback, partition_to_callbacks_); // Lock was acquired at the beggining of the block.
          break;
        }
        case Reply::ACCEPTED_AND_WANT_MORE: {
          consumed_by_callback = true;
          break;
        }
        case Reply::REJECTED: {
          break;
        }
      } /* switch */

      /* Some callback has taken the message - this is good, no more iterating. */
      if (consumed_by_callback) {
        break;
      }
    }
  }

  // Noone is interested in our message, so we are going to store it in a local cache.
  if (!consumed_by_callback) {
    absl::MutexLock lock(&messages_mutex_);
    auto& stored_messages = messages_waiting_for_interest_[kafka_partition];
    stored_messages.push_back(message); // XXX there should be buffer limits here

    // debug: count all present
    int total = 0;
    for (auto& e : messages_waiting_for_interest_) {
      total += e.second.size();
    }

    ENVOY_LOG(info, "Stored message [{}] for {}, there are now {} messages stored", message->offset(), str(kafka_partition), total);
  }
}

void Store::removeCallback(const RecordCbSharedPtr& callback) {
  absl::MutexLock lock(&callbacks_mutex_);
  removeCallbackWithoutLocking(callback, partition_to_callbacks_); // Lock was acquired a line above.
}

void Store::removeCallbackWithoutLocking(const RecordCbSharedPtr& callback, std::map<KafkaPartition, std::vector<RecordCbSharedPtr>>& partition_to_callbacks) {
  ENVOY_LOG(info, "Removing callback {}", callback->debugId());

  // absl::MutexLock lock(&callbacks_mutex_);
  // for (const auto& topic_and_partition : callback->interest()) {
  //   const std::string& topic = topic_and_partition.first;
  //   topic_to_consumer_[topic]->removeCallback(callback);
  // }

  int removed = 0;
  for (auto& e : partition_to_callbacks) {
    auto& partition_callbacks = e.second;
    int old_size = partition_callbacks.size();
    partition_callbacks.erase(std::remove(partition_callbacks.begin(), partition_callbacks.end(), callback), partition_callbacks.end());
    int new_size = partition_callbacks.size();
    removed += (old_size - new_size);
  }

  int remaining = 0;
  for (auto& e : partition_to_callbacks) {
    remaining += e.second.size();
  }

  ENVOY_LOG(info, "Removed callback {} in {} partitions, there are {} left", callback->debugId(), removed, remaining);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy