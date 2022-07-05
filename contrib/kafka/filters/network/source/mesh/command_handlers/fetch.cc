#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch.h"

#include "contrib/kafka/filters/network/source/external/responses.h"

#include <tuple>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

FetchRequestHolder::FetchRequestHolder(AbstractRequestListener& filter, SharedConsumerManager& consumer_manager, const std::shared_ptr<Request<FetchRequest>> request): 
BaseInFlightRequest{filter}, consumer_manager_{consumer_manager}, request_{request} {
}

void FetchRequestHolder::startProcessing() { notifyFilter(); }

bool FetchRequestHolder::finished() const { return true; }

AbstractResponseSharedPtr FetchRequestHolder::computeAnswer() const {

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1000ms);

  ENVOY_LOG(info, "Fetch request received");
  std::ostringstream debug;

  const std::vector<FetchTopic> topics = request_->data_.topics_;
  FetchSpec fetches_requested;
  for (const auto topic : topics) {
    const std::string topic_name = topic.topic_;
    const std::vector<FetchPartition> partitions = topic.partitions_;
    for (const auto partition : partitions) {
      const int32_t partition_id = partition.partition_;
      ENVOY_LOG(trace, "Fetch for {}-{}", topic_name, partition_id);
      fetches_requested[topic_name].push_back(partition_id); // yay
      
      debug << topic_name << "-" << partition_id << ", "; // aaa
    }
  }

  ENVOY_LOG(info, "fetch: {} -> {}", fetches_requested.size(), debug.str());

  consumer_manager_.processFetches(fetches_requested);

  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int32_t throttle_time_ms = 0;
  std::vector<FetchableTopicResponse> responses;
  /* hack - no data for now */
  for (const auto& ft : topics) {
    std::vector<FetchResponseResponsePartitionData> partitions;
    for (const auto& ftp : ft.partitions_) {
      FetchResponseResponsePartitionData frpd = { ftp.partition_, 0, 0, absl::nullopt };
      partitions.push_back(frpd);
    }
    FetchableTopicResponse ftr = { ft.topic_, partitions, TaggedFields{} };
    responses.push_back(ftr);
  }
  
  const FetchResponse data = { throttle_time_ms, responses };
  return std::make_shared<Response<FetchResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
