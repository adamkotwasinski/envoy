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
  ENVOY_LOG(info, "Fetch request CID={} received in {}", request_->request_header_.correlation_id_, oss.str());

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

  //auto self_reference = shared_from_this();
  //consumer_manager_.processFetches(self_reference, fetches_requested);

  // XXX Make this conditional in finished?
  Event::TimerCb callback = [this]() -> void { 
    markFinishedByTimer();
  };
  timer_ = fetch_purger_.track(callback, 1234); 

  // Corner case handling: empty requested partition count, also other possible???
  if (finished()) {
    notifyFilter();
  }
  ENVOY_LOG(info, "Fetch request CID={} finished processing in {}", request_->request_header_.correlation_id_, oss.str());
}

void FetchRequestHolder::markFinishedByTimer() {
  ENVOY_LOG(info, "Time ran out for {}", request_->request_header_.correlation_id_);
  timed_out_ = true;
  notifyFilter();
}

bool FetchRequestHolder::receive(RdKafkaMessagePtr message) {
  const auto& header = request_->request_header_;
  ENVOY_LOG(info, "FRH receive CID{}: {}/{}", header.correlation_id_, message->partition(), message->offset() );
  {
    absl::MutexLock lock(&messages_mutex_);
    messages_.push_back(std::move(message));
  }
  return !isEligibleForSendingDownstream(); // this might be wrong
}

bool FetchRequestHolder::isEligibleForSendingDownstream() const {
  absl::MutexLock lock(&messages_mutex_);
  // FIXME this needs to be better
  return messages_.size() >= 1;
}

bool FetchRequestHolder::finished() const { 
  return timed_out_ || isEligibleForSendingDownstream();
}

AbstractResponseSharedPtr FetchRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int32_t throttle_time_ms = 0;
  std::vector<FetchableTopicResponse> responses;

  {
    absl::MutexLock lock(&messages_mutex_);
    ENVOY_LOG(info, "response to FR{} has {} records", header.correlation_id_, messages_.size());
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
