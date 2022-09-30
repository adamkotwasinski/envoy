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
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  ENVOY_LOG(info, "Fetch request [{}] received in thread [{}]", request_->request_header_.correlation_id_, oss.str());

  const std::vector<FetchTopic>& topics = request_->data_.topics_;
  FetchSpec fetches_requested;
  for (const auto& topic : topics) {
    const std::string topic_name = topic.topic_;
    const std::vector<FetchPartition> partitions = topic.partitions_;
    for (const auto partition : partitions) {
      const int32_t partition_id = partition.partition_;
      fetches_requested[topic_name].push_back(partition_id);
    }
  }

  auto self_reference = shared_from_this();
  consumer_manager_.registerFetchCallback(self_reference, fetches_requested);

  // XXX Make this conditional in finished?
  Event::TimerCb callback = [this]() -> void { 
    markFinishedByTimer();
  };
  timer_ = fetch_purger_.track(callback, 1234);

  // Extreme corner case: Fetch request without topics to fetch.
  if (0 == fetches_requested.size()) {
    absl::MutexLock lock(&state_mutex_);
    ENVOY_LOG(info, "Fetch request [{}] finished by the virtue of requiring nothing", debugId());
    markFinishedAndCleanup();
  } //XXX to powinno byc w wielkim ifie ze wczesnym return

  if (finished()) {
    notifyFilter();
  }
}

void FetchRequestHolder::markFinishedByTimer() {
  ENVOY_LOG(info, "Fetch request {} timed out", debugId());
  {
    absl::MutexLock lock(&state_mutex_);
    markFinishedAndCleanup();
  }
  notifyFilter();
}

// Remember this method is called by a non-Envoy thread.
bool FetchRequestHolder::receive(RdKafkaMessagePtr message) {
  {
    absl::MutexLock lock(&state_mutex_);
    if (!finished_) {
      ENVOY_LOG(info, "Fetch request {} accepted message: {}/{}", debugId(), message->partition(), message->offset());

      messages_.push_back(std::move(message));

      // XXX dyskusyjne
      markFinishedAndCleanup();
      //notifyFilterThruDispatcher();

      return true;
    }
    else {
      ENVOY_LOG(info, "Fetch request {} rejected message: {}/{}", debugId(), message->partition(), message->offset());
      return false;
    }
  }
}

std::string FetchRequestHolder::debugId() const {
  std::ostringstream oss;
  oss << "[" << request_->request_header_.correlation_id_ << "]";
  return oss.str();
}

int32_t FetchRequestHolder::id() const {
  return request_->request_header_.correlation_id_;
}

void FetchRequestHolder::markFinishedAndCleanup() {
  ENVOY_LOG(info, "Request {} marked as finished", debugId());
  finished_ = true;
  //auto self_reference = shared_from_this();
  //consumer_manager_.unregisterFetchCallback(self_reference);
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
    ENVOY_LOG(info, "Response to Fetch request {} has {} records, finished = {}", debugId(), messages_.size(), finished_);
    processor_.transform(messages_);
  }

  /* hack - no data for now */
  for (const auto& ft : request_->data_.topics_) {
    std::vector<FetchResponseResponsePartitionData> partitions;
    for (const auto& ftp : ft.partitions_) {
      FetchResponseResponsePartitionData frpd = {ftp.partition_, 0, 0, absl::nullopt};
      partitions.push_back(frpd);
    }
    FetchableTopicResponse ftr = {ft.topic_, partitions, TaggedFields{}};
    responses.push_back(ftr);
  }

  const FetchResponse data = {throttle_time_ms, responses};
  return std::make_shared<Response<FetchResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
