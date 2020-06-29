#include "extensions/filters/network/kafka/mesh/command.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

////////////////////////////////////////////////////////////////////////////////////////////////////
/////// API VERSIONS ///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

ApiVersionsRequestHolder::ApiVersionsRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<ApiVersionsRequest>> request):
    filter_{filter}, request_{request}
{
}

void ApiVersionsRequestHolder::invoke(UpstreamKafkaFacade&) {
  // Api Versions requests are immediately ready for answer.
  filter_.onRequestReadyForAnswer();
}

bool ApiVersionsRequestHolder::finished() const {
  return true;
}

AbstractResponseSharedPtr ApiVersionsRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  ResponseMetadata metadata = { header.api_key_, header.api_version_, header.correlation_id_ };

  ApiVersionsResponseKey produce_key = { 0, 5, 5 };
  ApiVersionsResponseKey metadata_key = { 3, 1, 1 };
  ApiVersionsResponse data = { 0, { produce_key, metadata_key } };
  return std::make_shared<Response<ApiVersionsResponse>>(metadata, data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////// METADATA ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

MetadataRequestHolder::MetadataRequestHolder(AbstractRequestListener& filter, const ClusteringConfiguration& clustering_configuration, const std::shared_ptr<Request<MetadataRequest>> request):
    filter_{filter}, clustering_configuration_{clustering_configuration}, request_{request}
{
}

// Metadata requests are immediately ready for answer (as they do not need to reach upstream).
void MetadataRequestHolder::invoke(UpstreamKafkaFacade&) {
  filter_.onRequestReadyForAnswer();
}

bool MetadataRequestHolder::finished() const {
  return true;
}

constexpr int32_t ENVOY_BROKER_ID = 0;
constexpr int32_t NO_ERROR = 0;

// Cornerstone of how the mesh-filter actually works.
// We pretend to be one-node Kafka cluster, with Envoy instance being the only member.
// What means all the Kafka future traffic will go through this instance.
AbstractResponseSharedPtr MetadataRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = { header.api_key_, header.api_version_, header.correlation_id_ };

  MetadataResponseBroker broker = {ENVOY_BROKER_ID, clustering_configuration_.advertised_host_, clustering_configuration_.advertised_port_};
  std::vector<MetadataResponseTopic> response_topics;
  if (request_->data_.topics_) {
    for (const auto topic : *(request_->data_.topics_)) {
      const std::string& topic_name = topic.name_;
      std::vector<MetadataResponsePartition> topic_partitions;
      const absl::optional<ClusterConfig> cluster_config = clustering_configuration_.computeClusterConfigForTopic(topic_name);
      if (!cluster_config) {
        // Someone is requesting topics that are not known to our configuration.
        // So we do not attach any metadata, this will cause clients failures downstream as they will never be able to get metadata for these topics.
        continue;
      }
      for (int32_t partition_id = 0; partition_id < cluster_config->partition_count_; ++partition_id) {
        // Every partition is hosted by this proxy-broker.
        MetadataResponsePartition partition = { NO_ERROR, partition_id, broker.node_id_, {broker.node_id_}, {broker.node_id_}};
        topic_partitions.push_back(partition);
      }
      MetadataResponseTopic response_topic = { NO_ERROR, topic_name, false, topic_partitions};
      response_topics.push_back(response_topic);
    }
  }
  MetadataResponse data = { {broker}, broker.node_id_, response_topics};
  return std::make_shared<Response<MetadataResponse>>( metadata, data );
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////// PRODUCE ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

ProduceRequestHolder::ProduceRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<ProduceRequest>> request):
    filter_{filter}, request_{request}
{
  for (auto const& topic_data : request_->data_.topics_) {
    for (auto const& partition_data : topic_data.partitions_) {
      if (partition_data.records_) {
        const auto footmarks = computeFootmarks(topic_data.name_, partition_data.partition_index_, *(partition_data.records_));
        footmarks_.insert(footmarks_.end(), footmarks.begin(), footmarks.end());
      }
    }
  }
  expected_responses_ = footmarks_.size();
}

absl::string_view comsumeBytes(absl::string_view& input) {
  VarInt32Deserializer length_deserializer;
  length_deserializer.feed(input);
  const int32_t length = length_deserializer.get();
  if (length >= 0) {
    const absl::string_view result = { input.data(), static_cast<absl::string_view::size_type>(length) };
    input = { input.data() + length, input.length() - length };
    return result;
  } else {
    return {};
  }
}

std::vector<ProduceRequestHolder::RecordFootmark> ProduceRequestHolder::computeFootmarks(const std::string& topic, const int32_t partition, const Bytes& records) {
  // org.apache.kafka.common.record.DefaultRecordBatch.writeHeader(ByteBuffer, long, int, int, byte, CompressionType, TimestampType, long, long, long, short, int, boolean, boolean, int, int)
  const char* ptr = reinterpret_cast<const char*>(records.data());
  absl::string_view sv = { ptr, records.size() };

  unsigned int step = 8 + 4 + 4;
  if (sv.length() < step) {
    ENVOY_LOG(error, "bad data");
    return {};
  }
  sv = { sv.data() + step, sv.length() - step };

  Int8Deserializer magic;
  magic.feed(sv);

  if (magic.ready()) {
    int8_t m = magic.get();
    if (2 != m) {
      ENVOY_LOG(warn, "magic not equal to 2: {}", m);
      return {};
    }
  }

  unsigned int step2 = 4 + 2 + 4 + 8 + 8 + 8 + 2 + 4;
  if (sv.length() < step2) {
    ENVOY_LOG(error, "bad data");
    return {};
  }
  sv = { sv.data() + step2, sv.length() - step2 };

  Int32Deserializer count_des;
  count_des.feed(sv);
  const int32_t record_count = count_des.get();
  ENVOY_LOG(trace, "found {} records in records byte-array", record_count);

  std::vector<ProduceRequestHolder::RecordFootmark> result;
  while (!sv.empty()) {

    // org.apache.kafka.common.record.DefaultRecord.writeTo(DataOutputStream, int, long, ByteBuffer, ByteBuffer, Header[])

    VarInt32Deserializer length;
    length.feed(sv);
    const int32_t len = length.get();
    ENVOY_LOG(trace, "record len = {}", len);

    const absl::string_view expected_end_of_record = { sv.data() + len, sv.length() - len };

    Int8Deserializer attributes;
    attributes.feed(sv);
    VarInt64Deserializer tsDelta;
    tsDelta.feed(sv);
    VarUInt32Deserializer offsetDelta;
    offsetDelta.feed(sv);

    absl::string_view key = comsumeBytes(sv);
    absl::string_view value = comsumeBytes(sv);

    VarInt32Deserializer headers_count_deserializer;
    headers_count_deserializer.feed(sv);
    const int32_t headers_count = headers_count_deserializer.get();
    if (headers_count < 0) {
      // boom
    }
    for (int32_t i = 0; i < headers_count; ++i) {
      comsumeBytes(sv); // header key
      comsumeBytes(sv); // header value
    }

    ENVOY_LOG(trace, "key = [{}], value = [{}]", key, value);

    if (sv != expected_end_of_record) {
      ENVOY_LOG(warn, "they differ {} {}", sv.length(), expected_end_of_record.length());
      return {};
    }

    result.emplace_back(topic, partition, key, value);
  }
  return result;
}

void ProduceRequestHolder::invoke(UpstreamKafkaFacade& kafka_facade) {
  for (auto& fm : footmarks_) {
    KafkaProducerWrapper& producer = kafka_facade.getProducerForTopic(fm.topic_);
    producer.send(shared_from_this(), fm.topic_, fm.partition_, fm.key_, fm.value_);
  }
}

bool ProduceRequestHolder::finished() const {
  return 0 == expected_responses_;
}

bool ProduceRequestHolder::accept(const DeliveryMemento& memento) {
  ENVOY_LOG(trace, "ProduceRequestHolder - accept: {}/{}", memento.error_code_, memento.offset_);
  for (auto& footmark : footmarks_) {
    if (footmark.value_.data() == memento.data_) {
      // We have matched the downstream request that matches our confirmation from upstream Kafka.
      ENVOY_LOG(trace, "ProduceRequestHolder - accept - match found for {}", reinterpret_cast<long>(memento.data_));
      footmark.error_code_ = memento.error_code_;
      footmark.saved_offset_ = memento.offset_;
      --expected_responses_;
      if (finished()) {
        // All footmarks had their responses matched.
        // We can notify the filter to check if it can send another response.
        notifyFilter();
      }
      return true;
    }
  }
  return false;
}

void ProduceRequestHolder::notifyFilter() {
  filter_.onRequestReadyForAnswer();
}

AbstractResponseSharedPtr ProduceRequestHolder::computeAnswer() const {

  // Header.
  const RequestHeader& rh = request_->request_header_;
  ResponseMetadata metadata = { rh.api_key_, rh.api_version_, rh.correlation_id_ };

  // Real answer.
  using ErrorCodeAndOffset = std::pair<int16_t, uint32_t>;
  std::map<std::string, std::map<int32_t, ErrorCodeAndOffset>> topic_to_partition_responses;
  for (const auto& footmark : footmarks_) {
    auto& partition_map = topic_to_partition_responses[footmark.topic_];
    auto it = partition_map.find(footmark.partition_);
    if (it == partition_map.end()) {
      partition_map[footmark.partition_] = { footmark.error_code_, footmark.saved_offset_ };
    } else {
      // Proxy logic - aggregating multiple upstream answers into single downstream answer.
      // Let's fail if anything fails, otherwise use the lowest offset (like Kafka would have done).
      ErrorCodeAndOffset& curr = it->second;
      if (RdKafka::ErrorCode::ERR_NO_ERROR == curr.first) {
        curr.first = footmark.error_code_;
        curr.second = std::min(curr.second, footmark.saved_offset_);
      }
    }
  }

  std::vector<TopicProduceResponse> topic_responses;
  for (const auto& topic_entry : topic_to_partition_responses) {
    std::vector<PartitionProduceResponse> partition_responses;
    for (const auto& partition_entry : topic_entry.second) {
      const int32_t& partition = partition_entry.first;
      const int16_t& error_code = partition_entry.second.first;
      const int64_t& offset = partition_entry.second.second;
      partition_responses.emplace_back(partition, error_code, offset);
    }
    const std::string& topic = topic_entry.first;
    topic_responses.emplace_back(topic, partition_responses);
  }

  ProduceResponse data = { topic_responses, 0 };
  return std::make_shared<Response<ProduceResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
