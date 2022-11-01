#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch.h"

#include "contrib/kafka/filters/network/source/external/responses.h"

#include "absl/synchronization/mutex.h"

#include <thread>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FetchRequestHolder::FetchRequestHolder(AbstractRequestListener& filter,
                                       SharedConsumerManager& consumer_manager,
                                       FetchPurger& fetch_purger,
                                       const std::shared_ptr<Request<FetchRequest>> request)
    : BaseInFlightRequest{filter}, consumer_manager_{consumer_manager}, fetch_purger_{fetch_purger}, request_{request} {}

void FetchRequestHolder::startProcessing() {
  const TopicToPartitionsMap requested_topics = interest();

  // Extreme corner case: Fetch request without topics to fetch.
  if (requested_topics.size() == 0) {
    absl::MutexLock lock(&state_mutex_);
    ENVOY_LOG(info, "Fetch request [{}] finished by the virtue of requiring nothing", debugId());
    markFinishedAndCleanup(false);
    notifyFilter();
    return; // Early return for degenerate request.
  }

  {
    absl::MutexLock lock(&state_mutex_);
    for (const auto& topic_and_partitions : requested_topics) {
      const std::string& topic_name = topic_and_partitions.first;
      for (const int32_t partition : topic_and_partitions.second) {
        // This makes sure that all requested KafkaPartitions are tracked,
        // so then output generation is simpler.
        messages_[{topic_name, partition}] = {};
      }
    }
  }

  const auto self_reference = shared_from_this();
  consumer_manager_.getRecordsOrRegisterCallback(self_reference);

  // XXX Make this conditional in finished?
  Event::TimerCb callback = [this]() -> void {
    markFinishedByTimer();
  };
  timer_ = fetch_purger_.track(callback, 1234); // XXX 1234!

  // XXX this might be better in markFinishedAndCleanup
  if (finished()) {
    notifyFilter();
  }
}

TopicToPartitionsMap FetchRequestHolder::interest() const {
  TopicToPartitionsMap result;
  const std::vector<FetchTopic>& topics = request_->data_.topics_;
  for (const FetchTopic& topic : topics) {
    const std::string topic_name = topic.topic_;
    const std::vector<FetchPartition> partitions = topic.partitions_;
    for (const FetchPartition& partition : partitions) {
      result[topic_name].push_back(partition.partition_);
    }
  }
  return result;
}

void FetchRequestHolder::markFinishedByTimer() {
  ENVOY_LOG(info, "Fetch request {} timed out", debugId());
  {
    absl::MutexLock lock(&state_mutex_);
    markFinishedAndCleanup(true);
  }
}

// XXX temporary solution only
constexpr int32_t MINIMAL_MSG_CNT = 3;

// This method is called by a Kafka-consumer thread (not Envoy-worker one).
Reply FetchRequestHolder::receive(RdKafkaMessagePtr message) {
  absl::MutexLock lock(&state_mutex_);
  if (!finished_) {
    const KafkaPartition kp = { message->topic_name(), message->partition() };
    messages_[kp].push_back(message);
    
    uint32_t current_messages = 0;
    for (const auto& e : messages_) {
      current_messages += e.second.size();
    }

    if (current_messages < MINIMAL_MSG_CNT) {
      ENVOY_LOG(info, "Fetch request {} processed message (and wants more {}): {}/{}", debugId(), current_messages, message->partition(), message->offset());
      return Reply::ACCEPTED_AND_WANT_MORE;
    } else {
      ENVOY_LOG(info, "Fetch request {} processed message (and is finished with {}): {}/{}", debugId(), current_messages, message->partition(), message->offset());
      // We have all we needed, we can finish processing.
      markFinishedAndCleanup(false);
      return Reply::ACCEPTED_AND_FINISHED;
    }
  }
  else {
    ENVOY_LOG(info, "Fetch request {} rejected message: {}/{}", debugId(), message->partition(), message->offset());
    return Reply::REJECTED;
  }
}

std::string FetchRequestHolder::debugId() const {
  std::ostringstream oss;
  oss << "[" << request_->request_header_.correlation_id_ << "]";
  return oss.str();
}

void FetchRequestHolder::markFinishedAndCleanup(bool unregister) {
  ENVOY_LOG(info, "Request {} marked as finished", debugId());
  finished_ = true;

  if (unregister) {
    const auto self_reference = shared_from_this();
    consumer_manager_.removeCallback(self_reference);
  }

  // Our request is ready and can be sent downstream.
  // However, the caller here could be a Kafka-consumer worker thread (not an Envoy worker one),
  // so we need to use dispatcher to notify the filter that we are finished.
  // Also, our timer could have kicked off after the filter has been destroyed, so we need to keep a valid reference.
  if (filter_active_) { // XXX this is thread-unsafe (filter's dtor does not run in the same thread as this method)
    filter_.onRequestReadyForAnswerThruDispatcher();
  }
}

bool FetchRequestHolder::finished() const { 
  absl::MutexLock lock(&state_mutex_);
  return finished_;
}

AbstractResponseSharedPtr FetchRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int32_t throttle_time_ms = 0;
  std::vector<FetchableTopicResponse> responses;
  {
    absl::MutexLock lock(&state_mutex_);

    int cnt = 0;
    for (const auto& e : messages_) {
      cnt += e.second.size();
    }
    ENVOY_LOG(info, "Response to Fetch request {} has {} records, finished = {}", debugId(), cnt, finished_);
    responses = processor_.transform(messages_);
  }

  const FetchResponse data = {throttle_time_ms, responses};
  return std::make_shared<Response<FetchResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
