#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch.h"

#include "contrib/kafka/filters/network/source/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FetchRequestHolder::FetchRequestHolder(AbstractRequestListener& filter,
                                       SharedConsumerManager& consumer_manager,
                                       const std::shared_ptr<Request<FetchRequest>> request)
    : BaseInFlightRequest{filter}, consumer_manager_{consumer_manager}, request_{request} {}

void FetchRequestHolder::startProcessing() {
  ENVOY_LOG(info, "Fetch request received: CID={}", request_->request_header_.correlation_id_);

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
  consumer_manager_.processFetches(shared_from_this(), fetches_requested);

  // Corner case handling: ???
  if (finished()) {
    notifyFilter();
  }
}

bool FetchRequestHolder::receive(RdKafkaMessagePtr message) {
  const auto& header = request_->request_header_;
  ENVOY_LOG(info, "FRH receive {}: {}/{}", header.correlation_id_, message->partition(), message->offset() );
  messages_.push_back(std::move(message));
  return !isEligibleForSendingDownstream();
}

bool FetchRequestHolder::isEligibleForSendingDownstream() const {
  // FIXME this needs to be better
  return messages_.size() >= 1;
}

bool FetchRequestHolder::finished() const { 
  ENVOY_LOG(info, "checking finish for {}", request_->request_header_.correlation_id_);
  return isEligibleForSendingDownstream(); // FIXME inline iEFSD?
}

AbstractResponseSharedPtr FetchRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int32_t throttle_time_ms = 0;
  std::vector<FetchableTopicResponse> responses;

  ENVOY_LOG(info, "response to FR{} has {} records", header.correlation_id_, messages_.size());
  for (auto& message : messages_) {
    ENVOY_LOG(info, "record {}/{}", message->partition(), message->offset());
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
