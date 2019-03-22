
#include "contrib/kafka/filters/network/source/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {




BatchIndexAndErrorMessage::BatchIndexAndErrorMessage(int32_t batch_index, absl::optional<std::string> batch_index_error_message): batch_index_{batch_index}, batch_index_error_message_{batch_index_error_message}, tagged_fields_{TaggedFields({})} {};
BatchIndexAndErrorMessage::BatchIndexAndErrorMessage(int32_t batch_index, absl::optional<std::string> batch_index_error_message, TaggedFields tagged_fields): batch_index_{batch_index}, batch_index_error_message_{batch_index_error_message}, tagged_fields_{tagged_fields} {};


uint32_t BatchIndexAndErrorMessage::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 12) {
    written += encoder.computeSize(batch_index_);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.computeSize(batch_index_error_message_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(batch_index_error_message_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BatchIndexAndErrorMessage::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BatchIndexAndErrorMessage::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 12) {
    written += encoder.encode(batch_index_, dst);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.encode(batch_index_error_message_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(batch_index_error_message_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BatchIndexAndErrorMessage::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BatchIndexAndErrorMessage::operator==(const BatchIndexAndErrorMessage& rhs) const {

  return true
  && batch_index_ == rhs.batch_index_
  && batch_index_error_message_ == rhs.batch_index_error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


PartitionProduceResponse::PartitionProduceResponse(int32_t index, int16_t error_code, int64_t base_offset): index_{index}, error_code_{error_code}, base_offset_{base_offset}, log_append_time_ms_{-1}, log_start_offset_{-1}, record_errors_{std::vector<BatchIndexAndErrorMessage>{}}, error_message_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
PartitionProduceResponse::PartitionProduceResponse(int32_t index, int16_t error_code, int64_t base_offset, int64_t log_append_time_ms): index_{index}, error_code_{error_code}, base_offset_{base_offset}, log_append_time_ms_{log_append_time_ms}, log_start_offset_{-1}, record_errors_{std::vector<BatchIndexAndErrorMessage>{}}, error_message_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
PartitionProduceResponse::PartitionProduceResponse(int32_t index, int16_t error_code, int64_t base_offset, int64_t log_append_time_ms, int64_t log_start_offset): index_{index}, error_code_{error_code}, base_offset_{base_offset}, log_append_time_ms_{log_append_time_ms}, log_start_offset_{log_start_offset}, record_errors_{std::vector<BatchIndexAndErrorMessage>{}}, error_message_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
PartitionProduceResponse::PartitionProduceResponse(int32_t index, int16_t error_code, int64_t base_offset, int64_t log_append_time_ms, int64_t log_start_offset, std::vector<BatchIndexAndErrorMessage> record_errors, absl::optional<std::string> error_message): index_{index}, error_code_{error_code}, base_offset_{base_offset}, log_append_time_ms_{log_append_time_ms}, log_start_offset_{log_start_offset}, record_errors_{record_errors}, error_message_{error_message}, tagged_fields_{TaggedFields({})} {};
PartitionProduceResponse::PartitionProduceResponse(int32_t index, int16_t error_code, int64_t base_offset, int64_t log_append_time_ms, int64_t log_start_offset, std::vector<BatchIndexAndErrorMessage> record_errors, absl::optional<std::string> error_message, TaggedFields tagged_fields): index_{index}, error_code_{error_code}, base_offset_{base_offset}, log_append_time_ms_{log_append_time_ms}, log_start_offset_{log_start_offset}, record_errors_{record_errors}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t PartitionProduceResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(index_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(base_offset_);
  }
  
  if (api_version >= 2 && api_version < 12) {
    written += encoder.computeSize(log_append_time_ms_);
  }
  
  if (api_version >= 5 && api_version < 12) {
    written += encoder.computeSize(log_start_offset_);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.computeSize(record_errors_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(record_errors_);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t PartitionProduceResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t PartitionProduceResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(index_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(base_offset_, dst);
  }
  
  if (api_version >= 2 && api_version < 12) {
    written += encoder.encode(log_append_time_ms_, dst);
  }
  
  if (api_version >= 5 && api_version < 12) {
    written += encoder.encode(log_start_offset_, dst);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.encode(record_errors_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(record_errors_, dst);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t PartitionProduceResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool PartitionProduceResponse::operator==(const PartitionProduceResponse& rhs) const {

  return true
  && index_ == rhs.index_
  && error_code_ == rhs.error_code_
  && base_offset_ == rhs.base_offset_
  && log_append_time_ms_ == rhs.log_append_time_ms_
  && log_start_offset_ == rhs.log_start_offset_
  && record_errors_ == rhs.record_errors_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


TopicProduceResponse::TopicProduceResponse(std::string name, std::vector<PartitionProduceResponse> partition_responses): name_{name}, partition_responses_{partition_responses}, tagged_fields_{TaggedFields({})} {};
TopicProduceResponse::TopicProduceResponse(std::string name, std::vector<PartitionProduceResponse> partition_responses, TaggedFields tagged_fields): name_{name}, partition_responses_{partition_responses}, tagged_fields_{tagged_fields} {};


uint32_t TopicProduceResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partition_responses_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(partition_responses_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TopicProduceResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TopicProduceResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partition_responses_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(partition_responses_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TopicProduceResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TopicProduceResponse::operator==(const TopicProduceResponse& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_responses_ == rhs.partition_responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


ProduceResponse::ProduceResponse(std::vector<TopicProduceResponse> responses): responses_{responses}, throttle_time_ms_{0}, tagged_fields_{TaggedFields({})} {};
ProduceResponse::ProduceResponse(std::vector<TopicProduceResponse> responses, int32_t throttle_time_ms): responses_{responses}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
ProduceResponse::ProduceResponse(std::vector<TopicProduceResponse> responses, int32_t throttle_time_ms, TaggedFields tagged_fields): responses_{responses}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t ProduceResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(responses_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 1 && api_version < 12) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ProduceResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ProduceResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(responses_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 1 && api_version < 12) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ProduceResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ProduceResponse::operator==(const ProduceResponse& rhs) const {

  return true
  && responses_ == rhs.responses_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


AbortedTransaction::AbortedTransaction(int64_t producer_id, int64_t first_offset): producer_id_{producer_id}, first_offset_{first_offset}, tagged_fields_{TaggedFields({})} {};
AbortedTransaction::AbortedTransaction(int64_t producer_id, int64_t first_offset, TaggedFields tagged_fields): producer_id_{producer_id}, first_offset_{first_offset}, tagged_fields_{tagged_fields} {};


uint32_t AbortedTransaction::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.computeSize(first_offset_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AbortedTransaction::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AbortedTransaction::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.encode(first_offset_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AbortedTransaction::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AbortedTransaction::operator==(const AbortedTransaction& rhs) const {

  return true
  && producer_id_ == rhs.producer_id_
  && first_offset_ == rhs.first_offset_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchResponseResponsePartitionData::FetchResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int64_t high_watermark, absl::optional<Bytes> records): partition_index_{partition_index}, error_code_{error_code}, high_watermark_{high_watermark}, last_stable_offset_{-1}, log_start_offset_{-1}, aborted_transactions_{{std::vector<AbortedTransaction>{}}}, preferred_read_replica_{-1}, records_{records}, tagged_fields_{TaggedFields({})} {};
FetchResponseResponsePartitionData::FetchResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int64_t high_watermark, int64_t last_stable_offset, absl::optional<std::vector<AbortedTransaction>> aborted_transactions, absl::optional<Bytes> records): partition_index_{partition_index}, error_code_{error_code}, high_watermark_{high_watermark}, last_stable_offset_{last_stable_offset}, log_start_offset_{-1}, aborted_transactions_{aborted_transactions}, preferred_read_replica_{-1}, records_{records}, tagged_fields_{TaggedFields({})} {};
FetchResponseResponsePartitionData::FetchResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int64_t high_watermark, int64_t last_stable_offset, int64_t log_start_offset, absl::optional<std::vector<AbortedTransaction>> aborted_transactions, absl::optional<Bytes> records): partition_index_{partition_index}, error_code_{error_code}, high_watermark_{high_watermark}, last_stable_offset_{last_stable_offset}, log_start_offset_{log_start_offset}, aborted_transactions_{aborted_transactions}, preferred_read_replica_{-1}, records_{records}, tagged_fields_{TaggedFields({})} {};
FetchResponseResponsePartitionData::FetchResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int64_t high_watermark, int64_t last_stable_offset, int64_t log_start_offset, absl::optional<std::vector<AbortedTransaction>> aborted_transactions, int32_t preferred_read_replica, absl::optional<Bytes> records): partition_index_{partition_index}, error_code_{error_code}, high_watermark_{high_watermark}, last_stable_offset_{last_stable_offset}, log_start_offset_{log_start_offset}, aborted_transactions_{aborted_transactions}, preferred_read_replica_{preferred_read_replica}, records_{records}, tagged_fields_{TaggedFields({})} {};
FetchResponseResponsePartitionData::FetchResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int64_t high_watermark, int64_t last_stable_offset, int64_t log_start_offset, absl::optional<std::vector<AbortedTransaction>> aborted_transactions, int32_t preferred_read_replica, absl::optional<Bytes> records, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, high_watermark_{high_watermark}, last_stable_offset_{last_stable_offset}, log_start_offset_{log_start_offset}, aborted_transactions_{aborted_transactions}, preferred_read_replica_{preferred_read_replica}, records_{records}, tagged_fields_{tagged_fields} {};


uint32_t FetchResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(high_watermark_);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.computeSize(last_stable_offset_);
  }
  
  if (api_version >= 5 && api_version < 17) {
    written += encoder.computeSize(log_start_offset_);
  }
  
  if (api_version >= 4 && api_version < 12) {
    written += encoder.computeSize(aborted_transactions_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(aborted_transactions_);
  }
  
  if (api_version >= 11 && api_version < 17) {
    written += encoder.computeSize(preferred_read_replica_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(records_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(records_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(high_watermark_, dst);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.encode(last_stable_offset_, dst);
  }
  
  if (api_version >= 5 && api_version < 17) {
    written += encoder.encode(log_start_offset_, dst);
  }
  
  if (api_version >= 4 && api_version < 12) {
    written += encoder.encode(aborted_transactions_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(aborted_transactions_, dst);
  }
  
  if (api_version >= 11 && api_version < 17) {
    written += encoder.encode(preferred_read_replica_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(records_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(records_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchResponseResponsePartitionData::operator==(const FetchResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && high_watermark_ == rhs.high_watermark_
  && last_stable_offset_ == rhs.last_stable_offset_
  && log_start_offset_ == rhs.log_start_offset_
  && aborted_transactions_ == rhs.aborted_transactions_
  && preferred_read_replica_ == rhs.preferred_read_replica_
  && records_ == rhs.records_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchableTopicResponse::FetchableTopicResponse(std::string topic, std::vector<FetchResponseResponsePartitionData> partitions): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
FetchableTopicResponse::FetchableTopicResponse(std::string topic, std::vector<FetchResponseResponsePartitionData> partitions, TaggedFields tagged_fields): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{tagged_fields} {};
FetchableTopicResponse::FetchableTopicResponse(Uuid topic_id, std::vector<FetchResponseResponsePartitionData> partitions, TaggedFields tagged_fields): topic_{""}, topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t FetchableTopicResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 12 && api_version < 13) {
    written += encoder.computeCompactSize(topic_);
  }
  
  if (api_version >= 13 && api_version < 17) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchableTopicResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchableTopicResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 12 && api_version < 13) {
    written += encoder.encodeCompact(topic_, dst);
  }
  
  if (api_version >= 13 && api_version < 17) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchableTopicResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchableTopicResponse::operator==(const FetchableTopicResponse& rhs) const {

  return true
  && topic_ == rhs.topic_
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchResponse::FetchResponse(std::vector<FetchableTopicResponse> responses): throttle_time_ms_{0}, error_code_{0}, session_id_{0}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
FetchResponse::FetchResponse(int32_t throttle_time_ms, std::vector<FetchableTopicResponse> responses): throttle_time_ms_{throttle_time_ms}, error_code_{0}, session_id_{0}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
FetchResponse::FetchResponse(int32_t throttle_time_ms, int16_t error_code, int32_t session_id, std::vector<FetchableTopicResponse> responses): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, session_id_{session_id}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
FetchResponse::FetchResponse(int32_t throttle_time_ms, int16_t error_code, int32_t session_id, std::vector<FetchableTopicResponse> responses, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, session_id_{session_id}, responses_{responses}, tagged_fields_{tagged_fields} {};


uint32_t FetchResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 17) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.computeSize(session_id_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(responses_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 17) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.encode(session_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(responses_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchResponse::operator==(const FetchResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && session_id_ == rhs.session_id_
  && responses_ == rhs.responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsPartitionResponse::ListOffsetsPartitionResponse(int32_t partition_index, int16_t error_code, std::vector<int64_t> old_style_offsets): partition_index_{partition_index}, error_code_{error_code}, old_style_offsets_{old_style_offsets}, timestamp_{-1}, offset_{-1}, leader_epoch_{-1}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartitionResponse::ListOffsetsPartitionResponse(int32_t partition_index, int16_t error_code, int64_t timestamp, int64_t offset): partition_index_{partition_index}, error_code_{error_code}, old_style_offsets_{std::vector<int64_t>{}}, timestamp_{timestamp}, offset_{offset}, leader_epoch_{-1}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartitionResponse::ListOffsetsPartitionResponse(int32_t partition_index, int16_t error_code, int64_t timestamp, int64_t offset, int32_t leader_epoch): partition_index_{partition_index}, error_code_{error_code}, old_style_offsets_{std::vector<int64_t>{}}, timestamp_{timestamp}, offset_{offset}, leader_epoch_{leader_epoch}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartitionResponse::ListOffsetsPartitionResponse(int32_t partition_index, int16_t error_code, int64_t timestamp, int64_t offset, int32_t leader_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, old_style_offsets_{std::vector<int64_t>{}}, timestamp_{timestamp}, offset_{offset}, leader_epoch_{leader_epoch}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsPartitionResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(old_style_offsets_);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.computeSize(timestamp_);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.computeSize(offset_);
  }
  
  if (api_version >= 4 && api_version < 9) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListOffsetsPartitionResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsPartitionResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(old_style_offsets_, dst);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.encode(timestamp_, dst);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.encode(offset_, dst);
  }
  
  if (api_version >= 4 && api_version < 9) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListOffsetsPartitionResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsPartitionResponse::operator==(const ListOffsetsPartitionResponse& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && old_style_offsets_ == rhs.old_style_offsets_
  && timestamp_ == rhs.timestamp_
  && offset_ == rhs.offset_
  && leader_epoch_ == rhs.leader_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsTopicResponse::ListOffsetsTopicResponse(std::string name, std::vector<ListOffsetsPartitionResponse> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
ListOffsetsTopicResponse::ListOffsetsTopicResponse(std::string name, std::vector<ListOffsetsPartitionResponse> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsTopicResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListOffsetsTopicResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsTopicResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListOffsetsTopicResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsTopicResponse::operator==(const ListOffsetsTopicResponse& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsResponse::ListOffsetsResponse(std::vector<ListOffsetsTopicResponse> topics): throttle_time_ms_{0}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
ListOffsetsResponse::ListOffsetsResponse(int32_t throttle_time_ms, std::vector<ListOffsetsTopicResponse> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
ListOffsetsResponse::ListOffsetsResponse(int32_t throttle_time_ms, std::vector<ListOffsetsTopicResponse> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListOffsetsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListOffsetsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsResponse::operator==(const ListOffsetsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataResponseBroker::MetadataResponseBroker(int32_t node_id, std::string host, int32_t port): node_id_{node_id}, host_{host}, port_{port}, rack_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
MetadataResponseBroker::MetadataResponseBroker(int32_t node_id, std::string host, int32_t port, absl::optional<std::string> rack): node_id_{node_id}, host_{host}, port_{port}, rack_{rack}, tagged_fields_{TaggedFields({})} {};
MetadataResponseBroker::MetadataResponseBroker(int32_t node_id, std::string host, int32_t port, absl::optional<std::string> rack, TaggedFields tagged_fields): node_id_{node_id}, host_{host}, port_{port}, rack_{rack}, tagged_fields_{tagged_fields} {};


uint32_t MetadataResponseBroker::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(node_id_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(host_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.computeSize(rack_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(rack_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataResponseBroker::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataResponseBroker::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(node_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(host_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.encode(rack_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(rack_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataResponseBroker::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataResponseBroker::operator==(const MetadataResponseBroker& rhs) const {

  return true
  && node_id_ == rhs.node_id_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && rack_ == rhs.rack_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataResponsePartition::MetadataResponsePartition(int16_t error_code, int32_t partition_index, int32_t leader_id, std::vector<int32_t> replica_nodes, std::vector<int32_t> isr_nodes): error_code_{error_code}, partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{-1}, replica_nodes_{replica_nodes}, isr_nodes_{isr_nodes}, offline_replicas_{std::vector<int32_t>{}}, tagged_fields_{TaggedFields({})} {};
MetadataResponsePartition::MetadataResponsePartition(int16_t error_code, int32_t partition_index, int32_t leader_id, std::vector<int32_t> replica_nodes, std::vector<int32_t> isr_nodes, std::vector<int32_t> offline_replicas): error_code_{error_code}, partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{-1}, replica_nodes_{replica_nodes}, isr_nodes_{isr_nodes}, offline_replicas_{offline_replicas}, tagged_fields_{TaggedFields({})} {};
MetadataResponsePartition::MetadataResponsePartition(int16_t error_code, int32_t partition_index, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> replica_nodes, std::vector<int32_t> isr_nodes, std::vector<int32_t> offline_replicas): error_code_{error_code}, partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, replica_nodes_{replica_nodes}, isr_nodes_{isr_nodes}, offline_replicas_{offline_replicas}, tagged_fields_{TaggedFields({})} {};
MetadataResponsePartition::MetadataResponsePartition(int16_t error_code, int32_t partition_index, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> replica_nodes, std::vector<int32_t> isr_nodes, std::vector<int32_t> offline_replicas, TaggedFields tagged_fields): error_code_{error_code}, partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, replica_nodes_{replica_nodes}, isr_nodes_{isr_nodes}, offline_replicas_{offline_replicas}, tagged_fields_{tagged_fields} {};


uint32_t MetadataResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 7 && api_version < 13) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(replica_nodes_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(replica_nodes_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(isr_nodes_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(isr_nodes_);
  }
  
  if (api_version >= 5 && api_version < 9) {
    written += encoder.computeSize(offline_replicas_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(offline_replicas_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 13) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(replica_nodes_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(replica_nodes_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(isr_nodes_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(isr_nodes_, dst);
  }
  
  if (api_version >= 5 && api_version < 9) {
    written += encoder.encode(offline_replicas_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(offline_replicas_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataResponsePartition::operator==(const MetadataResponsePartition& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && partition_index_ == rhs.partition_index_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && replica_nodes_ == rhs.replica_nodes_
  && isr_nodes_ == rhs.isr_nodes_
  && offline_replicas_ == rhs.offline_replicas_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, std::string name, std::vector<MetadataResponsePartition> partitions): error_code_{error_code}, name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, is_internal_{false}, partitions_{partitions}, topic_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, std::string name, bool is_internal, std::vector<MetadataResponsePartition> partitions): error_code_{error_code}, name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, std::string name, bool is_internal, std::vector<MetadataResponsePartition> partitions, int32_t topic_authorized_operations): error_code_{error_code}, name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{topic_authorized_operations}, tagged_fields_{TaggedFields({})} {};
MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, std::string name, bool is_internal, std::vector<MetadataResponsePartition> partitions, int32_t topic_authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{topic_authorized_operations}, tagged_fields_{tagged_fields} {};
MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, std::string name, Uuid topic_id, bool is_internal, std::vector<MetadataResponsePartition> partitions, int32_t topic_authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, name_{absl::make_optional(name)}, topic_id_{topic_id}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{topic_authorized_operations}, tagged_fields_{tagged_fields} {};
MetadataResponseTopic::MetadataResponseTopic(int16_t error_code, absl::optional<std::string> name, Uuid topic_id, bool is_internal, std::vector<MetadataResponsePartition> partitions, int32_t topic_authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, name_{name}, topic_id_{topic_id}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{topic_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t MetadataResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 10 && api_version < 13) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 1 && api_version < 13) {
    written += encoder.computeSize(is_internal_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 8 && api_version < 13) {
    written += encoder.computeSize(topic_authorized_operations_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 13) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 10 && api_version < 13) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 1 && api_version < 13) {
    written += encoder.encode(is_internal_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 8 && api_version < 13) {
    written += encoder.encode(topic_authorized_operations_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataResponseTopic::operator==(const MetadataResponseTopic& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && name_ == rhs.name_
  && topic_id_ == rhs.topic_id_
  && is_internal_ == rhs.is_internal_
  && partitions_ == rhs.partitions_
  && topic_authorized_operations_ == rhs.topic_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataResponse::MetadataResponse(std::vector<MetadataResponseBroker> brokers, std::vector<MetadataResponseTopic> topics): throttle_time_ms_{0}, brokers_{brokers}, cluster_id_{absl::nullopt}, controller_id_{-1}, topics_{topics}, cluster_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponse::MetadataResponse(std::vector<MetadataResponseBroker> brokers, int32_t controller_id, std::vector<MetadataResponseTopic> topics): throttle_time_ms_{0}, brokers_{brokers}, cluster_id_{absl::nullopt}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponse::MetadataResponse(std::vector<MetadataResponseBroker> brokers, absl::optional<std::string> cluster_id, int32_t controller_id, std::vector<MetadataResponseTopic> topics): throttle_time_ms_{0}, brokers_{brokers}, cluster_id_{cluster_id}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponse::MetadataResponse(int32_t throttle_time_ms, std::vector<MetadataResponseBroker> brokers, absl::optional<std::string> cluster_id, int32_t controller_id, std::vector<MetadataResponseTopic> topics): throttle_time_ms_{throttle_time_ms}, brokers_{brokers}, cluster_id_{cluster_id}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
MetadataResponse::MetadataResponse(int32_t throttle_time_ms, std::vector<MetadataResponseBroker> brokers, absl::optional<std::string> cluster_id, int32_t controller_id, std::vector<MetadataResponseTopic> topics, int32_t cluster_authorized_operations): throttle_time_ms_{throttle_time_ms}, brokers_{brokers}, cluster_id_{cluster_id}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{cluster_authorized_operations}, tagged_fields_{TaggedFields({})} {};
MetadataResponse::MetadataResponse(int32_t throttle_time_ms, std::vector<MetadataResponseBroker> brokers, absl::optional<std::string> cluster_id, int32_t controller_id, std::vector<MetadataResponseTopic> topics, int32_t cluster_authorized_operations, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, brokers_{brokers}, cluster_id_{cluster_id}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{cluster_authorized_operations}, tagged_fields_{tagged_fields} {};
MetadataResponse::MetadataResponse(int32_t throttle_time_ms, std::vector<MetadataResponseBroker> brokers, absl::optional<std::string> cluster_id, int32_t controller_id, std::vector<MetadataResponseTopic> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, brokers_{brokers}, cluster_id_{cluster_id}, controller_id_{controller_id}, topics_{topics}, cluster_authorized_operations_{INT32_MIN}, tagged_fields_{tagged_fields} {};


uint32_t MetadataResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 13) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(brokers_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(brokers_);
  }
  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.computeSize(cluster_id_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(cluster_id_);
  }
  
  if (api_version >= 1 && api_version < 13) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 8 && api_version < 11) {
    written += encoder.computeSize(cluster_authorized_operations_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 13) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(brokers_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(brokers_, dst);
  }
  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.encode(cluster_id_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(cluster_id_, dst);
  }
  
  if (api_version >= 1 && api_version < 13) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 8 && api_version < 11) {
    written += encoder.encode(cluster_authorized_operations_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataResponse::operator==(const MetadataResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && brokers_ == rhs.brokers_
  && cluster_id_ == rhs.cluster_id_
  && controller_id_ == rhs.controller_id_
  && topics_ == rhs.topics_
  && cluster_authorized_operations_ == rhs.cluster_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrPartitionError::LeaderAndIsrPartitionError(std::string topic_name, int32_t partition_index, int16_t error_code): topic_name_{topic_name}, partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrPartitionError::LeaderAndIsrPartitionError(std::string topic_name, int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): topic_name_{topic_name}, partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};
LeaderAndIsrPartitionError::LeaderAndIsrPartitionError(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): topic_name_{""}, partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrPartitionError::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrPartitionError::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrPartitionError::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrPartitionError::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrPartitionError::operator==(const LeaderAndIsrPartitionError& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrTopicError::LeaderAndIsrTopicError(Uuid topic_id, std::vector<LeaderAndIsrPartitionError> partition_errors, TaggedFields tagged_fields): topic_id_{topic_id}, partition_errors_{partition_errors}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrTopicError::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(partition_errors_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrTopicError::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrTopicError::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(partition_errors_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrTopicError::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrTopicError::operator==(const LeaderAndIsrTopicError& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && partition_errors_ == rhs.partition_errors_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrResponse::LeaderAndIsrResponse(int16_t error_code, std::vector<LeaderAndIsrPartitionError> partition_errors): error_code_{error_code}, partition_errors_{partition_errors}, topics_{std::vector<LeaderAndIsrTopicError>{}}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrResponse::LeaderAndIsrResponse(int16_t error_code, std::vector<LeaderAndIsrPartitionError> partition_errors, TaggedFields tagged_fields): error_code_{error_code}, partition_errors_{partition_errors}, topics_{std::vector<LeaderAndIsrTopicError>{}}, tagged_fields_{tagged_fields} {};
LeaderAndIsrResponse::LeaderAndIsrResponse(int16_t error_code, std::vector<LeaderAndIsrTopicError> topics, TaggedFields tagged_fields): error_code_{error_code}, partition_errors_{std::vector<LeaderAndIsrPartitionError>{}}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partition_errors_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(partition_errors_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partition_errors_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(partition_errors_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrResponse::operator==(const LeaderAndIsrResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && partition_errors_ == rhs.partition_errors_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaPartitionError::StopReplicaPartitionError(std::string topic_name, int32_t partition_index, int16_t error_code): topic_name_{topic_name}, partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
StopReplicaPartitionError::StopReplicaPartitionError(std::string topic_name, int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): topic_name_{topic_name}, partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaPartitionError::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaPartitionError::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaPartitionError::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaPartitionError::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaPartitionError::operator==(const StopReplicaPartitionError& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaResponse::StopReplicaResponse(int16_t error_code, std::vector<StopReplicaPartitionError> partition_errors): error_code_{error_code}, partition_errors_{partition_errors}, tagged_fields_{TaggedFields({})} {};
StopReplicaResponse::StopReplicaResponse(int16_t error_code, std::vector<StopReplicaPartitionError> partition_errors, TaggedFields tagged_fields): error_code_{error_code}, partition_errors_{partition_errors}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partition_errors_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(partition_errors_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partition_errors_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(partition_errors_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaResponse::operator==(const StopReplicaResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && partition_errors_ == rhs.partition_errors_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataResponse::UpdateMetadataResponse(int16_t error_code): error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataResponse::UpdateMetadataResponse(int16_t error_code, TaggedFields tagged_fields): error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataResponse::operator==(const UpdateMetadataResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


RemainingPartition::RemainingPartition(std::string topic_name, int32_t partition_index): topic_name_{topic_name}, partition_index_{partition_index}, tagged_fields_{TaggedFields({})} {};
RemainingPartition::RemainingPartition(std::string topic_name, int32_t partition_index, TaggedFields tagged_fields): topic_name_{topic_name}, partition_index_{partition_index}, tagged_fields_{tagged_fields} {};


uint32_t RemainingPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t RemainingPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RemainingPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t RemainingPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RemainingPartition::operator==(const RemainingPartition& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControlledShutdownResponse::ControlledShutdownResponse(int16_t error_code, std::vector<RemainingPartition> remaining_partitions): error_code_{error_code}, remaining_partitions_{remaining_partitions}, tagged_fields_{TaggedFields({})} {};
ControlledShutdownResponse::ControlledShutdownResponse(int16_t error_code, std::vector<RemainingPartition> remaining_partitions, TaggedFields tagged_fields): error_code_{error_code}, remaining_partitions_{remaining_partitions}, tagged_fields_{tagged_fields} {};


uint32_t ControlledShutdownResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(remaining_partitions_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(remaining_partitions_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControlledShutdownResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControlledShutdownResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(remaining_partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(remaining_partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControlledShutdownResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControlledShutdownResponse::operator==(const ControlledShutdownResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && remaining_partitions_ == rhs.remaining_partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitResponsePartition::OffsetCommitResponsePartition(int32_t partition_index, int16_t error_code): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
OffsetCommitResponsePartition::OffsetCommitResponsePartition(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetCommitResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetCommitResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitResponsePartition::operator==(const OffsetCommitResponsePartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitResponseTopic::OffsetCommitResponseTopic(std::string name, std::vector<OffsetCommitResponsePartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
OffsetCommitResponseTopic::OffsetCommitResponseTopic(std::string name, std::vector<OffsetCommitResponsePartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetCommitResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetCommitResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitResponseTopic::operator==(const OffsetCommitResponseTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitResponse::OffsetCommitResponse(std::vector<OffsetCommitResponseTopic> topics): throttle_time_ms_{0}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitResponse::OffsetCommitResponse(int32_t throttle_time_ms, std::vector<OffsetCommitResponseTopic> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitResponse::OffsetCommitResponse(int32_t throttle_time_ms, std::vector<OffsetCommitResponseTopic> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 10) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetCommitResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 10) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetCommitResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitResponse::operator==(const OffsetCommitResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponsePartition::OffsetFetchResponsePartition(int32_t partition_index, int64_t committed_offset, absl::optional<std::string> metadata, int16_t error_code): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{-1}, metadata_{metadata}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponsePartition::OffsetFetchResponsePartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> metadata, int16_t error_code): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, metadata_{metadata}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponsePartition::OffsetFetchResponsePartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> metadata, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, metadata_{metadata}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(committed_offset_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(committed_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(metadata_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(metadata_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(committed_offset_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(committed_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(metadata_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(metadata_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponsePartition::operator==(const OffsetFetchResponsePartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && committed_offset_ == rhs.committed_offset_
  && committed_leader_epoch_ == rhs.committed_leader_epoch_
  && metadata_ == rhs.metadata_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponseTopic::OffsetFetchResponseTopic(std::string name, std::vector<OffsetFetchResponsePartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponseTopic::OffsetFetchResponseTopic(std::string name, std::vector<OffsetFetchResponsePartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponseTopic::operator==(const OffsetFetchResponseTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponsePartitions::OffsetFetchResponsePartitions(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> metadata, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, metadata_{metadata}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponsePartitions::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeSize(committed_offset_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeSize(committed_leader_epoch_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(metadata_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponsePartitions::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponsePartitions::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encode(committed_offset_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encode(committed_leader_epoch_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(metadata_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponsePartitions::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponsePartitions::operator==(const OffsetFetchResponsePartitions& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && committed_offset_ == rhs.committed_offset_
  && committed_leader_epoch_ == rhs.committed_leader_epoch_
  && metadata_ == rhs.metadata_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponseTopics::OffsetFetchResponseTopics(std::string name, std::vector<OffsetFetchResponsePartitions> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponseTopics::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponseTopics::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponseTopics::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponseTopics::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponseTopics::operator==(const OffsetFetchResponseTopics& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponseGroup::OffsetFetchResponseGroup(std::string group_id, std::vector<OffsetFetchResponseTopics> topics, int16_t error_code, TaggedFields tagged_fields): group_id_{group_id}, topics_{topics}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponseGroup::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponseGroup::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponseGroup::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponseGroup::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponseGroup::operator==(const OffsetFetchResponseGroup& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && topics_ == rhs.topics_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchResponse::OffsetFetchResponse(std::vector<OffsetFetchResponseTopic> topics): throttle_time_ms_{0}, topics_{topics}, error_code_{0}, groups_{std::vector<OffsetFetchResponseGroup>{}}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponse::OffsetFetchResponse(std::vector<OffsetFetchResponseTopic> topics, int16_t error_code): throttle_time_ms_{0}, topics_{topics}, error_code_{error_code}, groups_{std::vector<OffsetFetchResponseGroup>{}}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponse::OffsetFetchResponse(int32_t throttle_time_ms, std::vector<OffsetFetchResponseTopic> topics, int16_t error_code): throttle_time_ms_{throttle_time_ms}, topics_{topics}, error_code_{error_code}, groups_{std::vector<OffsetFetchResponseGroup>{}}, tagged_fields_{TaggedFields({})} {};
OffsetFetchResponse::OffsetFetchResponse(int32_t throttle_time_ms, std::vector<OffsetFetchResponseTopic> topics, int16_t error_code, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, error_code_{error_code}, groups_{std::vector<OffsetFetchResponseGroup>{}}, tagged_fields_{tagged_fields} {};
OffsetFetchResponse::OffsetFetchResponse(int32_t throttle_time_ms, std::vector<OffsetFetchResponseGroup> groups, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{std::vector<OffsetFetchResponseTopic>{}}, error_code_{0}, groups_{groups}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 10) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 10) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchResponse::operator==(const OffsetFetchResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && error_code_ == rhs.error_code_
  && groups_ == rhs.groups_
  && tagged_fields_ == rhs.tagged_fields_;
};


Coordinator::Coordinator(std::string key, int32_t node_id, std::string host, int32_t port, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): key_{key}, node_id_{node_id}, host_{host}, port_{port}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t Coordinator::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(key_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(node_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t Coordinator::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t Coordinator::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(key_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(node_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t Coordinator::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool Coordinator::operator==(const Coordinator& rhs) const {

  return true
  && key_ == rhs.key_
  && node_id_ == rhs.node_id_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


FindCoordinatorResponse::FindCoordinatorResponse(int16_t error_code, int32_t node_id, std::string host, int32_t port): throttle_time_ms_{0}, error_code_{error_code}, error_message_{{""}}, node_id_{node_id}, host_{host}, port_{port}, coordinators_{std::vector<Coordinator>{}}, tagged_fields_{TaggedFields({})} {};
FindCoordinatorResponse::FindCoordinatorResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, int32_t node_id, std::string host, int32_t port): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, node_id_{node_id}, host_{host}, port_{port}, coordinators_{std::vector<Coordinator>{}}, tagged_fields_{TaggedFields({})} {};
FindCoordinatorResponse::FindCoordinatorResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, int32_t node_id, std::string host, int32_t port, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, node_id_{node_id}, host_{host}, port_{port}, coordinators_{std::vector<Coordinator>{}}, tagged_fields_{tagged_fields} {};
FindCoordinatorResponse::FindCoordinatorResponse(int32_t throttle_time_ms, std::vector<Coordinator> coordinators, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{0}, error_message_{{""}}, node_id_{0}, host_{""}, port_{0}, coordinators_{coordinators}, tagged_fields_{tagged_fields} {};


uint32_t FindCoordinatorResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(node_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(host_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(coordinators_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FindCoordinatorResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FindCoordinatorResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(node_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(host_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(coordinators_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FindCoordinatorResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FindCoordinatorResponse::operator==(const FindCoordinatorResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && node_id_ == rhs.node_id_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && coordinators_ == rhs.coordinators_
  && tagged_fields_ == rhs.tagged_fields_;
};


JoinGroupResponseMember::JoinGroupResponseMember(std::string member_id, Bytes metadata): member_id_{member_id}, group_instance_id_{absl::nullopt}, metadata_{metadata}, tagged_fields_{TaggedFields({})} {};
JoinGroupResponseMember::JoinGroupResponseMember(std::string member_id, absl::optional<std::string> group_instance_id, Bytes metadata): member_id_{member_id}, group_instance_id_{group_instance_id}, metadata_{metadata}, tagged_fields_{TaggedFields({})} {};
JoinGroupResponseMember::JoinGroupResponseMember(std::string member_id, absl::optional<std::string> group_instance_id, Bytes metadata, TaggedFields tagged_fields): member_id_{member_id}, group_instance_id_{group_instance_id}, metadata_{metadata}, tagged_fields_{tagged_fields} {};


uint32_t JoinGroupResponseMember::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeSize(group_instance_id_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(group_instance_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(metadata_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(metadata_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t JoinGroupResponseMember::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t JoinGroupResponseMember::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encode(group_instance_id_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(group_instance_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(metadata_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(metadata_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t JoinGroupResponseMember::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool JoinGroupResponseMember::operator==(const JoinGroupResponseMember& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && metadata_ == rhs.metadata_
  && tagged_fields_ == rhs.tagged_fields_;
};


JoinGroupResponse::JoinGroupResponse(int16_t error_code, int32_t generation_id, std::string protocol_name, std::string leader, std::string member_id, std::vector<JoinGroupResponseMember> members): throttle_time_ms_{0}, error_code_{error_code}, generation_id_{generation_id}, protocol_type_{absl::nullopt}, protocol_name_{absl::make_optional(protocol_name)}, leader_{leader}, skip_assignment_{false}, member_id_{member_id}, members_{members}, tagged_fields_{TaggedFields({})} {};
JoinGroupResponse::JoinGroupResponse(int32_t throttle_time_ms, int16_t error_code, int32_t generation_id, std::string protocol_name, std::string leader, std::string member_id, std::vector<JoinGroupResponseMember> members): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, generation_id_{generation_id}, protocol_type_{absl::nullopt}, protocol_name_{absl::make_optional(protocol_name)}, leader_{leader}, skip_assignment_{false}, member_id_{member_id}, members_{members}, tagged_fields_{TaggedFields({})} {};
JoinGroupResponse::JoinGroupResponse(int32_t throttle_time_ms, int16_t error_code, int32_t generation_id, std::string protocol_name, std::string leader, std::string member_id, std::vector<JoinGroupResponseMember> members, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, generation_id_{generation_id}, protocol_type_{absl::nullopt}, protocol_name_{absl::make_optional(protocol_name)}, leader_{leader}, skip_assignment_{false}, member_id_{member_id}, members_{members}, tagged_fields_{tagged_fields} {};
JoinGroupResponse::JoinGroupResponse(int32_t throttle_time_ms, int16_t error_code, int32_t generation_id, absl::optional<std::string> protocol_type, absl::optional<std::string> protocol_name, std::string leader, std::string member_id, std::vector<JoinGroupResponseMember> members, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, generation_id_{generation_id}, protocol_type_{protocol_type}, protocol_name_{protocol_name}, leader_{leader}, skip_assignment_{false}, member_id_{member_id}, members_{members}, tagged_fields_{tagged_fields} {};
JoinGroupResponse::JoinGroupResponse(int32_t throttle_time_ms, int16_t error_code, int32_t generation_id, absl::optional<std::string> protocol_type, absl::optional<std::string> protocol_name, std::string leader, bool skip_assignment, std::string member_id, std::vector<JoinGroupResponseMember> members, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, generation_id_{generation_id}, protocol_type_{protocol_type}, protocol_name_{protocol_name}, leader_{leader}, skip_assignment_{skip_assignment}, member_id_{member_id}, members_{members}, tagged_fields_{tagged_fields} {};


uint32_t JoinGroupResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 10) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(generation_id_);
  }
  
  if (api_version >= 7 && api_version < 10) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(protocol_name_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(protocol_name_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(leader_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(leader_);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.computeSize(skip_assignment_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(members_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(members_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t JoinGroupResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t JoinGroupResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 10) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(generation_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 10) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(protocol_name_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(protocol_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(leader_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(leader_, dst);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.encode(skip_assignment_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(members_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(members_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t JoinGroupResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool JoinGroupResponse::operator==(const JoinGroupResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && generation_id_ == rhs.generation_id_
  && protocol_type_ == rhs.protocol_type_
  && protocol_name_ == rhs.protocol_name_
  && leader_ == rhs.leader_
  && skip_assignment_ == rhs.skip_assignment_
  && member_id_ == rhs.member_id_
  && members_ == rhs.members_
  && tagged_fields_ == rhs.tagged_fields_;
};


HeartbeatResponse::HeartbeatResponse(int16_t error_code): throttle_time_ms_{0}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
HeartbeatResponse::HeartbeatResponse(int32_t throttle_time_ms, int16_t error_code): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
HeartbeatResponse::HeartbeatResponse(int32_t throttle_time_ms, int16_t error_code, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t HeartbeatResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t HeartbeatResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t HeartbeatResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t HeartbeatResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool HeartbeatResponse::operator==(const HeartbeatResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


MemberResponse::MemberResponse(std::string member_id, absl::optional<std::string> group_instance_id, int16_t error_code): member_id_{member_id}, group_instance_id_{group_instance_id}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
MemberResponse::MemberResponse(std::string member_id, absl::optional<std::string> group_instance_id, int16_t error_code, TaggedFields tagged_fields): member_id_{member_id}, group_instance_id_{group_instance_id}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t MemberResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(group_instance_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(group_instance_id_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MemberResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MemberResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(group_instance_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(group_instance_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MemberResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MemberResponse::operator==(const MemberResponse& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaveGroupResponse::LeaveGroupResponse(int16_t error_code): throttle_time_ms_{0}, error_code_{error_code}, members_{std::vector<MemberResponse>{}}, tagged_fields_{TaggedFields({})} {};
LeaveGroupResponse::LeaveGroupResponse(int32_t throttle_time_ms, int16_t error_code): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, members_{std::vector<MemberResponse>{}}, tagged_fields_{TaggedFields({})} {};
LeaveGroupResponse::LeaveGroupResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<MemberResponse> members): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, members_{members}, tagged_fields_{TaggedFields({})} {};
LeaveGroupResponse::LeaveGroupResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<MemberResponse> members, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, members_{members}, tagged_fields_{tagged_fields} {};


uint32_t LeaveGroupResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(members_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(members_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaveGroupResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaveGroupResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(members_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(members_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaveGroupResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaveGroupResponse::operator==(const LeaveGroupResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && members_ == rhs.members_
  && tagged_fields_ == rhs.tagged_fields_;
};


SyncGroupResponse::SyncGroupResponse(int16_t error_code, Bytes assignment): throttle_time_ms_{0}, error_code_{error_code}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignment_{assignment}, tagged_fields_{TaggedFields({})} {};
SyncGroupResponse::SyncGroupResponse(int32_t throttle_time_ms, int16_t error_code, Bytes assignment): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignment_{assignment}, tagged_fields_{TaggedFields({})} {};
SyncGroupResponse::SyncGroupResponse(int32_t throttle_time_ms, int16_t error_code, Bytes assignment, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignment_{assignment}, tagged_fields_{tagged_fields} {};
SyncGroupResponse::SyncGroupResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> protocol_type, absl::optional<std::string> protocol_name, Bytes assignment, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, protocol_type_{protocol_type}, protocol_name_{protocol_name}, assignment_{assignment}, tagged_fields_{tagged_fields} {};


uint32_t SyncGroupResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(assignment_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(assignment_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t SyncGroupResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SyncGroupResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(assignment_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(assignment_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t SyncGroupResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SyncGroupResponse::operator==(const SyncGroupResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && protocol_type_ == rhs.protocol_type_
  && protocol_name_ == rhs.protocol_name_
  && assignment_ == rhs.assignment_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribedGroupMember::DescribedGroupMember(std::string member_id, std::string client_id, std::string client_host, Bytes member_metadata, Bytes member_assignment): member_id_{member_id}, group_instance_id_{absl::nullopt}, client_id_{client_id}, client_host_{client_host}, member_metadata_{member_metadata}, member_assignment_{member_assignment}, tagged_fields_{TaggedFields({})} {};
DescribedGroupMember::DescribedGroupMember(std::string member_id, absl::optional<std::string> group_instance_id, std::string client_id, std::string client_host, Bytes member_metadata, Bytes member_assignment): member_id_{member_id}, group_instance_id_{group_instance_id}, client_id_{client_id}, client_host_{client_host}, member_metadata_{member_metadata}, member_assignment_{member_assignment}, tagged_fields_{TaggedFields({})} {};
DescribedGroupMember::DescribedGroupMember(std::string member_id, absl::optional<std::string> group_instance_id, std::string client_id, std::string client_host, Bytes member_metadata, Bytes member_assignment, TaggedFields tagged_fields): member_id_{member_id}, group_instance_id_{group_instance_id}, client_id_{client_id}, client_host_{client_host}, member_metadata_{member_metadata}, member_assignment_{member_assignment}, tagged_fields_{tagged_fields} {};


uint32_t DescribedGroupMember::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeSize(group_instance_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(group_instance_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(client_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(client_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(client_host_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(client_host_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(member_metadata_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(member_metadata_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(member_assignment_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(member_assignment_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribedGroupMember::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribedGroupMember::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encode(group_instance_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(group_instance_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(client_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(client_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(client_host_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(client_host_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(member_metadata_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(member_metadata_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(member_assignment_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(member_assignment_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribedGroupMember::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribedGroupMember::operator==(const DescribedGroupMember& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && client_id_ == rhs.client_id_
  && client_host_ == rhs.client_host_
  && member_metadata_ == rhs.member_metadata_
  && member_assignment_ == rhs.member_assignment_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeGroupsResponseDescribedGroup::DescribeGroupsResponseDescribedGroup(int16_t error_code, std::string group_id, std::string group_state, std::string protocol_type, std::string protocol_data, std::vector<DescribedGroupMember> members): error_code_{error_code}, group_id_{group_id}, group_state_{group_state}, protocol_type_{protocol_type}, protocol_data_{protocol_data}, members_{members}, authorized_operations_{INT32_MIN}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsResponseDescribedGroup::DescribeGroupsResponseDescribedGroup(int16_t error_code, std::string group_id, std::string group_state, std::string protocol_type, std::string protocol_data, std::vector<DescribedGroupMember> members, int32_t authorized_operations): error_code_{error_code}, group_id_{group_id}, group_state_{group_state}, protocol_type_{protocol_type}, protocol_data_{protocol_data}, members_{members}, authorized_operations_{authorized_operations}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsResponseDescribedGroup::DescribeGroupsResponseDescribedGroup(int16_t error_code, std::string group_id, std::string group_state, std::string protocol_type, std::string protocol_data, std::vector<DescribedGroupMember> members, int32_t authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, group_id_{group_id}, group_state_{group_state}, protocol_type_{protocol_type}, protocol_data_{protocol_data}, members_{members}, authorized_operations_{authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t DescribeGroupsResponseDescribedGroup::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(group_state_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(group_state_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(protocol_type_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(protocol_data_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_data_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(members_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(members_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(authorized_operations_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeGroupsResponseDescribedGroup::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeGroupsResponseDescribedGroup::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(group_state_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(group_state_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(protocol_type_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(protocol_data_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_data_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(members_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(members_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(authorized_operations_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeGroupsResponseDescribedGroup::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeGroupsResponseDescribedGroup::operator==(const DescribeGroupsResponseDescribedGroup& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && group_id_ == rhs.group_id_
  && group_state_ == rhs.group_state_
  && protocol_type_ == rhs.protocol_type_
  && protocol_data_ == rhs.protocol_data_
  && members_ == rhs.members_
  && authorized_operations_ == rhs.authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeGroupsResponse::DescribeGroupsResponse(std::vector<DescribeGroupsResponseDescribedGroup> groups): throttle_time_ms_{0}, groups_{groups}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsResponse::DescribeGroupsResponse(int32_t throttle_time_ms, std::vector<DescribeGroupsResponseDescribedGroup> groups): throttle_time_ms_{throttle_time_ms}, groups_{groups}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsResponse::DescribeGroupsResponse(int32_t throttle_time_ms, std::vector<DescribeGroupsResponseDescribedGroup> groups, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, groups_{groups}, tagged_fields_{tagged_fields} {};


uint32_t DescribeGroupsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(groups_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeGroupsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeGroupsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(groups_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeGroupsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeGroupsResponse::operator==(const DescribeGroupsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && groups_ == rhs.groups_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListedGroup::ListedGroup(std::string group_id, std::string protocol_type): group_id_{group_id}, protocol_type_{protocol_type}, group_state_{""}, group_type_{""}, tagged_fields_{TaggedFields({})} {};
ListedGroup::ListedGroup(std::string group_id, std::string protocol_type, TaggedFields tagged_fields): group_id_{group_id}, protocol_type_{protocol_type}, group_state_{""}, group_type_{""}, tagged_fields_{tagged_fields} {};
ListedGroup::ListedGroup(std::string group_id, std::string protocol_type, std::string group_state, TaggedFields tagged_fields): group_id_{group_id}, protocol_type_{protocol_type}, group_state_{group_state}, group_type_{""}, tagged_fields_{tagged_fields} {};
ListedGroup::ListedGroup(std::string group_id, std::string protocol_type, std::string group_state, std::string group_type, TaggedFields tagged_fields): group_id_{group_id}, protocol_type_{protocol_type}, group_state_{group_state}, group_type_{group_type}, tagged_fields_{tagged_fields} {};


uint32_t ListedGroup::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(protocol_type_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(group_state_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(group_type_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListedGroup::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListedGroup::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(protocol_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(group_state_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(group_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListedGroup::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListedGroup::operator==(const ListedGroup& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && protocol_type_ == rhs.protocol_type_
  && group_state_ == rhs.group_state_
  && group_type_ == rhs.group_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListGroupsResponse::ListGroupsResponse(int16_t error_code, std::vector<ListedGroup> groups): throttle_time_ms_{0}, error_code_{error_code}, groups_{groups}, tagged_fields_{TaggedFields({})} {};
ListGroupsResponse::ListGroupsResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ListedGroup> groups): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, groups_{groups}, tagged_fields_{TaggedFields({})} {};
ListGroupsResponse::ListGroupsResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ListedGroup> groups, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, groups_{groups}, tagged_fields_{tagged_fields} {};


uint32_t ListGroupsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(groups_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListGroupsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListGroupsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(groups_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListGroupsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListGroupsResponse::operator==(const ListGroupsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && groups_ == rhs.groups_
  && tagged_fields_ == rhs.tagged_fields_;
};


SaslHandshakeResponse::SaslHandshakeResponse(int16_t error_code, std::vector<std::string> mechanisms): error_code_{error_code}, mechanisms_{mechanisms} {};


uint32_t SaslHandshakeResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(mechanisms_);
  }
  

  return written;
}

uint32_t SaslHandshakeResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SaslHandshakeResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(mechanisms_, dst);
  }
  

  return written;
}

uint32_t SaslHandshakeResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SaslHandshakeResponse::operator==(const SaslHandshakeResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && mechanisms_ == rhs.mechanisms_;
};


ApiVersion::ApiVersion(int16_t api_key, int16_t min_version, int16_t max_version): api_key_{api_key}, min_version_{min_version}, max_version_{max_version}, tagged_fields_{TaggedFields({})} {};
ApiVersion::ApiVersion(int16_t api_key, int16_t min_version, int16_t max_version, TaggedFields tagged_fields): api_key_{api_key}, min_version_{min_version}, max_version_{max_version}, tagged_fields_{tagged_fields} {};


uint32_t ApiVersion::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(api_key_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(min_version_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(max_version_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ApiVersion::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ApiVersion::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(api_key_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(min_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(max_version_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ApiVersion::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ApiVersion::operator==(const ApiVersion& rhs) const {

  return true
  && api_key_ == rhs.api_key_
  && min_version_ == rhs.min_version_
  && max_version_ == rhs.max_version_
  && tagged_fields_ == rhs.tagged_fields_;
};


ApiVersionsResponse::ApiVersionsResponse(int16_t error_code, std::vector<ApiVersion> api_keys): error_code_{error_code}, api_keys_{api_keys}, throttle_time_ms_{0}, tagged_fields_{TaggedFields({})} {};
ApiVersionsResponse::ApiVersionsResponse(int16_t error_code, std::vector<ApiVersion> api_keys, int32_t throttle_time_ms): error_code_{error_code}, api_keys_{api_keys}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
ApiVersionsResponse::ApiVersionsResponse(int16_t error_code, std::vector<ApiVersion> api_keys, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, api_keys_{api_keys}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t ApiVersionsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(api_keys_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(api_keys_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ApiVersionsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ApiVersionsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(api_keys_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(api_keys_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ApiVersionsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ApiVersionsResponse::operator==(const ApiVersionsResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && api_keys_ == rhs.api_keys_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatableTopicConfigs::CreatableTopicConfigs(std::string name, absl::optional<std::string> value, bool read_only, int8_t config_source, bool is_sensitive, TaggedFields tagged_fields): name_{name}, value_{value}, read_only_{read_only}, config_source_{config_source}, is_sensitive_{is_sensitive}, tagged_fields_{tagged_fields} {};


uint32_t CreatableTopicConfigs::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(read_only_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(config_source_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(is_sensitive_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatableTopicConfigs::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatableTopicConfigs::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(read_only_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(config_source_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(is_sensitive_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatableTopicConfigs::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatableTopicConfigs::operator==(const CreatableTopicConfigs& rhs) const {

  return true
  && name_ == rhs.name_
  && value_ == rhs.value_
  && read_only_ == rhs.read_only_
  && config_source_ == rhs.config_source_
  && is_sensitive_ == rhs.is_sensitive_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatableTopicResult::CreatableTopicResult(std::string name, int16_t error_code): name_{name}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{{""}}, num_partitions_{-1}, replication_factor_{-1}, configs_{{std::vector<CreatableTopicConfigs>{}}}, tagged_fields_{TaggedFields({})} {};
CreatableTopicResult::CreatableTopicResult(std::string name, int16_t error_code, absl::optional<std::string> error_message): name_{name}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{error_message}, num_partitions_{-1}, replication_factor_{-1}, configs_{{std::vector<CreatableTopicConfigs>{}}}, tagged_fields_{TaggedFields({})} {};
CreatableTopicResult::CreatableTopicResult(std::string name, int16_t error_code, absl::optional<std::string> error_message, int32_t num_partitions, int16_t replication_factor, absl::optional<std::vector<CreatableTopicConfigs>> configs, TaggedFields tagged_fields): name_{name}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{error_message}, num_partitions_{num_partitions}, replication_factor_{replication_factor}, configs_{configs}, tagged_fields_{tagged_fields} {};
CreatableTopicResult::CreatableTopicResult(std::string name, Uuid topic_id, int16_t error_code, absl::optional<std::string> error_message, int32_t num_partitions, int16_t replication_factor, absl::optional<std::vector<CreatableTopicConfigs>> configs, TaggedFields tagged_fields): name_{name}, topic_id_{topic_id}, error_code_{error_code}, error_message_{error_message}, num_partitions_{num_partitions}, replication_factor_{replication_factor}, configs_{configs}, tagged_fields_{tagged_fields} {};


uint32_t CreatableTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(num_partitions_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(replication_factor_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(configs_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatableTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatableTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(num_partitions_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(replication_factor_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(configs_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatableTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatableTopicResult::operator==(const CreatableTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && topic_id_ == rhs.topic_id_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && num_partitions_ == rhs.num_partitions_
  && replication_factor_ == rhs.replication_factor_
  && configs_ == rhs.configs_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateTopicsResponse::CreateTopicsResponse(std::vector<CreatableTopicResult> topics): throttle_time_ms_{0}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
CreateTopicsResponse::CreateTopicsResponse(int32_t throttle_time_ms, std::vector<CreatableTopicResult> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
CreateTopicsResponse::CreateTopicsResponse(int32_t throttle_time_ms, std::vector<CreatableTopicResult> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t CreateTopicsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateTopicsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateTopicsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateTopicsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateTopicsResponse::operator==(const CreateTopicsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeletableTopicResult::DeletableTopicResult(std::string name, int16_t error_code): name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
DeletableTopicResult::DeletableTopicResult(std::string name, int16_t error_code, TaggedFields tagged_fields): name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{absl::nullopt}, tagged_fields_{tagged_fields} {};
DeletableTopicResult::DeletableTopicResult(std::string name, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): name_{absl::make_optional(name)}, topic_id_{Uuid{0, 0}}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};
DeletableTopicResult::DeletableTopicResult(absl::optional<std::string> name, Uuid topic_id, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): name_{name}, topic_id_{topic_id}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t DeletableTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 7) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 5 && api_version < 7) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeletableTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeletableTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 7) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 5 && api_version < 7) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeletableTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeletableTopicResult::operator==(const DeletableTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && topic_id_ == rhs.topic_id_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteTopicsResponse::DeleteTopicsResponse(std::vector<DeletableTopicResult> responses): throttle_time_ms_{0}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
DeleteTopicsResponse::DeleteTopicsResponse(int32_t throttle_time_ms, std::vector<DeletableTopicResult> responses): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
DeleteTopicsResponse::DeleteTopicsResponse(int32_t throttle_time_ms, std::vector<DeletableTopicResult> responses, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{tagged_fields} {};


uint32_t DeleteTopicsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 7) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(responses_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteTopicsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteTopicsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 7) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(responses_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteTopicsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteTopicsResponse::operator==(const DeleteTopicsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && responses_ == rhs.responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsPartitionResult::DeleteRecordsPartitionResult(int32_t partition_index, int64_t low_watermark, int16_t error_code): partition_index_{partition_index}, low_watermark_{low_watermark}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsPartitionResult::DeleteRecordsPartitionResult(int32_t partition_index, int64_t low_watermark, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, low_watermark_{low_watermark}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsPartitionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(low_watermark_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteRecordsPartitionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsPartitionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(low_watermark_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteRecordsPartitionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsPartitionResult::operator==(const DeleteRecordsPartitionResult& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && low_watermark_ == rhs.low_watermark_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsTopicResult::DeleteRecordsTopicResult(std::string name, std::vector<DeleteRecordsPartitionResult> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsTopicResult::DeleteRecordsTopicResult(std::string name, std::vector<DeleteRecordsPartitionResult> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteRecordsTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteRecordsTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsTopicResult::operator==(const DeleteRecordsTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsResponse::DeleteRecordsResponse(int32_t throttle_time_ms, std::vector<DeleteRecordsTopicResult> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsResponse::DeleteRecordsResponse(int32_t throttle_time_ms, std::vector<DeleteRecordsTopicResult> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteRecordsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteRecordsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsResponse::operator==(const DeleteRecordsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


InitProducerIdResponse::InitProducerIdResponse(int32_t throttle_time_ms, int16_t error_code, int64_t producer_id, int16_t producer_epoch): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, tagged_fields_{TaggedFields({})} {};
InitProducerIdResponse::InitProducerIdResponse(int32_t throttle_time_ms, int16_t error_code, int64_t producer_id, int16_t producer_epoch, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, tagged_fields_{tagged_fields} {};


uint32_t InitProducerIdResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t InitProducerIdResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t InitProducerIdResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t InitProducerIdResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool InitProducerIdResponse::operator==(const InitProducerIdResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


EpochEndOffset::EpochEndOffset(int16_t error_code, int32_t partition, int64_t end_offset): error_code_{error_code}, partition_{partition}, leader_epoch_{-1}, end_offset_{end_offset}, tagged_fields_{TaggedFields({})} {};
EpochEndOffset::EpochEndOffset(int16_t error_code, int32_t partition, int32_t leader_epoch, int64_t end_offset): error_code_{error_code}, partition_{partition}, leader_epoch_{leader_epoch}, end_offset_{end_offset}, tagged_fields_{TaggedFields({})} {};
EpochEndOffset::EpochEndOffset(int16_t error_code, int32_t partition, int32_t leader_epoch, int64_t end_offset, TaggedFields tagged_fields): error_code_{error_code}, partition_{partition}, leader_epoch_{leader_epoch}, end_offset_{end_offset}, tagged_fields_{tagged_fields} {};


uint32_t EpochEndOffset::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(end_offset_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t EpochEndOffset::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EpochEndOffset::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(end_offset_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t EpochEndOffset::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EpochEndOffset::operator==(const EpochEndOffset& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && partition_ == rhs.partition_
  && leader_epoch_ == rhs.leader_epoch_
  && end_offset_ == rhs.end_offset_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetForLeaderTopicResult::OffsetForLeaderTopicResult(std::string topic, std::vector<EpochEndOffset> partitions): topic_{topic}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderTopicResult::OffsetForLeaderTopicResult(std::string topic, std::vector<EpochEndOffset> partitions, TaggedFields tagged_fields): topic_{topic}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetForLeaderTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(topic_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetForLeaderTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetForLeaderTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(topic_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetForLeaderTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetForLeaderTopicResult::operator==(const OffsetForLeaderTopicResult& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetForLeaderEpochResponse::OffsetForLeaderEpochResponse(std::vector<OffsetForLeaderTopicResult> topics): throttle_time_ms_{0}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderEpochResponse::OffsetForLeaderEpochResponse(int32_t throttle_time_ms, std::vector<OffsetForLeaderTopicResult> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderEpochResponse::OffsetForLeaderEpochResponse(int32_t throttle_time_ms, std::vector<OffsetForLeaderTopicResult> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t OffsetForLeaderEpochResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetForLeaderEpochResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetForLeaderEpochResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetForLeaderEpochResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetForLeaderEpochResponse::operator==(const OffsetForLeaderEpochResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnPartitionResult::AddPartitionsToTxnPartitionResult(int32_t partition_index, int16_t partition_error_code): partition_index_{partition_index}, partition_error_code_{partition_error_code}, tagged_fields_{TaggedFields({})} {};
AddPartitionsToTxnPartitionResult::AddPartitionsToTxnPartitionResult(int32_t partition_index, int16_t partition_error_code, TaggedFields tagged_fields): partition_index_{partition_index}, partition_error_code_{partition_error_code}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnPartitionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(partition_error_code_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnPartitionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnPartitionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(partition_error_code_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnPartitionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnPartitionResult::operator==(const AddPartitionsToTxnPartitionResult& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && partition_error_code_ == rhs.partition_error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnTopicResult::AddPartitionsToTxnTopicResult(std::string name, std::vector<AddPartitionsToTxnPartitionResult> results_by_partition): name_{name}, results_by_partition_{results_by_partition}, tagged_fields_{TaggedFields({})} {};
AddPartitionsToTxnTopicResult::AddPartitionsToTxnTopicResult(std::string name, std::vector<AddPartitionsToTxnPartitionResult> results_by_partition, TaggedFields tagged_fields): name_{name}, results_by_partition_{results_by_partition}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(results_by_partition_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(results_by_partition_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(results_by_partition_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(results_by_partition_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnTopicResult::operator==(const AddPartitionsToTxnTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && results_by_partition_ == rhs.results_by_partition_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnResult::AddPartitionsToTxnResult(std::string transactional_id, std::vector<AddPartitionsToTxnTopicResult> topic_results, TaggedFields tagged_fields): transactional_id_{transactional_id}, topic_results_{topic_results}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(topic_results_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(topic_results_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnResult::operator==(const AddPartitionsToTxnResult& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && topic_results_ == rhs.topic_results_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnResponse::AddPartitionsToTxnResponse(int32_t throttle_time_ms, std::vector<AddPartitionsToTxnTopicResult> results_by_topic_v3_and_below): throttle_time_ms_{throttle_time_ms}, error_code_{0}, results_by_transaction_{std::vector<AddPartitionsToTxnResult>{}}, results_by_topic_v3_and_below_{results_by_topic_v3_and_below}, tagged_fields_{TaggedFields({})} {};
AddPartitionsToTxnResponse::AddPartitionsToTxnResponse(int32_t throttle_time_ms, std::vector<AddPartitionsToTxnTopicResult> results_by_topic_v3_and_below, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{0}, results_by_transaction_{std::vector<AddPartitionsToTxnResult>{}}, results_by_topic_v3_and_below_{results_by_topic_v3_and_below}, tagged_fields_{tagged_fields} {};
AddPartitionsToTxnResponse::AddPartitionsToTxnResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<AddPartitionsToTxnResult> results_by_transaction, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, results_by_transaction_{results_by_transaction}, results_by_topic_v3_and_below_{std::vector<AddPartitionsToTxnTopicResult>{}}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(results_by_transaction_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(results_by_topic_v3_and_below_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(results_by_topic_v3_and_below_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(results_by_transaction_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(results_by_topic_v3_and_below_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(results_by_topic_v3_and_below_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnResponse::operator==(const AddPartitionsToTxnResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && results_by_transaction_ == rhs.results_by_transaction_
  && results_by_topic_v3_and_below_ == rhs.results_by_topic_v3_and_below_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddOffsetsToTxnResponse::AddOffsetsToTxnResponse(int32_t throttle_time_ms, int16_t error_code): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
AddOffsetsToTxnResponse::AddOffsetsToTxnResponse(int32_t throttle_time_ms, int16_t error_code, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t AddOffsetsToTxnResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddOffsetsToTxnResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddOffsetsToTxnResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddOffsetsToTxnResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddOffsetsToTxnResponse::operator==(const AddOffsetsToTxnResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


EndTxnResponse::EndTxnResponse(int32_t throttle_time_ms, int16_t error_code): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
EndTxnResponse::EndTxnResponse(int32_t throttle_time_ms, int16_t error_code, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t EndTxnResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t EndTxnResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndTxnResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t EndTxnResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndTxnResponse::operator==(const EndTxnResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


WritableTxnMarkerPartitionResult::WritableTxnMarkerPartitionResult(int32_t partition_index, int16_t error_code): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
WritableTxnMarkerPartitionResult::WritableTxnMarkerPartitionResult(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t WritableTxnMarkerPartitionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WritableTxnMarkerPartitionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WritableTxnMarkerPartitionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WritableTxnMarkerPartitionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WritableTxnMarkerPartitionResult::operator==(const WritableTxnMarkerPartitionResult& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


WritableTxnMarkerTopicResult::WritableTxnMarkerTopicResult(std::string name, std::vector<WritableTxnMarkerPartitionResult> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
WritableTxnMarkerTopicResult::WritableTxnMarkerTopicResult(std::string name, std::vector<WritableTxnMarkerPartitionResult> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t WritableTxnMarkerTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WritableTxnMarkerTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WritableTxnMarkerTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WritableTxnMarkerTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WritableTxnMarkerTopicResult::operator==(const WritableTxnMarkerTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


WritableTxnMarkerResult::WritableTxnMarkerResult(int64_t producer_id, std::vector<WritableTxnMarkerTopicResult> topics): producer_id_{producer_id}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
WritableTxnMarkerResult::WritableTxnMarkerResult(int64_t producer_id, std::vector<WritableTxnMarkerTopicResult> topics, TaggedFields tagged_fields): producer_id_{producer_id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t WritableTxnMarkerResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WritableTxnMarkerResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WritableTxnMarkerResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WritableTxnMarkerResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WritableTxnMarkerResult::operator==(const WritableTxnMarkerResult& rhs) const {

  return true
  && producer_id_ == rhs.producer_id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


WriteTxnMarkersResponse::WriteTxnMarkersResponse(std::vector<WritableTxnMarkerResult> markers): markers_{markers}, tagged_fields_{TaggedFields({})} {};
WriteTxnMarkersResponse::WriteTxnMarkersResponse(std::vector<WritableTxnMarkerResult> markers, TaggedFields tagged_fields): markers_{markers}, tagged_fields_{tagged_fields} {};


uint32_t WriteTxnMarkersResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(markers_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(markers_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WriteTxnMarkersResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WriteTxnMarkersResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(markers_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(markers_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WriteTxnMarkersResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WriteTxnMarkersResponse::operator==(const WriteTxnMarkersResponse& rhs) const {

  return true
  && markers_ == rhs.markers_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitResponsePartition::TxnOffsetCommitResponsePartition(int32_t partition_index, int16_t error_code): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitResponsePartition::TxnOffsetCommitResponsePartition(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitResponsePartition::operator==(const TxnOffsetCommitResponsePartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitResponseTopic::TxnOffsetCommitResponseTopic(std::string name, std::vector<TxnOffsetCommitResponsePartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitResponseTopic::TxnOffsetCommitResponseTopic(std::string name, std::vector<TxnOffsetCommitResponsePartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitResponseTopic::operator==(const TxnOffsetCommitResponseTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitResponse::TxnOffsetCommitResponse(int32_t throttle_time_ms, std::vector<TxnOffsetCommitResponseTopic> topics): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitResponse::TxnOffsetCommitResponse(int32_t throttle_time_ms, std::vector<TxnOffsetCommitResponseTopic> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TxnOffsetCommitResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitResponse::operator==(const TxnOffsetCommitResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AclDescription::AclDescription(std::string principal, std::string host, int8_t operation, int8_t permission_type): principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
AclDescription::AclDescription(std::string principal, std::string host, int8_t operation, int8_t permission_type, TaggedFields tagged_fields): principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{tagged_fields} {};


uint32_t AclDescription::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(host_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(operation_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(permission_type_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AclDescription::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AclDescription::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(host_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(operation_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(permission_type_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AclDescription::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AclDescription::operator==(const AclDescription& rhs) const {

  return true
  && principal_ == rhs.principal_
  && host_ == rhs.host_
  && operation_ == rhs.operation_
  && permission_type_ == rhs.permission_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeAclsResource::DescribeAclsResource(int8_t resource_type, std::string resource_name, std::vector<AclDescription> acls): resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{3}, acls_{acls}, tagged_fields_{TaggedFields({})} {};
DescribeAclsResource::DescribeAclsResource(int8_t resource_type, std::string resource_name, int8_t pattern_type, std::vector<AclDescription> acls): resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{pattern_type}, acls_{acls}, tagged_fields_{TaggedFields({})} {};
DescribeAclsResource::DescribeAclsResource(int8_t resource_type, std::string resource_name, int8_t pattern_type, std::vector<AclDescription> acls, TaggedFields tagged_fields): resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{pattern_type}, acls_{acls}, tagged_fields_{tagged_fields} {};


uint32_t DescribeAclsResource::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(pattern_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(acls_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(acls_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeAclsResource::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeAclsResource::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(pattern_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(acls_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(acls_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeAclsResource::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeAclsResource::operator==(const DescribeAclsResource& rhs) const {

  return true
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && pattern_type_ == rhs.pattern_type_
  && acls_ == rhs.acls_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeAclsResponse::DescribeAclsResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<DescribeAclsResource> resources): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, resources_{resources}, tagged_fields_{TaggedFields({})} {};
DescribeAclsResponse::DescribeAclsResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<DescribeAclsResource> resources, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, resources_{resources}, tagged_fields_{tagged_fields} {};


uint32_t DescribeAclsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resources_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(resources_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeAclsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeAclsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resources_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(resources_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeAclsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeAclsResponse::operator==(const DescribeAclsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && resources_ == rhs.resources_
  && tagged_fields_ == rhs.tagged_fields_;
};


AclCreationResult::AclCreationResult(int16_t error_code, absl::optional<std::string> error_message): error_code_{error_code}, error_message_{error_message}, tagged_fields_{TaggedFields({})} {};
AclCreationResult::AclCreationResult(int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t AclCreationResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AclCreationResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AclCreationResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AclCreationResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AclCreationResult::operator==(const AclCreationResult& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateAclsResponse::CreateAclsResponse(int32_t throttle_time_ms, std::vector<AclCreationResult> results): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{TaggedFields({})} {};
CreateAclsResponse::CreateAclsResponse(int32_t throttle_time_ms, std::vector<AclCreationResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t CreateAclsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateAclsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateAclsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateAclsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateAclsResponse::operator==(const CreateAclsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteAclsMatchingAcl::DeleteAclsMatchingAcl(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, std::string principal, std::string host, int8_t operation, int8_t permission_type): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{3}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DeleteAclsMatchingAcl::DeleteAclsMatchingAcl(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, int8_t pattern_type, std::string principal, std::string host, int8_t operation, int8_t permission_type): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{pattern_type}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DeleteAclsMatchingAcl::DeleteAclsMatchingAcl(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, int8_t pattern_type, std::string principal, std::string host, int8_t operation, int8_t permission_type, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, pattern_type_{pattern_type}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{tagged_fields} {};


uint32_t DeleteAclsMatchingAcl::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(pattern_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(host_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(operation_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(permission_type_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteAclsMatchingAcl::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteAclsMatchingAcl::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(pattern_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(host_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(operation_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(permission_type_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteAclsMatchingAcl::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteAclsMatchingAcl::operator==(const DeleteAclsMatchingAcl& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && pattern_type_ == rhs.pattern_type_
  && principal_ == rhs.principal_
  && host_ == rhs.host_
  && operation_ == rhs.operation_
  && permission_type_ == rhs.permission_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteAclsFilterResult::DeleteAclsFilterResult(int16_t error_code, absl::optional<std::string> error_message, std::vector<DeleteAclsMatchingAcl> matching_acls): error_code_{error_code}, error_message_{error_message}, matching_acls_{matching_acls}, tagged_fields_{TaggedFields({})} {};
DeleteAclsFilterResult::DeleteAclsFilterResult(int16_t error_code, absl::optional<std::string> error_message, std::vector<DeleteAclsMatchingAcl> matching_acls, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, matching_acls_{matching_acls}, tagged_fields_{tagged_fields} {};


uint32_t DeleteAclsFilterResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(matching_acls_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(matching_acls_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteAclsFilterResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteAclsFilterResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(matching_acls_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(matching_acls_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteAclsFilterResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteAclsFilterResult::operator==(const DeleteAclsFilterResult& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && matching_acls_ == rhs.matching_acls_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteAclsResponse::DeleteAclsResponse(int32_t throttle_time_ms, std::vector<DeleteAclsFilterResult> filter_results): throttle_time_ms_{throttle_time_ms}, filter_results_{filter_results}, tagged_fields_{TaggedFields({})} {};
DeleteAclsResponse::DeleteAclsResponse(int32_t throttle_time_ms, std::vector<DeleteAclsFilterResult> filter_results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, filter_results_{filter_results}, tagged_fields_{tagged_fields} {};


uint32_t DeleteAclsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(filter_results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(filter_results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteAclsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteAclsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(filter_results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(filter_results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteAclsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteAclsResponse::operator==(const DeleteAclsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && filter_results_ == rhs.filter_results_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsSynonym::DescribeConfigsSynonym(std::string name, absl::optional<std::string> value, int8_t source): name_{name}, value_{value}, source_{source}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsSynonym::DescribeConfigsSynonym(std::string name, absl::optional<std::string> value, int8_t source, TaggedFields tagged_fields): name_{name}, value_{value}, source_{source}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsSynonym::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(source_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsSynonym::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsSynonym::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(source_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsSynonym::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsSynonym::operator==(const DescribeConfigsSynonym& rhs) const {

  return true
  && name_ == rhs.name_
  && value_ == rhs.value_
  && source_ == rhs.source_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsResourceResult::DescribeConfigsResourceResult(std::string name, absl::optional<std::string> value, bool read_only, bool is_default, bool is_sensitive): name_{name}, value_{value}, read_only_{read_only}, is_default_{is_default}, config_source_{-1}, is_sensitive_{is_sensitive}, synonyms_{std::vector<DescribeConfigsSynonym>{}}, config_type_{0}, documentation_{{""}}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResourceResult::DescribeConfigsResourceResult(std::string name, absl::optional<std::string> value, bool read_only, int8_t config_source, bool is_sensitive, std::vector<DescribeConfigsSynonym> synonyms): name_{name}, value_{value}, read_only_{read_only}, is_default_{false}, config_source_{config_source}, is_sensitive_{is_sensitive}, synonyms_{synonyms}, config_type_{0}, documentation_{{""}}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResourceResult::DescribeConfigsResourceResult(std::string name, absl::optional<std::string> value, bool read_only, int8_t config_source, bool is_sensitive, std::vector<DescribeConfigsSynonym> synonyms, int8_t config_type, absl::optional<std::string> documentation): name_{name}, value_{value}, read_only_{read_only}, is_default_{false}, config_source_{config_source}, is_sensitive_{is_sensitive}, synonyms_{synonyms}, config_type_{config_type}, documentation_{documentation}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResourceResult::DescribeConfigsResourceResult(std::string name, absl::optional<std::string> value, bool read_only, int8_t config_source, bool is_sensitive, std::vector<DescribeConfigsSynonym> synonyms, int8_t config_type, absl::optional<std::string> documentation, TaggedFields tagged_fields): name_{name}, value_{value}, read_only_{read_only}, is_default_{false}, config_source_{config_source}, is_sensitive_{is_sensitive}, synonyms_{synonyms}, config_type_{config_type}, documentation_{documentation}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsResourceResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(read_only_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(is_default_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(config_source_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(is_sensitive_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(synonyms_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(synonyms_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(config_type_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(documentation_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(documentation_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsResourceResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsResourceResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(read_only_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(is_default_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(config_source_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(is_sensitive_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(synonyms_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(synonyms_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(config_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(documentation_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(documentation_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsResourceResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsResourceResult::operator==(const DescribeConfigsResourceResult& rhs) const {

  return true
  && name_ == rhs.name_
  && value_ == rhs.value_
  && read_only_ == rhs.read_only_
  && is_default_ == rhs.is_default_
  && config_source_ == rhs.config_source_
  && is_sensitive_ == rhs.is_sensitive_
  && synonyms_ == rhs.synonyms_
  && config_type_ == rhs.config_type_
  && documentation_ == rhs.documentation_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsResult::DescribeConfigsResult(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, std::vector<DescribeConfigsResourceResult> configs): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResult::DescribeConfigsResult(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, std::vector<DescribeConfigsResourceResult> configs, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(configs_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(configs_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(configs_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(configs_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsResult::operator==(const DescribeConfigsResult& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && configs_ == rhs.configs_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsResponse::DescribeConfigsResponse(int32_t throttle_time_ms, std::vector<DescribeConfigsResult> results): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResponse::DescribeConfigsResponse(int32_t throttle_time_ms, std::vector<DescribeConfigsResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsResponse::operator==(const DescribeConfigsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterConfigsResourceResponse::AlterConfigsResourceResponse(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, tagged_fields_{TaggedFields({})} {};
AlterConfigsResourceResponse::AlterConfigsResourceResponse(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, tagged_fields_{tagged_fields} {};


uint32_t AlterConfigsResourceResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterConfigsResourceResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterConfigsResourceResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterConfigsResourceResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterConfigsResourceResponse::operator==(const AlterConfigsResourceResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterConfigsResponse::AlterConfigsResponse(int32_t throttle_time_ms, std::vector<AlterConfigsResourceResponse> responses): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
AlterConfigsResponse::AlterConfigsResponse(int32_t throttle_time_ms, std::vector<AlterConfigsResourceResponse> responses, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{tagged_fields} {};


uint32_t AlterConfigsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(responses_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterConfigsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterConfigsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(responses_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterConfigsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterConfigsResponse::operator==(const AlterConfigsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && responses_ == rhs.responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDirPartitionResult::AlterReplicaLogDirPartitionResult(int32_t partition_index, int16_t error_code): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDirPartitionResult::AlterReplicaLogDirPartitionResult(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDirPartitionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirPartitionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDirPartitionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirPartitionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDirPartitionResult::operator==(const AlterReplicaLogDirPartitionResult& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDirTopicResult::AlterReplicaLogDirTopicResult(std::string topic_name, std::vector<AlterReplicaLogDirPartitionResult> partitions): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDirTopicResult::AlterReplicaLogDirTopicResult(std::string topic_name, std::vector<AlterReplicaLogDirPartitionResult> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDirTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDirTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDirTopicResult::operator==(const AlterReplicaLogDirTopicResult& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDirsResponse::AlterReplicaLogDirsResponse(int32_t throttle_time_ms, std::vector<AlterReplicaLogDirTopicResult> results): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDirsResponse::AlterReplicaLogDirsResponse(int32_t throttle_time_ms, std::vector<AlterReplicaLogDirTopicResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDirsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDirsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDirsResponse::operator==(const AlterReplicaLogDirsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeLogDirsPartition::DescribeLogDirsPartition(int32_t partition_index, int64_t partition_size, int64_t offset_lag, bool is_future_key): partition_index_{partition_index}, partition_size_{partition_size}, offset_lag_{offset_lag}, is_future_key_{is_future_key}, tagged_fields_{TaggedFields({})} {};
DescribeLogDirsPartition::DescribeLogDirsPartition(int32_t partition_index, int64_t partition_size, int64_t offset_lag, bool is_future_key, TaggedFields tagged_fields): partition_index_{partition_index}, partition_size_{partition_size}, offset_lag_{offset_lag}, is_future_key_{is_future_key}, tagged_fields_{tagged_fields} {};


uint32_t DescribeLogDirsPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_size_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(offset_lag_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(is_future_key_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeLogDirsPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeLogDirsPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_size_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(offset_lag_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(is_future_key_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeLogDirsPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeLogDirsPartition::operator==(const DescribeLogDirsPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && partition_size_ == rhs.partition_size_
  && offset_lag_ == rhs.offset_lag_
  && is_future_key_ == rhs.is_future_key_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeLogDirsTopic::DescribeLogDirsTopic(std::string name, std::vector<DescribeLogDirsPartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
DescribeLogDirsTopic::DescribeLogDirsTopic(std::string name, std::vector<DescribeLogDirsPartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DescribeLogDirsTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeLogDirsTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeLogDirsTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeLogDirsTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeLogDirsTopic::operator==(const DescribeLogDirsTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeLogDirsResult::DescribeLogDirsResult(int16_t error_code, std::string log_dir, std::vector<DescribeLogDirsTopic> topics): error_code_{error_code}, log_dir_{log_dir}, topics_{topics}, total_bytes_{-1}, usable_bytes_{-1}, tagged_fields_{TaggedFields({})} {};
DescribeLogDirsResult::DescribeLogDirsResult(int16_t error_code, std::string log_dir, std::vector<DescribeLogDirsTopic> topics, TaggedFields tagged_fields): error_code_{error_code}, log_dir_{log_dir}, topics_{topics}, total_bytes_{-1}, usable_bytes_{-1}, tagged_fields_{tagged_fields} {};
DescribeLogDirsResult::DescribeLogDirsResult(int16_t error_code, std::string log_dir, std::vector<DescribeLogDirsTopic> topics, int64_t total_bytes, int64_t usable_bytes, TaggedFields tagged_fields): error_code_{error_code}, log_dir_{log_dir}, topics_{topics}, total_bytes_{total_bytes}, usable_bytes_{usable_bytes}, tagged_fields_{tagged_fields} {};


uint32_t DescribeLogDirsResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(log_dir_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(log_dir_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeSize(total_bytes_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeSize(usable_bytes_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeLogDirsResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeLogDirsResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(log_dir_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(log_dir_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encode(total_bytes_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encode(usable_bytes_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeLogDirsResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeLogDirsResult::operator==(const DescribeLogDirsResult& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && log_dir_ == rhs.log_dir_
  && topics_ == rhs.topics_
  && total_bytes_ == rhs.total_bytes_
  && usable_bytes_ == rhs.usable_bytes_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeLogDirsResponse::DescribeLogDirsResponse(int32_t throttle_time_ms, std::vector<DescribeLogDirsResult> results): throttle_time_ms_{throttle_time_ms}, error_code_{0}, results_{results}, tagged_fields_{TaggedFields({})} {};
DescribeLogDirsResponse::DescribeLogDirsResponse(int32_t throttle_time_ms, std::vector<DescribeLogDirsResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{0}, results_{results}, tagged_fields_{tagged_fields} {};
DescribeLogDirsResponse::DescribeLogDirsResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<DescribeLogDirsResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t DescribeLogDirsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeLogDirsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeLogDirsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeLogDirsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeLogDirsResponse::operator==(const DescribeLogDirsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


SaslAuthenticateResponse::SaslAuthenticateResponse(int16_t error_code, absl::optional<std::string> error_message, Bytes auth_bytes): error_code_{error_code}, error_message_{error_message}, auth_bytes_{auth_bytes}, session_lifetime_ms_{0}, tagged_fields_{TaggedFields({})} {};
SaslAuthenticateResponse::SaslAuthenticateResponse(int16_t error_code, absl::optional<std::string> error_message, Bytes auth_bytes, int64_t session_lifetime_ms): error_code_{error_code}, error_message_{error_message}, auth_bytes_{auth_bytes}, session_lifetime_ms_{session_lifetime_ms}, tagged_fields_{TaggedFields({})} {};
SaslAuthenticateResponse::SaslAuthenticateResponse(int16_t error_code, absl::optional<std::string> error_message, Bytes auth_bytes, int64_t session_lifetime_ms, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, auth_bytes_{auth_bytes}, session_lifetime_ms_{session_lifetime_ms}, tagged_fields_{tagged_fields} {};


uint32_t SaslAuthenticateResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(auth_bytes_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(auth_bytes_);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.computeSize(session_lifetime_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t SaslAuthenticateResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SaslAuthenticateResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(auth_bytes_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(auth_bytes_, dst);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.encode(session_lifetime_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t SaslAuthenticateResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SaslAuthenticateResponse::operator==(const SaslAuthenticateResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && auth_bytes_ == rhs.auth_bytes_
  && session_lifetime_ms_ == rhs.session_lifetime_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatePartitionsTopicResult::CreatePartitionsTopicResult(std::string name, int16_t error_code, absl::optional<std::string> error_message): name_{name}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{TaggedFields({})} {};
CreatePartitionsTopicResult::CreatePartitionsTopicResult(std::string name, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): name_{name}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t CreatePartitionsTopicResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatePartitionsTopicResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatePartitionsTopicResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatePartitionsTopicResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatePartitionsTopicResult::operator==(const CreatePartitionsTopicResult& rhs) const {

  return true
  && name_ == rhs.name_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatePartitionsResponse::CreatePartitionsResponse(int32_t throttle_time_ms, std::vector<CreatePartitionsTopicResult> results): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{TaggedFields({})} {};
CreatePartitionsResponse::CreatePartitionsResponse(int32_t throttle_time_ms, std::vector<CreatePartitionsTopicResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t CreatePartitionsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatePartitionsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatePartitionsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatePartitionsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatePartitionsResponse::operator==(const CreatePartitionsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateDelegationTokenResponse::CreateDelegationTokenResponse(int16_t error_code, std::string principal_type, std::string principal_name, int64_t issue_timestamp_ms, int64_t expiry_timestamp_ms, int64_t max_timestamp_ms, std::string token_id, Bytes hmac, int32_t throttle_time_ms): error_code_{error_code}, principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{""}, token_requester_principal_name_{""}, issue_timestamp_ms_{issue_timestamp_ms}, expiry_timestamp_ms_{expiry_timestamp_ms}, max_timestamp_ms_{max_timestamp_ms}, token_id_{token_id}, hmac_{hmac}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
CreateDelegationTokenResponse::CreateDelegationTokenResponse(int16_t error_code, std::string principal_type, std::string principal_name, int64_t issue_timestamp_ms, int64_t expiry_timestamp_ms, int64_t max_timestamp_ms, std::string token_id, Bytes hmac, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{""}, token_requester_principal_name_{""}, issue_timestamp_ms_{issue_timestamp_ms}, expiry_timestamp_ms_{expiry_timestamp_ms}, max_timestamp_ms_{max_timestamp_ms}, token_id_{token_id}, hmac_{hmac}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};
CreateDelegationTokenResponse::CreateDelegationTokenResponse(int16_t error_code, std::string principal_type, std::string principal_name, std::string token_requester_principal_type, std::string token_requester_principal_name, int64_t issue_timestamp_ms, int64_t expiry_timestamp_ms, int64_t max_timestamp_ms, std::string token_id, Bytes hmac, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{token_requester_principal_type}, token_requester_principal_name_{token_requester_principal_name}, issue_timestamp_ms_{issue_timestamp_ms}, expiry_timestamp_ms_{expiry_timestamp_ms}, max_timestamp_ms_{max_timestamp_ms}, token_id_{token_id}, hmac_{hmac}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t CreateDelegationTokenResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_type_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_name_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(token_requester_principal_type_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(token_requester_principal_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(issue_timestamp_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(expiry_timestamp_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(max_timestamp_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(token_id_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(token_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(hmac_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(hmac_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateDelegationTokenResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateDelegationTokenResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_type_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_name_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(token_requester_principal_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(token_requester_principal_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(issue_timestamp_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(expiry_timestamp_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(max_timestamp_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(token_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(token_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(hmac_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(hmac_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateDelegationTokenResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateDelegationTokenResponse::operator==(const CreateDelegationTokenResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && principal_type_ == rhs.principal_type_
  && principal_name_ == rhs.principal_name_
  && token_requester_principal_type_ == rhs.token_requester_principal_type_
  && token_requester_principal_name_ == rhs.token_requester_principal_name_
  && issue_timestamp_ms_ == rhs.issue_timestamp_ms_
  && expiry_timestamp_ms_ == rhs.expiry_timestamp_ms_
  && max_timestamp_ms_ == rhs.max_timestamp_ms_
  && token_id_ == rhs.token_id_
  && hmac_ == rhs.hmac_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


RenewDelegationTokenResponse::RenewDelegationTokenResponse(int16_t error_code, int64_t expiry_timestamp_ms, int32_t throttle_time_ms): error_code_{error_code}, expiry_timestamp_ms_{expiry_timestamp_ms}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
RenewDelegationTokenResponse::RenewDelegationTokenResponse(int16_t error_code, int64_t expiry_timestamp_ms, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, expiry_timestamp_ms_{expiry_timestamp_ms}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t RenewDelegationTokenResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(expiry_timestamp_ms_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t RenewDelegationTokenResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RenewDelegationTokenResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(expiry_timestamp_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t RenewDelegationTokenResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RenewDelegationTokenResponse::operator==(const RenewDelegationTokenResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && expiry_timestamp_ms_ == rhs.expiry_timestamp_ms_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


ExpireDelegationTokenResponse::ExpireDelegationTokenResponse(int16_t error_code, int64_t expiry_timestamp_ms, int32_t throttle_time_ms): error_code_{error_code}, expiry_timestamp_ms_{expiry_timestamp_ms}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
ExpireDelegationTokenResponse::ExpireDelegationTokenResponse(int16_t error_code, int64_t expiry_timestamp_ms, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, expiry_timestamp_ms_{expiry_timestamp_ms}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t ExpireDelegationTokenResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(expiry_timestamp_ms_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ExpireDelegationTokenResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ExpireDelegationTokenResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(expiry_timestamp_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ExpireDelegationTokenResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ExpireDelegationTokenResponse::operator==(const ExpireDelegationTokenResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && expiry_timestamp_ms_ == rhs.expiry_timestamp_ms_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribedDelegationTokenRenewer::DescribedDelegationTokenRenewer(std::string principal_type, std::string principal_name): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{TaggedFields({})} {};
DescribedDelegationTokenRenewer::DescribedDelegationTokenRenewer(std::string principal_type, std::string principal_name, TaggedFields tagged_fields): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{tagged_fields} {};


uint32_t DescribedDelegationTokenRenewer::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_type_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribedDelegationTokenRenewer::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribedDelegationTokenRenewer::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_type_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribedDelegationTokenRenewer::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribedDelegationTokenRenewer::operator==(const DescribedDelegationTokenRenewer& rhs) const {

  return true
  && principal_type_ == rhs.principal_type_
  && principal_name_ == rhs.principal_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribedDelegationToken::DescribedDelegationToken(std::string principal_type, std::string principal_name, int64_t issue_timestamp, int64_t expiry_timestamp, int64_t max_timestamp, std::string token_id, Bytes hmac, std::vector<DescribedDelegationTokenRenewer> renewers): principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{""}, token_requester_principal_name_{""}, issue_timestamp_{issue_timestamp}, expiry_timestamp_{expiry_timestamp}, max_timestamp_{max_timestamp}, token_id_{token_id}, hmac_{hmac}, renewers_{renewers}, tagged_fields_{TaggedFields({})} {};
DescribedDelegationToken::DescribedDelegationToken(std::string principal_type, std::string principal_name, int64_t issue_timestamp, int64_t expiry_timestamp, int64_t max_timestamp, std::string token_id, Bytes hmac, std::vector<DescribedDelegationTokenRenewer> renewers, TaggedFields tagged_fields): principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{""}, token_requester_principal_name_{""}, issue_timestamp_{issue_timestamp}, expiry_timestamp_{expiry_timestamp}, max_timestamp_{max_timestamp}, token_id_{token_id}, hmac_{hmac}, renewers_{renewers}, tagged_fields_{tagged_fields} {};
DescribedDelegationToken::DescribedDelegationToken(std::string principal_type, std::string principal_name, std::string token_requester_principal_type, std::string token_requester_principal_name, int64_t issue_timestamp, int64_t expiry_timestamp, int64_t max_timestamp, std::string token_id, Bytes hmac, std::vector<DescribedDelegationTokenRenewer> renewers, TaggedFields tagged_fields): principal_type_{principal_type}, principal_name_{principal_name}, token_requester_principal_type_{token_requester_principal_type}, token_requester_principal_name_{token_requester_principal_name}, issue_timestamp_{issue_timestamp}, expiry_timestamp_{expiry_timestamp}, max_timestamp_{max_timestamp}, token_id_{token_id}, hmac_{hmac}, renewers_{renewers}, tagged_fields_{tagged_fields} {};


uint32_t DescribedDelegationToken::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_type_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_name_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(token_requester_principal_type_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(token_requester_principal_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(issue_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(expiry_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(max_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(token_id_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(token_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(hmac_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(hmac_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(renewers_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(renewers_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribedDelegationToken::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribedDelegationToken::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_type_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_name_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(token_requester_principal_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(token_requester_principal_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(issue_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(expiry_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(max_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(token_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(token_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(hmac_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(hmac_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(renewers_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(renewers_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribedDelegationToken::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribedDelegationToken::operator==(const DescribedDelegationToken& rhs) const {

  return true
  && principal_type_ == rhs.principal_type_
  && principal_name_ == rhs.principal_name_
  && token_requester_principal_type_ == rhs.token_requester_principal_type_
  && token_requester_principal_name_ == rhs.token_requester_principal_name_
  && issue_timestamp_ == rhs.issue_timestamp_
  && expiry_timestamp_ == rhs.expiry_timestamp_
  && max_timestamp_ == rhs.max_timestamp_
  && token_id_ == rhs.token_id_
  && hmac_ == rhs.hmac_
  && renewers_ == rhs.renewers_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeDelegationTokenResponse::DescribeDelegationTokenResponse(int16_t error_code, std::vector<DescribedDelegationToken> tokens, int32_t throttle_time_ms): error_code_{error_code}, tokens_{tokens}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{TaggedFields({})} {};
DescribeDelegationTokenResponse::DescribeDelegationTokenResponse(int16_t error_code, std::vector<DescribedDelegationToken> tokens, int32_t throttle_time_ms, TaggedFields tagged_fields): error_code_{error_code}, tokens_{tokens}, throttle_time_ms_{throttle_time_ms}, tagged_fields_{tagged_fields} {};


uint32_t DescribeDelegationTokenResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(tokens_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tokens_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeDelegationTokenResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeDelegationTokenResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(tokens_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tokens_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeDelegationTokenResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeDelegationTokenResponse::operator==(const DescribeDelegationTokenResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && tokens_ == rhs.tokens_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeletableGroupResult::DeletableGroupResult(std::string group_id, int16_t error_code): group_id_{group_id}, error_code_{error_code}, tagged_fields_{TaggedFields({})} {};
DeletableGroupResult::DeletableGroupResult(std::string group_id, int16_t error_code, TaggedFields tagged_fields): group_id_{group_id}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t DeletableGroupResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeletableGroupResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeletableGroupResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeletableGroupResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeletableGroupResult::operator==(const DeletableGroupResult& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteGroupsResponse::DeleteGroupsResponse(int32_t throttle_time_ms, std::vector<DeletableGroupResult> results): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{TaggedFields({})} {};
DeleteGroupsResponse::DeleteGroupsResponse(int32_t throttle_time_ms, std::vector<DeletableGroupResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t DeleteGroupsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteGroupsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteGroupsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteGroupsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteGroupsResponse::operator==(const DeleteGroupsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


PartitionResult::PartitionResult(int32_t partition_id, int16_t error_code, absl::optional<std::string> error_message): partition_id_{partition_id}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{TaggedFields({})} {};
PartitionResult::PartitionResult(int32_t partition_id, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): partition_id_{partition_id}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t PartitionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partition_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t PartitionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t PartitionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partition_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t PartitionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool PartitionResult::operator==(const PartitionResult& rhs) const {

  return true
  && partition_id_ == rhs.partition_id_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


ReplicaElectionResult::ReplicaElectionResult(std::string topic, std::vector<PartitionResult> partition_result): topic_{topic}, partition_result_{partition_result}, tagged_fields_{TaggedFields({})} {};
ReplicaElectionResult::ReplicaElectionResult(std::string topic, std::vector<PartitionResult> partition_result, TaggedFields tagged_fields): topic_{topic}, partition_result_{partition_result}, tagged_fields_{tagged_fields} {};


uint32_t ReplicaElectionResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topic_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partition_result_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(partition_result_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ReplicaElectionResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReplicaElectionResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topic_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partition_result_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(partition_result_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ReplicaElectionResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReplicaElectionResult::operator==(const ReplicaElectionResult& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partition_result_ == rhs.partition_result_
  && tagged_fields_ == rhs.tagged_fields_;
};


ElectLeadersResponse::ElectLeadersResponse(int32_t throttle_time_ms, std::vector<ReplicaElectionResult> replica_election_results): throttle_time_ms_{throttle_time_ms}, error_code_{0}, replica_election_results_{replica_election_results}, tagged_fields_{TaggedFields({})} {};
ElectLeadersResponse::ElectLeadersResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ReplicaElectionResult> replica_election_results): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, replica_election_results_{replica_election_results}, tagged_fields_{TaggedFields({})} {};
ElectLeadersResponse::ElectLeadersResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ReplicaElectionResult> replica_election_results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, replica_election_results_{replica_election_results}, tagged_fields_{tagged_fields} {};


uint32_t ElectLeadersResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(replica_election_results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(replica_election_results_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ElectLeadersResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ElectLeadersResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(replica_election_results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(replica_election_results_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ElectLeadersResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ElectLeadersResponse::operator==(const ElectLeadersResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && replica_election_results_ == rhs.replica_election_results_
  && tagged_fields_ == rhs.tagged_fields_;
};


IncrementalAlterConfigsResponseAlterConfigsResourceResponse::IncrementalAlterConfigsResponseAlterConfigsResourceResponse(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, tagged_fields_{TaggedFields({})} {};
IncrementalAlterConfigsResponseAlterConfigsResourceResponse::IncrementalAlterConfigsResponseAlterConfigsResourceResponse(int16_t error_code, absl::optional<std::string> error_message, int8_t resource_type, std::string resource_name, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, resource_type_{resource_type}, resource_name_{resource_name}, tagged_fields_{tagged_fields} {};


uint32_t IncrementalAlterConfigsResponseAlterConfigsResourceResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsResponseAlterConfigsResourceResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t IncrementalAlterConfigsResponseAlterConfigsResourceResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsResponseAlterConfigsResourceResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool IncrementalAlterConfigsResponseAlterConfigsResourceResponse::operator==(const IncrementalAlterConfigsResponseAlterConfigsResourceResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


IncrementalAlterConfigsResponse::IncrementalAlterConfigsResponse(int32_t throttle_time_ms, std::vector<IncrementalAlterConfigsResponseAlterConfigsResourceResponse> responses): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{TaggedFields({})} {};
IncrementalAlterConfigsResponse::IncrementalAlterConfigsResponse(int32_t throttle_time_ms, std::vector<IncrementalAlterConfigsResponseAlterConfigsResourceResponse> responses, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, responses_{responses}, tagged_fields_{tagged_fields} {};


uint32_t IncrementalAlterConfigsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(responses_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t IncrementalAlterConfigsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(responses_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool IncrementalAlterConfigsResponse::operator==(const IncrementalAlterConfigsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && responses_ == rhs.responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


ReassignablePartitionResponse::ReassignablePartitionResponse(int32_t partition_index, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t ReassignablePartitionResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ReassignablePartitionResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReassignablePartitionResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ReassignablePartitionResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReassignablePartitionResponse::operator==(const ReassignablePartitionResponse& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


ReassignableTopicResponse::ReassignableTopicResponse(std::string name, std::vector<ReassignablePartitionResponse> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ReassignableTopicResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ReassignableTopicResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReassignableTopicResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ReassignableTopicResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReassignableTopicResponse::operator==(const ReassignableTopicResponse& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterPartitionReassignmentsResponse::AlterPartitionReassignmentsResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<ReassignableTopicResponse> responses, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, responses_{responses}, tagged_fields_{tagged_fields} {};


uint32_t AlterPartitionReassignmentsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(responses_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterPartitionReassignmentsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterPartitionReassignmentsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(responses_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterPartitionReassignmentsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterPartitionReassignmentsResponse::operator==(const AlterPartitionReassignmentsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && responses_ == rhs.responses_
  && tagged_fields_ == rhs.tagged_fields_;
};


OngoingPartitionReassignment::OngoingPartitionReassignment(int32_t partition_index, std::vector<int32_t> replicas, std::vector<int32_t> adding_replicas, std::vector<int32_t> removing_replicas, TaggedFields tagged_fields): partition_index_{partition_index}, replicas_{replicas}, adding_replicas_{adding_replicas}, removing_replicas_{removing_replicas}, tagged_fields_{tagged_fields} {};


uint32_t OngoingPartitionReassignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(adding_replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(removing_replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OngoingPartitionReassignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OngoingPartitionReassignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(adding_replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(removing_replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OngoingPartitionReassignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OngoingPartitionReassignment::operator==(const OngoingPartitionReassignment& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && replicas_ == rhs.replicas_
  && adding_replicas_ == rhs.adding_replicas_
  && removing_replicas_ == rhs.removing_replicas_
  && tagged_fields_ == rhs.tagged_fields_;
};


OngoingTopicReassignment::OngoingTopicReassignment(std::string name, std::vector<OngoingPartitionReassignment> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OngoingTopicReassignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OngoingTopicReassignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OngoingTopicReassignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OngoingTopicReassignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OngoingTopicReassignment::operator==(const OngoingTopicReassignment& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListPartitionReassignmentsResponse::ListPartitionReassignmentsResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<OngoingTopicReassignment> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t ListPartitionReassignmentsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListPartitionReassignmentsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListPartitionReassignmentsResponse::operator==(const ListPartitionReassignmentsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetDeleteResponsePartition::OffsetDeleteResponsePartition(int32_t partition_index, int16_t error_code): partition_index_{partition_index}, error_code_{error_code} {};


uint32_t OffsetDeleteResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  

  return written;
}

uint32_t OffsetDeleteResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  

  return written;
}

uint32_t OffsetDeleteResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteResponsePartition::operator==(const OffsetDeleteResponsePartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_;
};


OffsetDeleteResponseTopic::OffsetDeleteResponseTopic(std::string name, std::vector<OffsetDeleteResponsePartition> partitions): name_{name}, partitions_{partitions} {};


uint32_t OffsetDeleteResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partitions_);
  }
  

  return written;
}

uint32_t OffsetDeleteResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partitions_, dst);
  }
  

  return written;
}

uint32_t OffsetDeleteResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteResponseTopic::operator==(const OffsetDeleteResponseTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_;
};


OffsetDeleteResponse::OffsetDeleteResponse(int16_t error_code, int32_t throttle_time_ms, std::vector<OffsetDeleteResponseTopic> topics): error_code_{error_code}, throttle_time_ms_{throttle_time_ms}, topics_{topics} {};


uint32_t OffsetDeleteResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t OffsetDeleteResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t OffsetDeleteResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteResponse::operator==(const OffsetDeleteResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_;
};


DescribeClientQuotasResponseResponseEntityData::DescribeClientQuotasResponseResponseEntityData(std::string entity_type, absl::optional<std::string> entity_name): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{TaggedFields({})} {};
DescribeClientQuotasResponseResponseEntityData::DescribeClientQuotasResponseResponseEntityData(std::string entity_type, absl::optional<std::string> entity_name, TaggedFields tagged_fields): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClientQuotasResponseResponseEntityData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_type_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_type_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponseResponseEntityData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClientQuotasResponseResponseEntityData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_type_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponseResponseEntityData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClientQuotasResponseResponseEntityData::operator==(const DescribeClientQuotasResponseResponseEntityData& rhs) const {

  return true
  && entity_type_ == rhs.entity_type_
  && entity_name_ == rhs.entity_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


ValueData::ValueData(std::string key, double value): key_{key}, value_{value}, tagged_fields_{TaggedFields({})} {};
ValueData::ValueData(std::string key, double value, TaggedFields tagged_fields): key_{key}, value_{value}, tagged_fields_{tagged_fields} {};


uint32_t ValueData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(key_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(key_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ValueData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ValueData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(key_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(key_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ValueData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ValueData::operator==(const ValueData& rhs) const {

  return true
  && key_ == rhs.key_
  && value_ == rhs.value_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClientQuotasResponseResponseEntryData::DescribeClientQuotasResponseResponseEntryData(std::vector<DescribeClientQuotasResponseResponseEntityData> entity, std::vector<ValueData> values): entity_{entity}, values_{values}, tagged_fields_{TaggedFields({})} {};
DescribeClientQuotasResponseResponseEntryData::DescribeClientQuotasResponseResponseEntryData(std::vector<DescribeClientQuotasResponseResponseEntityData> entity, std::vector<ValueData> values, TaggedFields tagged_fields): entity_{entity}, values_{values}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClientQuotasResponseResponseEntryData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(values_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(values_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponseResponseEntryData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClientQuotasResponseResponseEntryData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(values_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(values_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponseResponseEntryData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClientQuotasResponseResponseEntryData::operator==(const DescribeClientQuotasResponseResponseEntryData& rhs) const {

  return true
  && entity_ == rhs.entity_
  && values_ == rhs.values_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClientQuotasResponse::DescribeClientQuotasResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, absl::optional<std::vector<DescribeClientQuotasResponseResponseEntryData>> entries): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, entries_{entries}, tagged_fields_{TaggedFields({})} {};
DescribeClientQuotasResponse::DescribeClientQuotasResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, absl::optional<std::vector<DescribeClientQuotasResponseResponseEntryData>> entries, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, entries_{entries}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClientQuotasResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entries_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entries_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClientQuotasResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entries_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entries_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClientQuotasResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClientQuotasResponse::operator==(const DescribeClientQuotasResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && entries_ == rhs.entries_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseEntityData::ResponseEntityData(std::string entity_type, absl::optional<std::string> entity_name): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{TaggedFields({})} {};
ResponseEntityData::ResponseEntityData(std::string entity_type, absl::optional<std::string> entity_name, TaggedFields tagged_fields): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{tagged_fields} {};


uint32_t ResponseEntityData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_type_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_type_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseEntityData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseEntityData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_type_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseEntityData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseEntityData::operator==(const ResponseEntityData& rhs) const {

  return true
  && entity_type_ == rhs.entity_type_
  && entity_name_ == rhs.entity_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseEntryData::ResponseEntryData(int16_t error_code, absl::optional<std::string> error_message, std::vector<ResponseEntityData> entity): error_code_{error_code}, error_message_{error_message}, entity_{entity}, tagged_fields_{TaggedFields({})} {};
ResponseEntryData::ResponseEntryData(int16_t error_code, absl::optional<std::string> error_message, std::vector<ResponseEntityData> entity, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, entity_{entity}, tagged_fields_{tagged_fields} {};


uint32_t ResponseEntryData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_message_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseEntryData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseEntryData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_message_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseEntryData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseEntryData::operator==(const ResponseEntryData& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && entity_ == rhs.entity_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterClientQuotasResponse::AlterClientQuotasResponse(int32_t throttle_time_ms, std::vector<ResponseEntryData> entries): throttle_time_ms_{throttle_time_ms}, entries_{entries}, tagged_fields_{TaggedFields({})} {};
AlterClientQuotasResponse::AlterClientQuotasResponse(int32_t throttle_time_ms, std::vector<ResponseEntryData> entries, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, entries_{entries}, tagged_fields_{tagged_fields} {};


uint32_t AlterClientQuotasResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entries_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entries_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterClientQuotasResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterClientQuotasResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entries_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entries_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterClientQuotasResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterClientQuotasResponse::operator==(const AlterClientQuotasResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && entries_ == rhs.entries_
  && tagged_fields_ == rhs.tagged_fields_;
};


CredentialInfo::CredentialInfo(int8_t mechanism, int32_t iterations, TaggedFields tagged_fields): mechanism_{mechanism}, iterations_{iterations}, tagged_fields_{tagged_fields} {};


uint32_t CredentialInfo::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(mechanism_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(iterations_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CredentialInfo::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CredentialInfo::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(mechanism_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(iterations_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CredentialInfo::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CredentialInfo::operator==(const CredentialInfo& rhs) const {

  return true
  && mechanism_ == rhs.mechanism_
  && iterations_ == rhs.iterations_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeUserScramCredentialsResult::DescribeUserScramCredentialsResult(std::string user, int16_t error_code, absl::optional<std::string> error_message, std::vector<CredentialInfo> credential_infos, TaggedFields tagged_fields): user_{user}, error_code_{error_code}, error_message_{error_message}, credential_infos_{credential_infos}, tagged_fields_{tagged_fields} {};


uint32_t DescribeUserScramCredentialsResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(user_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(credential_infos_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeUserScramCredentialsResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(user_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(credential_infos_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeUserScramCredentialsResult::operator==(const DescribeUserScramCredentialsResult& rhs) const {

  return true
  && user_ == rhs.user_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && credential_infos_ == rhs.credential_infos_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeUserScramCredentialsResponse::DescribeUserScramCredentialsResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<DescribeUserScramCredentialsResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t DescribeUserScramCredentialsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeUserScramCredentialsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeUserScramCredentialsResponse::operator==(const DescribeUserScramCredentialsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterUserScramCredentialsResult::AlterUserScramCredentialsResult(std::string user, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): user_{user}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t AlterUserScramCredentialsResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(user_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterUserScramCredentialsResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(user_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterUserScramCredentialsResult::operator==(const AlterUserScramCredentialsResult& rhs) const {

  return true
  && user_ == rhs.user_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterUserScramCredentialsResponse::AlterUserScramCredentialsResponse(int32_t throttle_time_ms, std::vector<AlterUserScramCredentialsResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t AlterUserScramCredentialsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterUserScramCredentialsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterUserScramCredentialsResponse::operator==(const AlterUserScramCredentialsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteResponseResponsePartitionData::VoteResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch, bool vote_granted, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, vote_granted_{vote_granted}, tagged_fields_{tagged_fields} {};


uint32_t VoteResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(vote_granted_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t VoteResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(vote_granted_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t VoteResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteResponseResponsePartitionData::operator==(const VoteResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && vote_granted_ == rhs.vote_granted_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteResponseResponseTopicData::VoteResponseResponseTopicData(std::string topic_name, std::vector<VoteResponseResponsePartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t VoteResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t VoteResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t VoteResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteResponseResponseTopicData::operator==(const VoteResponseResponseTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteResponse::VoteResponse(int16_t error_code, std::vector<VoteResponseResponseTopicData> topics, TaggedFields tagged_fields): error_code_{error_code}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t VoteResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t VoteResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t VoteResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteResponse::operator==(const VoteResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


BeginQuorumEpochResponseResponsePartitionData::BeginQuorumEpochResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch} {};


uint32_t BeginQuorumEpochResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_epoch_);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_epoch_, dst);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochResponseResponsePartitionData::operator==(const BeginQuorumEpochResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_;
};


BeginQuorumEpochResponseResponseTopicData::BeginQuorumEpochResponseResponseTopicData(std::string topic_name, std::vector<BeginQuorumEpochResponseResponsePartitionData> partitions): topic_name_{topic_name}, partitions_{partitions} {};


uint32_t BeginQuorumEpochResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partitions_);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partitions_, dst);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochResponseResponseTopicData::operator==(const BeginQuorumEpochResponseResponseTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_;
};


BeginQuorumEpochResponse::BeginQuorumEpochResponse(int16_t error_code, std::vector<BeginQuorumEpochResponseResponseTopicData> topics): error_code_{error_code}, topics_{topics} {};


uint32_t BeginQuorumEpochResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t BeginQuorumEpochResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochResponse::operator==(const BeginQuorumEpochResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_;
};


EndQuorumEpochResponseResponsePartitionData::EndQuorumEpochResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch} {};


uint32_t EndQuorumEpochResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_epoch_);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_epoch_, dst);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochResponseResponsePartitionData::operator==(const EndQuorumEpochResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_;
};


EndQuorumEpochResponseResponseTopicData::EndQuorumEpochResponseResponseTopicData(std::string topic_name, std::vector<EndQuorumEpochResponseResponsePartitionData> partitions): topic_name_{topic_name}, partitions_{partitions} {};


uint32_t EndQuorumEpochResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partitions_);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partitions_, dst);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochResponseResponseTopicData::operator==(const EndQuorumEpochResponseResponseTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_;
};


EndQuorumEpochResponse::EndQuorumEpochResponse(int16_t error_code, std::vector<EndQuorumEpochResponseResponseTopicData> topics): error_code_{error_code}, topics_{topics} {};


uint32_t EndQuorumEpochResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t EndQuorumEpochResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochResponse::operator==(const EndQuorumEpochResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_;
};


ReplicaState::ReplicaState(int32_t replica_id, int64_t log_end_offset, TaggedFields tagged_fields): replica_id_{replica_id}, log_end_offset_{log_end_offset}, last_fetch_timestamp_{-1}, last_caught_up_timestamp_{-1}, tagged_fields_{tagged_fields} {};
ReplicaState::ReplicaState(int32_t replica_id, int64_t log_end_offset, int64_t last_fetch_timestamp, int64_t last_caught_up_timestamp, TaggedFields tagged_fields): replica_id_{replica_id}, log_end_offset_{log_end_offset}, last_fetch_timestamp_{last_fetch_timestamp}, last_caught_up_timestamp_{last_caught_up_timestamp}, tagged_fields_{tagged_fields} {};


uint32_t ReplicaState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(replica_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(log_end_offset_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(last_fetch_timestamp_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(last_caught_up_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ReplicaState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReplicaState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(replica_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(log_end_offset_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(last_fetch_timestamp_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(last_caught_up_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ReplicaState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReplicaState::operator==(const ReplicaState& rhs) const {

  return true
  && replica_id_ == rhs.replica_id_
  && log_end_offset_ == rhs.log_end_offset_
  && last_fetch_timestamp_ == rhs.last_fetch_timestamp_
  && last_caught_up_timestamp_ == rhs.last_caught_up_timestamp_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeQuorumResponseResponsePartitionData::DescribeQuorumResponseResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch, int64_t high_watermark, std::vector<ReplicaState> current_voters, std::vector<ReplicaState> observers, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, high_watermark_{high_watermark}, current_voters_{current_voters}, observers_{observers}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(high_watermark_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(current_voters_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(observers_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeQuorumResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(high_watermark_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(current_voters_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(observers_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeQuorumResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumResponseResponsePartitionData::operator==(const DescribeQuorumResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && high_watermark_ == rhs.high_watermark_
  && current_voters_ == rhs.current_voters_
  && observers_ == rhs.observers_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeQuorumResponseResponseTopicData::DescribeQuorumResponseResponseTopicData(std::string topic_name, std::vector<DescribeQuorumResponseResponsePartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeQuorumResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeQuorumResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumResponseResponseTopicData::operator==(const DescribeQuorumResponseResponseTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeQuorumResponse::DescribeQuorumResponse(int16_t error_code, std::vector<DescribeQuorumResponseResponseTopicData> topics, TaggedFields tagged_fields): error_code_{error_code}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeQuorumResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeQuorumResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumResponse::operator==(const DescribeQuorumResponse& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponsePartitionData::ResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, isr_{isr}, leader_recovery_state_{0}, partition_epoch_{partition_epoch}, tagged_fields_{tagged_fields} {};
ResponsePartitionData::ResponsePartitionData(int32_t partition_index, int16_t error_code, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> isr, int8_t leader_recovery_state, int32_t partition_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, isr_{isr}, leader_recovery_state_{leader_recovery_state}, partition_epoch_{partition_epoch}, tagged_fields_{tagged_fields} {};


uint32_t ResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(isr_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(leader_recovery_state_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partition_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(isr_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(leader_recovery_state_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partition_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponsePartitionData::operator==(const ResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && isr_ == rhs.isr_
  && leader_recovery_state_ == rhs.leader_recovery_state_
  && partition_epoch_ == rhs.partition_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseTopicData::ResponseTopicData(std::string topic_name, std::vector<ResponsePartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{tagged_fields} {};
ResponseTopicData::ResponseTopicData(Uuid topic_id, std::vector<ResponsePartitionData> partitions, TaggedFields tagged_fields): topic_name_{""}, topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseTopicData::operator==(const ResponseTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterPartitionResponse::AlterPartitionResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ResponseTopicData> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t AlterPartitionResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterPartitionResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterPartitionResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterPartitionResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterPartitionResponse::operator==(const AlterPartitionResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdatableFeatureResult::UpdatableFeatureResult(std::string feature, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): feature_{feature}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t UpdatableFeatureResult::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(feature_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdatableFeatureResult::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdatableFeatureResult::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(feature_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdatableFeatureResult::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdatableFeatureResult::operator==(const UpdatableFeatureResult& rhs) const {

  return true
  && feature_ == rhs.feature_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateFeaturesResponse::UpdateFeaturesResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::vector<UpdatableFeatureResult> results, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, results_{results}, tagged_fields_{tagged_fields} {};


uint32_t UpdateFeaturesResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(results_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateFeaturesResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateFeaturesResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(results_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateFeaturesResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateFeaturesResponse::operator==(const UpdateFeaturesResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && results_ == rhs.results_
  && tagged_fields_ == rhs.tagged_fields_;
};


EnvelopeResponse::EnvelopeResponse(absl::optional<Bytes> response_data, int16_t error_code, TaggedFields tagged_fields): response_data_{response_data}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t EnvelopeResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(response_data_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t EnvelopeResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EnvelopeResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(response_data_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t EnvelopeResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EnvelopeResponse::operator==(const EnvelopeResponse& rhs) const {

  return true
  && response_data_ == rhs.response_data_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseSnapshotId::ResponseSnapshotId(int64_t end_offset, int32_t epoch, TaggedFields tagged_fields): end_offset_{end_offset}, epoch_{epoch}, tagged_fields_{tagged_fields} {};


uint32_t ResponseSnapshotId::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(end_offset_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseSnapshotId::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseSnapshotId::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(end_offset_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseSnapshotId::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseSnapshotId::operator==(const ResponseSnapshotId& rhs) const {

  return true
  && end_offset_ == rhs.end_offset_
  && epoch_ == rhs.epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponsePartitionSnapshot::ResponsePartitionSnapshot(int32_t index, int16_t error_code, ResponseSnapshotId snapshot_id, int64_t size, int64_t position, Bytes unaligned_records, TaggedFields tagged_fields): index_{index}, error_code_{error_code}, snapshot_id_{snapshot_id}, size_{size}, position_{position}, unaligned_records_{unaligned_records}, tagged_fields_{tagged_fields} {};


uint32_t ResponsePartitionSnapshot::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(snapshot_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(size_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(position_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(unaligned_records_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponsePartitionSnapshot::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponsePartitionSnapshot::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(snapshot_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(size_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(position_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(unaligned_records_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponsePartitionSnapshot::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponsePartitionSnapshot::operator==(const ResponsePartitionSnapshot& rhs) const {

  return true
  && index_ == rhs.index_
  && error_code_ == rhs.error_code_
  && snapshot_id_ == rhs.snapshot_id_
  && size_ == rhs.size_
  && position_ == rhs.position_
  && unaligned_records_ == rhs.unaligned_records_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseTopicSnapshot::ResponseTopicSnapshot(std::string name, std::vector<ResponsePartitionSnapshot> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ResponseTopicSnapshot::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseTopicSnapshot::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseTopicSnapshot::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseTopicSnapshot::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseTopicSnapshot::operator==(const ResponseTopicSnapshot& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchSnapshotResponse::FetchSnapshotResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ResponseTopicSnapshot> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t FetchSnapshotResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchSnapshotResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchSnapshotResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchSnapshotResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchSnapshotResponse::operator==(const FetchSnapshotResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClusterBroker::DescribeClusterBroker(int32_t broker_id, std::string host, int32_t port, absl::optional<std::string> rack, TaggedFields tagged_fields): broker_id_{broker_id}, host_{host}, port_{port}, rack_{rack}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClusterBroker::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(rack_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClusterBroker::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClusterBroker::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(rack_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClusterBroker::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClusterBroker::operator==(const DescribeClusterBroker& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && rack_ == rhs.rack_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClusterResponse::DescribeClusterResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, std::string cluster_id, int32_t controller_id, std::vector<DescribeClusterBroker> brokers, int32_t cluster_authorized_operations, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, endpoint_type_{1}, cluster_id_{cluster_id}, controller_id_{controller_id}, brokers_{brokers}, cluster_authorized_operations_{cluster_authorized_operations}, tagged_fields_{tagged_fields} {};
DescribeClusterResponse::DescribeClusterResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, int8_t endpoint_type, std::string cluster_id, int32_t controller_id, std::vector<DescribeClusterBroker> brokers, int32_t cluster_authorized_operations, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, endpoint_type_{endpoint_type}, cluster_id_{cluster_id}, controller_id_{controller_id}, brokers_{brokers}, cluster_authorized_operations_{cluster_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClusterResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(endpoint_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(cluster_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(brokers_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(cluster_authorized_operations_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClusterResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClusterResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(endpoint_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(cluster_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(brokers_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(cluster_authorized_operations_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClusterResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClusterResponse::operator==(const DescribeClusterResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && endpoint_type_ == rhs.endpoint_type_
  && cluster_id_ == rhs.cluster_id_
  && controller_id_ == rhs.controller_id_
  && brokers_ == rhs.brokers_
  && cluster_authorized_operations_ == rhs.cluster_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


ProducerState::ProducerState(int64_t producer_id, int32_t producer_epoch, int32_t last_sequence, int64_t last_timestamp, int32_t coordinator_epoch, int64_t current_txn_start_offset, TaggedFields tagged_fields): producer_id_{producer_id}, producer_epoch_{producer_epoch}, last_sequence_{last_sequence}, last_timestamp_{last_timestamp}, coordinator_epoch_{coordinator_epoch}, current_txn_start_offset_{current_txn_start_offset}, tagged_fields_{tagged_fields} {};


uint32_t ProducerState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(last_sequence_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(last_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(coordinator_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(current_txn_start_offset_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ProducerState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ProducerState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(last_sequence_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(last_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(coordinator_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(current_txn_start_offset_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ProducerState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ProducerState::operator==(const ProducerState& rhs) const {

  return true
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && last_sequence_ == rhs.last_sequence_
  && last_timestamp_ == rhs.last_timestamp_
  && coordinator_epoch_ == rhs.coordinator_epoch_
  && current_txn_start_offset_ == rhs.current_txn_start_offset_
  && tagged_fields_ == rhs.tagged_fields_;
};


PartitionResponse::PartitionResponse(int32_t partition_index, int16_t error_code, absl::optional<std::string> error_message, std::vector<ProducerState> active_producers, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, error_message_{error_message}, active_producers_{active_producers}, tagged_fields_{tagged_fields} {};


uint32_t PartitionResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(active_producers_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t PartitionResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t PartitionResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(active_producers_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t PartitionResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool PartitionResponse::operator==(const PartitionResponse& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && active_producers_ == rhs.active_producers_
  && tagged_fields_ == rhs.tagged_fields_;
};


TopicResponse::TopicResponse(std::string name, std::vector<PartitionResponse> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t TopicResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TopicResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TopicResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TopicResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TopicResponse::operator==(const TopicResponse& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeProducersResponse::DescribeProducersResponse(int32_t throttle_time_ms, std::vector<TopicResponse> topics, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DescribeProducersResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeProducersResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeProducersResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeProducersResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeProducersResponse::operator==(const DescribeProducersResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


BrokerRegistrationResponse::BrokerRegistrationResponse(int32_t throttle_time_ms, int16_t error_code, int64_t broker_epoch, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, broker_epoch_{broker_epoch}, tagged_fields_{tagged_fields} {};


uint32_t BrokerRegistrationResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BrokerRegistrationResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BrokerRegistrationResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BrokerRegistrationResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BrokerRegistrationResponse::operator==(const BrokerRegistrationResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && broker_epoch_ == rhs.broker_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


BrokerHeartbeatResponse::BrokerHeartbeatResponse(int32_t throttle_time_ms, int16_t error_code, bool is_caught_up, bool is_fenced, bool should_shut_down, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, is_caught_up_{is_caught_up}, is_fenced_{is_fenced}, should_shut_down_{should_shut_down}, tagged_fields_{tagged_fields} {};


uint32_t BrokerHeartbeatResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(is_caught_up_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(is_fenced_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(should_shut_down_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BrokerHeartbeatResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BrokerHeartbeatResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(is_caught_up_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(is_fenced_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(should_shut_down_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BrokerHeartbeatResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BrokerHeartbeatResponse::operator==(const BrokerHeartbeatResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && is_caught_up_ == rhs.is_caught_up_
  && is_fenced_ == rhs.is_fenced_
  && should_shut_down_ == rhs.should_shut_down_
  && tagged_fields_ == rhs.tagged_fields_;
};


UnregisterBrokerResponse::UnregisterBrokerResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t UnregisterBrokerResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UnregisterBrokerResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UnregisterBrokerResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UnregisterBrokerResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UnregisterBrokerResponse::operator==(const UnregisterBrokerResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTransactionsResponseResponseTopicData::DescribeTransactionsResponseResponseTopicData(std::string topic, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_{topic}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTransactionsResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTransactionsResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTransactionsResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTransactionsResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTransactionsResponseResponseTopicData::operator==(const DescribeTransactionsResponseResponseTopicData& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


TransactionState::TransactionState(int16_t error_code, std::string transactional_id, std::string transaction_state, int32_t transaction_timeout_ms, int64_t transaction_start_time_ms, int64_t producer_id, int16_t producer_epoch, std::vector<DescribeTransactionsResponseResponseTopicData> topics, TaggedFields tagged_fields): error_code_{error_code}, transactional_id_{transactional_id}, transaction_state_{transaction_state}, transaction_timeout_ms_{transaction_timeout_ms}, transaction_start_time_ms_{transaction_start_time_ms}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t TransactionState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(transaction_state_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(transaction_timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(transaction_start_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TransactionState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TransactionState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(transaction_state_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(transaction_timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(transaction_start_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TransactionState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TransactionState::operator==(const TransactionState& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && transactional_id_ == rhs.transactional_id_
  && transaction_state_ == rhs.transaction_state_
  && transaction_timeout_ms_ == rhs.transaction_timeout_ms_
  && transaction_start_time_ms_ == rhs.transaction_start_time_ms_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTransactionsResponse::DescribeTransactionsResponse(int32_t throttle_time_ms, std::vector<TransactionState> transaction_states, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, transaction_states_{transaction_states}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTransactionsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(transaction_states_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTransactionsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTransactionsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(transaction_states_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTransactionsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTransactionsResponse::operator==(const DescribeTransactionsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && transaction_states_ == rhs.transaction_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListTransactionsResponseTransactionState::ListTransactionsResponseTransactionState(std::string transactional_id, int64_t producer_id, std::string transaction_state, TaggedFields tagged_fields): transactional_id_{transactional_id}, producer_id_{producer_id}, transaction_state_{transaction_state}, tagged_fields_{tagged_fields} {};


uint32_t ListTransactionsResponseTransactionState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(transaction_state_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListTransactionsResponseTransactionState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListTransactionsResponseTransactionState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(transaction_state_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListTransactionsResponseTransactionState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListTransactionsResponseTransactionState::operator==(const ListTransactionsResponseTransactionState& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && producer_id_ == rhs.producer_id_
  && transaction_state_ == rhs.transaction_state_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListTransactionsResponse::ListTransactionsResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<std::string> unknown_state_filters, std::vector<ListTransactionsResponseTransactionState> transaction_states, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, unknown_state_filters_{unknown_state_filters}, transaction_states_{transaction_states}, tagged_fields_{tagged_fields} {};


uint32_t ListTransactionsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(unknown_state_filters_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(transaction_states_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListTransactionsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListTransactionsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(unknown_state_filters_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(transaction_states_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListTransactionsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListTransactionsResponse::operator==(const ListTransactionsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && unknown_state_filters_ == rhs.unknown_state_filters_
  && transaction_states_ == rhs.transaction_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


AllocateProducerIdsResponse::AllocateProducerIdsResponse(int32_t throttle_time_ms, int16_t error_code, int64_t producer_id_start, int32_t producer_id_len, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, producer_id_start_{producer_id_start}, producer_id_len_{producer_id_len}, tagged_fields_{tagged_fields} {};


uint32_t AllocateProducerIdsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_id_start_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(producer_id_len_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AllocateProducerIdsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AllocateProducerIdsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_id_start_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(producer_id_len_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AllocateProducerIdsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AllocateProducerIdsResponse::operator==(const AllocateProducerIdsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && producer_id_start_ == rhs.producer_id_start_
  && producer_id_len_ == rhs.producer_id_len_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupHeartbeatResponseResponseTopicPartitions::ConsumerGroupHeartbeatResponseResponseTopicPartitions(Uuid topic_id, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupHeartbeatResponseResponseTopicPartitions::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponseResponseTopicPartitions::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupHeartbeatResponseResponseTopicPartitions::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponseResponseTopicPartitions::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupHeartbeatResponseResponseTopicPartitions::operator==(const ConsumerGroupHeartbeatResponseResponseTopicPartitions& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupHeartbeatResponseAssignment::ConsumerGroupHeartbeatResponseAssignment(std::vector<ConsumerGroupHeartbeatResponseResponseTopicPartitions> topic_partitions, TaggedFields tagged_fields): topic_partitions_{topic_partitions}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupHeartbeatResponseAssignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponseAssignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupHeartbeatResponseAssignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponseAssignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupHeartbeatResponseAssignment::operator==(const ConsumerGroupHeartbeatResponseAssignment& rhs) const {

  return true
  && topic_partitions_ == rhs.topic_partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupHeartbeatResponse::ConsumerGroupHeartbeatResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, absl::optional<std::string> member_id, int32_t member_epoch, int32_t heartbeat_interval_ms, absl::optional<ConsumerGroupHeartbeatResponseAssignment> assignment, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, member_id_{member_id}, member_epoch_{member_epoch}, heartbeat_interval_ms_{heartbeat_interval_ms}, assignment_{assignment}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupHeartbeatResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(member_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(heartbeat_interval_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(assignment_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupHeartbeatResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(member_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(heartbeat_interval_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(assignment_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupHeartbeatResponse::operator==(const ConsumerGroupHeartbeatResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && member_id_ == rhs.member_id_
  && member_epoch_ == rhs.member_epoch_
  && heartbeat_interval_ms_ == rhs.heartbeat_interval_ms_
  && assignment_ == rhs.assignment_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseTopicPartitions::ResponseTopicPartitions(Uuid topic_id, std::string topic_name, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_id_{topic_id}, topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ResponseTopicPartitions::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseTopicPartitions::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseTopicPartitions::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseTopicPartitions::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseTopicPartitions::operator==(const ResponseTopicPartitions& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


Assignment::Assignment(std::vector<ResponseTopicPartitions> topic_partitions, TaggedFields tagged_fields): topic_partitions_{topic_partitions}, tagged_fields_{tagged_fields} {};


uint32_t Assignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t Assignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t Assignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t Assignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool Assignment::operator==(const Assignment& rhs) const {

  return true
  && topic_partitions_ == rhs.topic_partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


Member::Member(std::string member_id, absl::optional<std::string> instance_id, absl::optional<std::string> rack_id, int32_t member_epoch, std::string client_id, std::string client_host, std::vector<std::string> subscribed_topic_names, absl::optional<std::string> subscribed_topic_regex, Assignment assignment, Assignment target_assignment, TaggedFields tagged_fields): member_id_{member_id}, instance_id_{instance_id}, rack_id_{rack_id}, member_epoch_{member_epoch}, client_id_{client_id}, client_host_{client_host}, subscribed_topic_names_{subscribed_topic_names}, subscribed_topic_regex_{subscribed_topic_regex}, assignment_{assignment}, target_assignment_{target_assignment}, tagged_fields_{tagged_fields} {};


uint32_t Member::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(instance_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(rack_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(member_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(client_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(client_host_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(subscribed_topic_names_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(subscribed_topic_regex_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(assignment_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(target_assignment_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t Member::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t Member::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(instance_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(rack_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(member_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(client_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(client_host_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(subscribed_topic_names_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(subscribed_topic_regex_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(assignment_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(target_assignment_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t Member::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool Member::operator==(const Member& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && instance_id_ == rhs.instance_id_
  && rack_id_ == rhs.rack_id_
  && member_epoch_ == rhs.member_epoch_
  && client_id_ == rhs.client_id_
  && client_host_ == rhs.client_host_
  && subscribed_topic_names_ == rhs.subscribed_topic_names_
  && subscribed_topic_regex_ == rhs.subscribed_topic_regex_
  && assignment_ == rhs.assignment_
  && target_assignment_ == rhs.target_assignment_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribedGroup::DescribedGroup(int16_t error_code, absl::optional<std::string> error_message, std::string group_id, std::string group_state, int32_t group_epoch, int32_t assignment_epoch, std::string assignor_name, std::vector<Member> members, int32_t authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, error_message_{error_message}, group_id_{group_id}, group_state_{group_state}, group_epoch_{group_epoch}, assignment_epoch_{assignment_epoch}, assignor_name_{assignor_name}, members_{members}, authorized_operations_{authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t DescribedGroup::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(group_state_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(group_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(assignment_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(assignor_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(members_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(authorized_operations_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribedGroup::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribedGroup::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(group_state_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(group_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(assignment_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(assignor_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(members_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(authorized_operations_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribedGroup::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribedGroup::operator==(const DescribedGroup& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && group_id_ == rhs.group_id_
  && group_state_ == rhs.group_state_
  && group_epoch_ == rhs.group_epoch_
  && assignment_epoch_ == rhs.assignment_epoch_
  && assignor_name_ == rhs.assignor_name_
  && members_ == rhs.members_
  && authorized_operations_ == rhs.authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupDescribeResponse::ConsumerGroupDescribeResponse(int32_t throttle_time_ms, std::vector<DescribedGroup> groups, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, groups_{groups}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupDescribeResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupDescribeResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupDescribeResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupDescribeResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupDescribeResponse::operator==(const ConsumerGroupDescribeResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && groups_ == rhs.groups_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControllerRegistrationResponse::ControllerRegistrationResponse(int32_t throttle_time_ms, int16_t error_code, absl::optional<std::string> error_message, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, error_message_{error_message}, tagged_fields_{tagged_fields} {};


uint32_t ControllerRegistrationResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(error_message_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControllerRegistrationResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControllerRegistrationResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(error_message_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControllerRegistrationResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControllerRegistrationResponse::operator==(const ControllerRegistrationResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && error_message_ == rhs.error_message_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsResponseResponsePartitionData::AssignReplicasToDirsResponseResponsePartitionData(int32_t partition_index, int16_t error_code, TaggedFields tagged_fields): partition_index_{partition_index}, error_code_{error_code}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsResponseResponsePartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponseResponsePartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsResponseResponsePartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponseResponsePartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsResponseResponsePartitionData::operator==(const AssignReplicasToDirsResponseResponsePartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && error_code_ == rhs.error_code_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsResponseResponseTopicData::AssignReplicasToDirsResponseResponseTopicData(Uuid topic_id, std::vector<AssignReplicasToDirsResponseResponsePartitionData> partitions, TaggedFields tagged_fields): topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsResponseResponseTopicData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponseResponseTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsResponseResponseTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponseResponseTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsResponseResponseTopicData::operator==(const AssignReplicasToDirsResponseResponseTopicData& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseDirectoryData::ResponseDirectoryData(Uuid id, std::vector<AssignReplicasToDirsResponseResponseTopicData> topics, TaggedFields tagged_fields): id_{id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t ResponseDirectoryData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseDirectoryData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseDirectoryData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseDirectoryData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseDirectoryData::operator==(const ResponseDirectoryData& rhs) const {

  return true
  && id_ == rhs.id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsResponse::AssignReplicasToDirsResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ResponseDirectoryData> directories, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, directories_{directories}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(directories_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(directories_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsResponse::operator==(const AssignReplicasToDirsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && directories_ == rhs.directories_
  && tagged_fields_ == rhs.tagged_fields_;
};


ClientMetricsResource::ClientMetricsResource(std::string name, TaggedFields tagged_fields): name_{name}, tagged_fields_{tagged_fields} {};


uint32_t ClientMetricsResource::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ClientMetricsResource::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ClientMetricsResource::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ClientMetricsResource::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ClientMetricsResource::operator==(const ClientMetricsResource& rhs) const {

  return true
  && name_ == rhs.name_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListClientMetricsResourcesResponse::ListClientMetricsResourcesResponse(int32_t throttle_time_ms, int16_t error_code, std::vector<ClientMetricsResource> client_metrics_resources, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, error_code_{error_code}, client_metrics_resources_{client_metrics_resources}, tagged_fields_{tagged_fields} {};


uint32_t ListClientMetricsResourcesResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(client_metrics_resources_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListClientMetricsResourcesResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListClientMetricsResourcesResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(client_metrics_resources_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListClientMetricsResourcesResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListClientMetricsResourcesResponse::operator==(const ListClientMetricsResourcesResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && error_code_ == rhs.error_code_
  && client_metrics_resources_ == rhs.client_metrics_resources_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTopicPartitionsResponsePartition::DescribeTopicPartitionsResponsePartition(int16_t error_code, int32_t partition_index, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> replica_nodes, std::vector<int32_t> isr_nodes, absl::optional<std::vector<int32_t>> eligible_leader_replicas, absl::optional<std::vector<int32_t>> last_known_elr, std::vector<int32_t> offline_replicas, TaggedFields tagged_fields): error_code_{error_code}, partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, replica_nodes_{replica_nodes}, isr_nodes_{isr_nodes}, eligible_leader_replicas_{eligible_leader_replicas}, last_known_elr_{last_known_elr}, offline_replicas_{offline_replicas}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTopicPartitionsResponsePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(replica_nodes_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(isr_nodes_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(eligible_leader_replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(last_known_elr_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(offline_replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponsePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTopicPartitionsResponsePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(replica_nodes_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(isr_nodes_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(eligible_leader_replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(last_known_elr_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(offline_replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponsePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTopicPartitionsResponsePartition::operator==(const DescribeTopicPartitionsResponsePartition& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && partition_index_ == rhs.partition_index_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && replica_nodes_ == rhs.replica_nodes_
  && isr_nodes_ == rhs.isr_nodes_
  && eligible_leader_replicas_ == rhs.eligible_leader_replicas_
  && last_known_elr_ == rhs.last_known_elr_
  && offline_replicas_ == rhs.offline_replicas_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTopicPartitionsResponseTopic::DescribeTopicPartitionsResponseTopic(int16_t error_code, absl::optional<std::string> name, Uuid topic_id, bool is_internal, std::vector<DescribeTopicPartitionsResponsePartition> partitions, int32_t topic_authorized_operations, TaggedFields tagged_fields): error_code_{error_code}, name_{name}, topic_id_{topic_id}, is_internal_{is_internal}, partitions_{partitions}, topic_authorized_operations_{topic_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTopicPartitionsResponseTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(error_code_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(is_internal_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_authorized_operations_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponseTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTopicPartitionsResponseTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(error_code_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(is_internal_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_authorized_operations_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponseTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTopicPartitionsResponseTopic::operator==(const DescribeTopicPartitionsResponseTopic& rhs) const {

  return true
  && error_code_ == rhs.error_code_
  && name_ == rhs.name_
  && topic_id_ == rhs.topic_id_
  && is_internal_ == rhs.is_internal_
  && partitions_ == rhs.partitions_
  && topic_authorized_operations_ == rhs.topic_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


ResponseCursor::ResponseCursor(std::string topic_name, int32_t partition_index, TaggedFields tagged_fields): topic_name_{topic_name}, partition_index_{partition_index}, tagged_fields_{tagged_fields} {};


uint32_t ResponseCursor::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ResponseCursor::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ResponseCursor::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ResponseCursor::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ResponseCursor::operator==(const ResponseCursor& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTopicPartitionsResponse::DescribeTopicPartitionsResponse(int32_t throttle_time_ms, std::vector<DescribeTopicPartitionsResponseTopic> topics, absl::optional<ResponseCursor> next_cursor, TaggedFields tagged_fields): throttle_time_ms_{throttle_time_ms}, topics_{topics}, next_cursor_{next_cursor}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTopicPartitionsResponse::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(throttle_time_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(next_cursor_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponse::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTopicPartitionsResponse::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(throttle_time_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(next_cursor_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsResponse::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTopicPartitionsResponse::operator==(const DescribeTopicPartitionsResponse& rhs) const {

  return true
  && throttle_time_ms_ == rhs.throttle_time_ms_
  && topics_ == rhs.topics_
  && next_cursor_ == rhs.next_cursor_
  && tagged_fields_ == rhs.tagged_fields_;
};

}}}}