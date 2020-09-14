#include "extensions/filters/network/kafka/mesh/command_handlers/produce.h"

#include "extensions/filters/network/kafka/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::vector<RecordFootmark>
RecordExtractorImpl::computeFootmarks(const std::vector<TopicProduceData>& data) const {
  std::vector<RecordFootmark> result;
  for (auto const& topic_data : data) {
    for (auto const& partition_data : topic_data.partitions_) {
      if (partition_data.records_) {
        const auto topic_result = computeFootmarksForTopic(
            topic_data.name_, partition_data.partition_index_, *(partition_data.records_));
        result.insert(result.end(), topic_result.begin(), topic_result.end());
      }
    }
  }
  return result;
}

std::vector<RecordFootmark>
RecordExtractorImpl::computeFootmarksForTopic(const std::string& topic, const int32_t partition,
                                              const Bytes& bytes) const {

  // org.apache.kafka.common.record.DefaultRecordBatch.writeHeader(ByteBuffer, long, int, int, byte,
  // CompressionType, TimestampType, long, long, long, short, int, boolean, boolean, int, int)
  absl::string_view data = { reinterpret_cast<const char*>(bytes.data()) , bytes.size()};

  // Fields common to any records payload. Magic will follow.
  const unsigned int common_fields_size = /* BaseOffset */ 8 + /* Length */ 4 + /* PartitionLeaderEpoch */ 4;
  if (data.length() < common_fields_size) {
    // Badly formatted record batch (underflow).
    return {};
  }
  // Let's skip these common fields.
  data = {data.data() + common_fields_size, data.length() - common_fields_size};

  // Extract magic.
  // Magic tells us what is the format of records present in the byte array.
  Int8Deserializer magic_deserializer;
  magic_deserializer.feed(data);
  if (magic_deserializer.ready()) {
    int8_t magic = magic_deserializer.get();
    if (2 == magic) {
      // Magic format introduced around Kafka 1.0.0 and still used with Kafka 2.4.
      // We can extract the records out of the record batch.
      return extractRecordsOutOfBatchWithMagicEqualTo2(topic, partition, data);
    } else {
      // Old client sending old magic, or Apache Kafka introducing new magic.
      return {};
    }
  } else {
    // Badly formatted record data (underflow).
    return {};
  }
}

// Helper function to get the data (key, value) out of record.
absl::string_view comsumeBytes(absl::string_view& input) {
  VarInt32Deserializer length_deserializer;
  length_deserializer.feed(input);
  const int32_t length = length_deserializer.get();
  // Length can be negative (null value was published by client).
  if (length >= 0) {
    const absl::string_view result = {input.data(),
                                      static_cast<absl::string_view::size_type>(length)};
    input = {input.data() + length, input.length() - length};
    return result;
  } else {
    return {};
  }
}

class FirstFields : public CompositeDeserializerWith8Delegates<std::vector<int64_t>,
Int32Deserializer,
Int16Deserializer,
Int32Deserializer,
Int64Deserializer,
Int64Deserializer,
Int64Deserializer,
Int16Deserializer,
Int32Deserializer> {};

std::vector<RecordFootmark> RecordExtractorImpl::extractRecordsOutOfBatchWithMagicEqualTo2(const std::string& topic,
                                                               const int32_t partition,
                                                               absl::string_view data) const {

  // Not going to reuse the information in these fields, because we are going to republish.
  unsigned int ignored_fields_size = /* CRC */ 4 + /* Attributes */ 2 + /* LastOffsetDelta */ 4 +
                       /* FirstTimestamp */ 8 + /* MaxTimestamp */ 8 + /* ProducerId */ 8 +
                       /* ProducerEpoch */ 2 + /* BaseSequence */ 4;

  // if (data.length() < ignored_fields_size) {
  //   // Badly formatted record batch (underflow).
  //   return {};
  // }
  // data = {data.data() + ignored_fields_size, data.length() - ignored_fields_size};

  FirstFields ff;
  ff.feed(data);
  if (!ff.ready()) {
    // Badly formatted record batch (underflow).
    return {};
  }

  // Number of records (we are still going to loop over them).
  Int32Deserializer count_deserializer;
  count_deserializer.feed(data);

  if (!count_deserializer.ready()) {
    // Badly formatted record batch (underflow).
    return {};
  }
  const int32_t record_count = count_deserializer.get();
  if (record_count < 0) {
    // Badly formatted record batch (negative number of records).
    return {};
  }

  // We have managed to consume all the fancy bytes, now it's time to get to records.

  std::vector<RecordFootmark> result;
  while (!data.empty()) {
    const absl::optional<RecordFootmark> record = extractRecord(topic, partition, data);
    if (record) {
      result.push_back(*record);
    } else {
      // Badly formatted record (cannot trust anything in record array).
      return {};
    }
  }
  return result;
}

absl::optional<RecordFootmark> RecordExtractorImpl::extractRecord(const std::string& topic, const int32_t partition, absl::string_view& data) const {
  // org.apache.kafka.common.record.DefaultRecord.writeTo(DataOutputStream, int, long, ByteBuffer, ByteBuffer, Header[])

  VarInt32Deserializer length;
  length.feed(data);
  const int32_t len = length.get();

  const absl::string_view expected_end_of_record = {data.data() + len, data.length() - len};

  Int8Deserializer attributes;
  attributes.feed(data);
  VarInt64Deserializer tsDelta;
  tsDelta.feed(data);
  VarUInt32Deserializer offsetDelta;
  offsetDelta.feed(data);

  absl::string_view key = comsumeBytes(data);
  absl::string_view value = comsumeBytes(data);

  VarInt32Deserializer headers_count_deserializer;
  headers_count_deserializer.feed(data);
  const int32_t headers_count = headers_count_deserializer.get();
  if (headers_count < 0) {
    // boom
  }
  for (int32_t i = 0; i < headers_count; ++i) {
    comsumeBytes(data); // header key
    comsumeBytes(data); // header value
  }

  if (data == expected_end_of_record) {
    // We have consumed everything nicely.
    return { RecordFootmark{ topic, partition, key, value } };
  } else {
    return {};
  }
}

ProduceRequestHolder::ProduceRequestHolder(AbstractRequestListener& filter,
                                           const std::shared_ptr<Request<ProduceRequest>> request)
    : ProduceRequestHolder{filter, RecordExtractorImpl{}, request} {};

ProduceRequestHolder::ProduceRequestHolder(AbstractRequestListener& filter,
                                           const RecordExtractor& record_extractor,
                                           const std::shared_ptr<Request<ProduceRequest>> request)
    : BaseInFlightRequest{filter}, request_{request} {
  footmarks_ = record_extractor.computeFootmarks(request_->data_.topics_);
  expected_responses_ = footmarks_.size();
}

void ProduceRequestHolder::invoke(UpstreamKafkaFacade& kafka_facade) {
  for (auto& fm : footmarks_) {
    RecordSink& producer = kafka_facade.getProducerForTopic(fm.topic_);
    producer.send(shared_from_this(), fm.topic_, fm.partition_, fm.key_, fm.value_);
  }
  // Corner case handling:
  // If we ever receive produce request without records, we need to notify the filter we are ready,
  // because otherwise no notification will ever come from the real Kafka producer.
  if (0 == expected_responses_) {
    notifyFilter();
  }
}

bool ProduceRequestHolder::finished() const { return 0 == expected_responses_; }

bool ProduceRequestHolder::accept(const DeliveryMemento& memento) {
  ENVOY_LOG(warn, "ProduceRequestHolder - accept: {}/{}", memento.error_code_, memento.offset_);
  for (auto& footmark : footmarks_) {
    if (footmark.value_.data() == memento.data_) {
      // We have matched the downstream request that matches our confirmation from upstream Kafka.
      ENVOY_LOG(trace, "ProduceRequestHolder - accept - match found for {} in request {}",
                reinterpret_cast<long>(memento.data_), request_->request_header_.correlation_id_);
      footmark.error_code_ = memento.error_code_;
      footmark.saved_offset_ = memento.offset_;
      --expected_responses_;
      if (finished()) {
        // All elements had their responses matched.
        // We can notify the filter to check if it can send another response.
        ENVOY_LOG(warn, "ProduceRequestHolder - accept - notifying filter for {}",
                  request_->request_header_.correlation_id_);
        notifyFilter();
      }
      return true;
    }
  }
  return false;
}

AbstractResponseSharedPtr ProduceRequestHolder::computeAnswer() const {

  // Header.
  const RequestHeader& rh = request_->request_header_;
  ResponseMetadata metadata = {rh.api_key_, rh.api_version_, rh.correlation_id_};

  // Real answer.
  using ErrorCodeAndOffset = std::pair<int16_t, uint32_t>;
  std::map<std::string, std::map<int32_t, ErrorCodeAndOffset>> topic_to_partition_responses;
  for (const auto& footmark : footmarks_) {
    auto& partition_map = topic_to_partition_responses[footmark.topic_];
    auto it = partition_map.find(footmark.partition_);
    if (it == partition_map.end()) {
      partition_map[footmark.partition_] = {footmark.error_code_, footmark.saved_offset_};
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

  ProduceResponse data = {topic_responses, 0};
  return std::make_shared<Response<ProduceResponse>>(metadata, data);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
