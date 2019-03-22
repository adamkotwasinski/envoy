
#include "contrib/kafka/filters/network/source/external/requests.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {




PartitionProduceData::PartitionProduceData(int32_t index, absl::optional<Bytes> records): index_{index}, records_{records}, tagged_fields_{TaggedFields({})} {};
PartitionProduceData::PartitionProduceData(int32_t index, absl::optional<Bytes> records, TaggedFields tagged_fields): index_{index}, records_{records}, tagged_fields_{tagged_fields} {};


uint32_t PartitionProduceData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(index_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(records_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(records_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t PartitionProduceData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t PartitionProduceData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(index_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(records_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(records_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t PartitionProduceData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool PartitionProduceData::operator==(const PartitionProduceData& rhs) const {

  return true
  && index_ == rhs.index_
  && records_ == rhs.records_
  && tagged_fields_ == rhs.tagged_fields_;
};


TopicProduceData::TopicProduceData(std::string name, std::vector<PartitionProduceData> partition_data): name_{name}, partition_data_{partition_data}, tagged_fields_{TaggedFields({})} {};
TopicProduceData::TopicProduceData(std::string name, std::vector<PartitionProduceData> partition_data, TaggedFields tagged_fields): name_{name}, partition_data_{partition_data}, tagged_fields_{tagged_fields} {};


uint32_t TopicProduceData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partition_data_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(partition_data_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TopicProduceData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TopicProduceData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partition_data_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(partition_data_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TopicProduceData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TopicProduceData::operator==(const TopicProduceData& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_data_ == rhs.partition_data_
  && tagged_fields_ == rhs.tagged_fields_;
};


ProduceRequest::ProduceRequest(int16_t acks, int32_t timeout_ms, std::vector<TopicProduceData> topic_data): transactional_id_{absl::nullopt}, acks_{acks}, timeout_ms_{timeout_ms}, topic_data_{topic_data}, tagged_fields_{TaggedFields({})} {};
ProduceRequest::ProduceRequest(absl::optional<std::string> transactional_id, int16_t acks, int32_t timeout_ms, std::vector<TopicProduceData> topic_data): transactional_id_{transactional_id}, acks_{acks}, timeout_ms_{timeout_ms}, topic_data_{topic_data}, tagged_fields_{TaggedFields({})} {};
ProduceRequest::ProduceRequest(absl::optional<std::string> transactional_id, int16_t acks, int32_t timeout_ms, std::vector<TopicProduceData> topic_data, TaggedFields tagged_fields): transactional_id_{transactional_id}, acks_{acks}, timeout_ms_{timeout_ms}, topic_data_{topic_data}, tagged_fields_{tagged_fields} {};


uint32_t ProduceRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 9) {
    written += encoder.computeSize(transactional_id_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(acks_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(topic_data_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(topic_data_);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ProduceRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ProduceRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 9) {
    written += encoder.encode(transactional_id_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(acks_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(topic_data_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(topic_data_, dst);
  }
  
  if (api_version >= 9 && api_version < 12) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ProduceRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ProduceRequest::operator==(const ProduceRequest& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && acks_ == rhs.acks_
  && timeout_ms_ == rhs.timeout_ms_
  && topic_data_ == rhs.topic_data_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchPartition::FetchPartition(int32_t partition, int64_t fetch_offset, int32_t partition_max_bytes): partition_{partition}, current_leader_epoch_{-1}, fetch_offset_{fetch_offset}, last_fetched_epoch_{-1}, log_start_offset_{-1}, partition_max_bytes_{partition_max_bytes}, tagged_fields_{TaggedFields({})} {};
FetchPartition::FetchPartition(int32_t partition, int64_t fetch_offset, int64_t log_start_offset, int32_t partition_max_bytes): partition_{partition}, current_leader_epoch_{-1}, fetch_offset_{fetch_offset}, last_fetched_epoch_{-1}, log_start_offset_{log_start_offset}, partition_max_bytes_{partition_max_bytes}, tagged_fields_{TaggedFields({})} {};
FetchPartition::FetchPartition(int32_t partition, int32_t current_leader_epoch, int64_t fetch_offset, int64_t log_start_offset, int32_t partition_max_bytes): partition_{partition}, current_leader_epoch_{current_leader_epoch}, fetch_offset_{fetch_offset}, last_fetched_epoch_{-1}, log_start_offset_{log_start_offset}, partition_max_bytes_{partition_max_bytes}, tagged_fields_{TaggedFields({})} {};
FetchPartition::FetchPartition(int32_t partition, int32_t current_leader_epoch, int64_t fetch_offset, int32_t last_fetched_epoch, int64_t log_start_offset, int32_t partition_max_bytes, TaggedFields tagged_fields): partition_{partition}, current_leader_epoch_{current_leader_epoch}, fetch_offset_{fetch_offset}, last_fetched_epoch_{last_fetched_epoch}, log_start_offset_{log_start_offset}, partition_max_bytes_{partition_max_bytes}, tagged_fields_{tagged_fields} {};


uint32_t FetchPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(partition_);
  }
  
  if (api_version >= 9 && api_version < 17) {
    written += encoder.computeSize(current_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(fetch_offset_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeSize(last_fetched_epoch_);
  }
  
  if (api_version >= 5 && api_version < 17) {
    written += encoder.computeSize(log_start_offset_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(partition_max_bytes_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(partition_, dst);
  }
  
  if (api_version >= 9 && api_version < 17) {
    written += encoder.encode(current_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(fetch_offset_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encode(last_fetched_epoch_, dst);
  }
  
  if (api_version >= 5 && api_version < 17) {
    written += encoder.encode(log_start_offset_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(partition_max_bytes_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchPartition::operator==(const FetchPartition& rhs) const {

  return true
  && partition_ == rhs.partition_
  && current_leader_epoch_ == rhs.current_leader_epoch_
  && fetch_offset_ == rhs.fetch_offset_
  && last_fetched_epoch_ == rhs.last_fetched_epoch_
  && log_start_offset_ == rhs.log_start_offset_
  && partition_max_bytes_ == rhs.partition_max_bytes_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchTopic::FetchTopic(std::string topic, std::vector<FetchPartition> partitions): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
FetchTopic::FetchTopic(std::string topic, std::vector<FetchPartition> partitions, TaggedFields tagged_fields): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{tagged_fields} {};
FetchTopic::FetchTopic(Uuid topic_id, std::vector<FetchPartition> partitions, TaggedFields tagged_fields): topic_{""}, topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t FetchTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t FetchTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t FetchTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchTopic::operator==(const FetchTopic& rhs) const {

  return true
  && topic_ == rhs.topic_
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ForgottenTopic::ForgottenTopic(std::string topic, std::vector<int32_t> partitions): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
ForgottenTopic::ForgottenTopic(std::string topic, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_{topic}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{tagged_fields} {};
ForgottenTopic::ForgottenTopic(Uuid topic_id, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_{""}, topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ForgottenTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 7 && api_version < 12) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 12 && api_version < 13) {
    written += encoder.computeCompactSize(topic_);
  }
  
  if (api_version >= 13 && api_version < 17) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 7 && api_version < 12) {
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

uint32_t ForgottenTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ForgottenTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 7 && api_version < 12) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 12 && api_version < 13) {
    written += encoder.encodeCompact(topic_, dst);
  }
  
  if (api_version >= 13 && api_version < 17) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 12) {
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

uint32_t ForgottenTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ForgottenTopic::operator==(const ForgottenTopic& rhs) const {

  return true
  && topic_ == rhs.topic_
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, std::vector<FetchTopic> topics): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{0x7fffffff}, isolation_level_{0}, session_id_{0}, session_epoch_{-1}, topics_{topics}, forgotten_topics_data_{std::vector<ForgottenTopic>{}}, rack_id_{}, tagged_fields_{TaggedFields({})} {};
FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, std::vector<FetchTopic> topics): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{0}, session_id_{0}, session_epoch_{-1}, topics_{topics}, forgotten_topics_data_{std::vector<ForgottenTopic>{}}, rack_id_{}, tagged_fields_{TaggedFields({})} {};
FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, int8_t isolation_level, std::vector<FetchTopic> topics): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{isolation_level}, session_id_{0}, session_epoch_{-1}, topics_{topics}, forgotten_topics_data_{std::vector<ForgottenTopic>{}}, rack_id_{}, tagged_fields_{TaggedFields({})} {};
FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, int8_t isolation_level, int32_t session_id, int32_t session_epoch, std::vector<FetchTopic> topics, std::vector<ForgottenTopic> forgotten_topics_data): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{isolation_level}, session_id_{session_id}, session_epoch_{session_epoch}, topics_{topics}, forgotten_topics_data_{forgotten_topics_data}, rack_id_{}, tagged_fields_{TaggedFields({})} {};
FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, int8_t isolation_level, int32_t session_id, int32_t session_epoch, std::vector<FetchTopic> topics, std::vector<ForgottenTopic> forgotten_topics_data, std::string rack_id): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{isolation_level}, session_id_{session_id}, session_epoch_{session_epoch}, topics_{topics}, forgotten_topics_data_{forgotten_topics_data}, rack_id_{rack_id}, tagged_fields_{TaggedFields({})} {};
FetchRequest::FetchRequest(int32_t replica_id, int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, int8_t isolation_level, int32_t session_id, int32_t session_epoch, std::vector<FetchTopic> topics, std::vector<ForgottenTopic> forgotten_topics_data, std::string rack_id, TaggedFields tagged_fields): replica_id_{replica_id}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{isolation_level}, session_id_{session_id}, session_epoch_{session_epoch}, topics_{topics}, forgotten_topics_data_{forgotten_topics_data}, rack_id_{rack_id}, tagged_fields_{tagged_fields} {};
FetchRequest::FetchRequest(int32_t max_wait_ms, int32_t min_bytes, int32_t max_bytes, int8_t isolation_level, int32_t session_id, int32_t session_epoch, std::vector<FetchTopic> topics, std::vector<ForgottenTopic> forgotten_topics_data, std::string rack_id, TaggedFields tagged_fields): replica_id_{-1}, max_wait_ms_{max_wait_ms}, min_bytes_{min_bytes}, max_bytes_{max_bytes}, isolation_level_{isolation_level}, session_id_{session_id}, session_epoch_{session_epoch}, topics_{topics}, forgotten_topics_data_{forgotten_topics_data}, rack_id_{rack_id}, tagged_fields_{tagged_fields} {};


uint32_t FetchRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 15) {
    written += encoder.computeSize(replica_id_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(max_wait_ms_);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.computeSize(min_bytes_);
  }
  
  if (api_version >= 3 && api_version < 17) {
    written += encoder.computeSize(max_bytes_);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.computeSize(isolation_level_);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.computeSize(session_id_);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.computeSize(session_epoch_);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 7 && api_version < 12) {
    written += encoder.computeSize(forgotten_topics_data_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(forgotten_topics_data_);
  }
  
  if (api_version >= 11 && api_version < 12) {
    written += encoder.computeSize(rack_id_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(rack_id_);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 15) {
    written += encoder.encode(replica_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(max_wait_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 17) {
    written += encoder.encode(min_bytes_, dst);
  }
  
  if (api_version >= 3 && api_version < 17) {
    written += encoder.encode(max_bytes_, dst);
  }
  
  if (api_version >= 4 && api_version < 17) {
    written += encoder.encode(isolation_level_, dst);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.encode(session_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 17) {
    written += encoder.encode(session_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 12) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 7 && api_version < 12) {
    written += encoder.encode(forgotten_topics_data_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(forgotten_topics_data_, dst);
  }
  
  if (api_version >= 11 && api_version < 12) {
    written += encoder.encode(rack_id_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(rack_id_, dst);
  }
  
  if (api_version >= 12 && api_version < 17) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchRequest::operator==(const FetchRequest& rhs) const {

  return true
  && replica_id_ == rhs.replica_id_
  && max_wait_ms_ == rhs.max_wait_ms_
  && min_bytes_ == rhs.min_bytes_
  && max_bytes_ == rhs.max_bytes_
  && isolation_level_ == rhs.isolation_level_
  && session_id_ == rhs.session_id_
  && session_epoch_ == rhs.session_epoch_
  && topics_ == rhs.topics_
  && forgotten_topics_data_ == rhs.forgotten_topics_data_
  && rack_id_ == rhs.rack_id_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsPartition::ListOffsetsPartition(int32_t partition_index, int64_t timestamp, int32_t max_num_offsets): partition_index_{partition_index}, current_leader_epoch_{-1}, timestamp_{timestamp}, max_num_offsets_{max_num_offsets}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartition::ListOffsetsPartition(int32_t partition_index, int64_t timestamp): partition_index_{partition_index}, current_leader_epoch_{-1}, timestamp_{timestamp}, max_num_offsets_{1}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartition::ListOffsetsPartition(int32_t partition_index, int32_t current_leader_epoch, int64_t timestamp): partition_index_{partition_index}, current_leader_epoch_{current_leader_epoch}, timestamp_{timestamp}, max_num_offsets_{1}, tagged_fields_{TaggedFields({})} {};
ListOffsetsPartition::ListOffsetsPartition(int32_t partition_index, int32_t current_leader_epoch, int64_t timestamp, TaggedFields tagged_fields): partition_index_{partition_index}, current_leader_epoch_{current_leader_epoch}, timestamp_{timestamp}, max_num_offsets_{1}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 4 && api_version < 9) {
    written += encoder.computeSize(current_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(timestamp_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(max_num_offsets_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListOffsetsPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 4 && api_version < 9) {
    written += encoder.encode(current_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(max_num_offsets_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListOffsetsPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsPartition::operator==(const ListOffsetsPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && current_leader_epoch_ == rhs.current_leader_epoch_
  && timestamp_ == rhs.timestamp_
  && max_num_offsets_ == rhs.max_num_offsets_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsTopic::ListOffsetsTopic(std::string name, std::vector<ListOffsetsPartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
ListOffsetsTopic::ListOffsetsTopic(std::string name, std::vector<ListOffsetsPartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t ListOffsetsTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t ListOffsetsTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsTopic::operator==(const ListOffsetsTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListOffsetsRequest::ListOffsetsRequest(int32_t replica_id, std::vector<ListOffsetsTopic> topics): replica_id_{replica_id}, isolation_level_{0}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
ListOffsetsRequest::ListOffsetsRequest(int32_t replica_id, int8_t isolation_level, std::vector<ListOffsetsTopic> topics): replica_id_{replica_id}, isolation_level_{isolation_level}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
ListOffsetsRequest::ListOffsetsRequest(int32_t replica_id, int8_t isolation_level, std::vector<ListOffsetsTopic> topics, TaggedFields tagged_fields): replica_id_{replica_id}, isolation_level_{isolation_level}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t ListOffsetsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(replica_id_);
  }
  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.computeSize(isolation_level_);
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

uint32_t ListOffsetsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListOffsetsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(replica_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 9) {
    written += encoder.encode(isolation_level_, dst);
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

uint32_t ListOffsetsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListOffsetsRequest::operator==(const ListOffsetsRequest& rhs) const {

  return true
  && replica_id_ == rhs.replica_id_
  && isolation_level_ == rhs.isolation_level_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataRequestTopic::MetadataRequestTopic(std::string name): topic_id_{Uuid{0, 0}}, name_{absl::make_optional(name)}, tagged_fields_{TaggedFields({})} {};
MetadataRequestTopic::MetadataRequestTopic(std::string name, TaggedFields tagged_fields): topic_id_{Uuid{0, 0}}, name_{absl::make_optional(name)}, tagged_fields_{tagged_fields} {};
MetadataRequestTopic::MetadataRequestTopic(Uuid topic_id, absl::optional<std::string> name, TaggedFields tagged_fields): topic_id_{topic_id}, name_{name}, tagged_fields_{tagged_fields} {};


uint32_t MetadataRequestTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 10 && api_version < 13) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataRequestTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataRequestTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 10 && api_version < 13) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataRequestTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataRequestTopic::operator==(const MetadataRequestTopic& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && name_ == rhs.name_
  && tagged_fields_ == rhs.tagged_fields_;
};


MetadataRequest::MetadataRequest(std::vector<MetadataRequestTopic> topics): topics_{absl::make_optional(topics)}, allow_auto_topic_creation_{true}, include_cluster_authorized_operations_{false}, include_topic_authorized_operations_{false}, tagged_fields_{TaggedFields({})} {};
MetadataRequest::MetadataRequest(absl::optional<std::vector<MetadataRequestTopic>> topics): topics_{topics}, allow_auto_topic_creation_{true}, include_cluster_authorized_operations_{false}, include_topic_authorized_operations_{false}, tagged_fields_{TaggedFields({})} {};
MetadataRequest::MetadataRequest(absl::optional<std::vector<MetadataRequestTopic>> topics, bool allow_auto_topic_creation): topics_{topics}, allow_auto_topic_creation_{allow_auto_topic_creation}, include_cluster_authorized_operations_{false}, include_topic_authorized_operations_{false}, tagged_fields_{TaggedFields({})} {};
MetadataRequest::MetadataRequest(absl::optional<std::vector<MetadataRequestTopic>> topics, bool allow_auto_topic_creation, bool include_cluster_authorized_operations, bool include_topic_authorized_operations): topics_{topics}, allow_auto_topic_creation_{allow_auto_topic_creation}, include_cluster_authorized_operations_{include_cluster_authorized_operations}, include_topic_authorized_operations_{include_topic_authorized_operations}, tagged_fields_{TaggedFields({})} {};
MetadataRequest::MetadataRequest(absl::optional<std::vector<MetadataRequestTopic>> topics, bool allow_auto_topic_creation, bool include_cluster_authorized_operations, bool include_topic_authorized_operations, TaggedFields tagged_fields): topics_{topics}, allow_auto_topic_creation_{allow_auto_topic_creation}, include_cluster_authorized_operations_{include_cluster_authorized_operations}, include_topic_authorized_operations_{include_topic_authorized_operations}, tagged_fields_{tagged_fields} {};
MetadataRequest::MetadataRequest(absl::optional<std::vector<MetadataRequestTopic>> topics, bool allow_auto_topic_creation, bool include_topic_authorized_operations, TaggedFields tagged_fields): topics_{topics}, allow_auto_topic_creation_{allow_auto_topic_creation}, include_cluster_authorized_operations_{false}, include_topic_authorized_operations_{include_topic_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t MetadataRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 4 && api_version < 13) {
    written += encoder.computeSize(allow_auto_topic_creation_);
  }
  
  if (api_version >= 8 && api_version < 11) {
    written += encoder.computeSize(include_cluster_authorized_operations_);
  }
  
  if (api_version >= 8 && api_version < 13) {
    written += encoder.computeSize(include_topic_authorized_operations_);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MetadataRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MetadataRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 4 && api_version < 13) {
    written += encoder.encode(allow_auto_topic_creation_, dst);
  }
  
  if (api_version >= 8 && api_version < 11) {
    written += encoder.encode(include_cluster_authorized_operations_, dst);
  }
  
  if (api_version >= 8 && api_version < 13) {
    written += encoder.encode(include_topic_authorized_operations_, dst);
  }
  
  if (api_version >= 9 && api_version < 13) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MetadataRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MetadataRequest::operator==(const MetadataRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && allow_auto_topic_creation_ == rhs.allow_auto_topic_creation_
  && include_cluster_authorized_operations_ == rhs.include_cluster_authorized_operations_
  && include_topic_authorized_operations_ == rhs.include_topic_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(std::string topic_name, int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas): topic_name_{topic_name}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{std::vector<int32_t>{}}, removing_replicas_{std::vector<int32_t>{}}, is_new_{false}, leader_recovery_state_{0}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(std::string topic_name, int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas, bool is_new): topic_name_{topic_name}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{std::vector<int32_t>{}}, removing_replicas_{std::vector<int32_t>{}}, is_new_{is_new}, leader_recovery_state_{0}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas, bool is_new): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{std::vector<int32_t>{}}, removing_replicas_{std::vector<int32_t>{}}, is_new_{is_new}, leader_recovery_state_{0}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas, std::vector<int32_t> adding_replicas, std::vector<int32_t> removing_replicas, bool is_new): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{adding_replicas}, removing_replicas_{removing_replicas}, is_new_{is_new}, leader_recovery_state_{0}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas, std::vector<int32_t> adding_replicas, std::vector<int32_t> removing_replicas, bool is_new, TaggedFields tagged_fields): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{adding_replicas}, removing_replicas_{removing_replicas}, is_new_{is_new}, leader_recovery_state_{0}, tagged_fields_{tagged_fields} {};
LeaderAndIsrPartitionState::LeaderAndIsrPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t partition_epoch, std::vector<int32_t> replicas, std::vector<int32_t> adding_replicas, std::vector<int32_t> removing_replicas, bool is_new, int8_t leader_recovery_state, TaggedFields tagged_fields): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, partition_epoch_{partition_epoch}, replicas_{replicas}, adding_replicas_{adding_replicas}, removing_replicas_{removing_replicas}, is_new_{is_new}, leader_recovery_state_{leader_recovery_state}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrPartitionState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(controller_epoch_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(leader_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(isr_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(isr_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partition_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(replicas_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(replicas_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(adding_replicas_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(adding_replicas_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(removing_replicas_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(removing_replicas_);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.computeSize(is_new_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeSize(leader_recovery_state_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrPartitionState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrPartitionState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(controller_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(leader_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(isr_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(isr_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partition_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(replicas_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(replicas_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(adding_replicas_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(adding_replicas_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(removing_replicas_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(removing_replicas_, dst);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.encode(is_new_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encode(leader_recovery_state_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrPartitionState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrPartitionState::operator==(const LeaderAndIsrPartitionState& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && controller_epoch_ == rhs.controller_epoch_
  && leader_ == rhs.leader_
  && leader_epoch_ == rhs.leader_epoch_
  && isr_ == rhs.isr_
  && partition_epoch_ == rhs.partition_epoch_
  && replicas_ == rhs.replicas_
  && adding_replicas_ == rhs.adding_replicas_
  && removing_replicas_ == rhs.removing_replicas_
  && is_new_ == rhs.is_new_
  && leader_recovery_state_ == rhs.leader_recovery_state_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrTopicState::LeaderAndIsrTopicState(std::string topic_name, std::vector<LeaderAndIsrPartitionState> partition_states): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partition_states_{partition_states}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrTopicState::LeaderAndIsrTopicState(std::string topic_name, std::vector<LeaderAndIsrPartitionState> partition_states, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partition_states_{partition_states}, tagged_fields_{tagged_fields} {};
LeaderAndIsrTopicState::LeaderAndIsrTopicState(std::string topic_name, Uuid topic_id, std::vector<LeaderAndIsrPartitionState> partition_states, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{topic_id}, partition_states_{partition_states}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrTopicState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeSize(partition_states_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(partition_states_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrTopicState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrTopicState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encode(partition_states_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(partition_states_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrTopicState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrTopicState::operator==(const LeaderAndIsrTopicState& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && topic_id_ == rhs.topic_id_
  && partition_states_ == rhs.partition_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrLiveLeader::LeaderAndIsrLiveLeader(int32_t broker_id, std::string host_name, int32_t port): broker_id_{broker_id}, host_name_{host_name}, port_{port}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrLiveLeader::LeaderAndIsrLiveLeader(int32_t broker_id, std::string host_name, int32_t port, TaggedFields tagged_fields): broker_id_{broker_id}, host_name_{host_name}, port_{port}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrLiveLeader::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(host_name_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(host_name_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrLiveLeader::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrLiveLeader::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(host_name_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(host_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrLiveLeader::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrLiveLeader::operator==(const LeaderAndIsrLiveLeader& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && host_name_ == rhs.host_name_
  && port_ == rhs.port_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaderAndIsrRequest::LeaderAndIsrRequest(int32_t controller_id, int32_t controller_epoch, std::vector<LeaderAndIsrPartitionState> ungrouped_partition_states, std::vector<LeaderAndIsrLiveLeader> live_leaders): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{-1}, type_{0}, ungrouped_partition_states_{ungrouped_partition_states}, topic_states_{std::vector<LeaderAndIsrTopicState>{}}, live_leaders_{live_leaders}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrRequest::LeaderAndIsrRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, std::vector<LeaderAndIsrTopicState> topic_states, std::vector<LeaderAndIsrLiveLeader> live_leaders): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, type_{0}, ungrouped_partition_states_{std::vector<LeaderAndIsrPartitionState>{}}, topic_states_{topic_states}, live_leaders_{live_leaders}, tagged_fields_{TaggedFields({})} {};
LeaderAndIsrRequest::LeaderAndIsrRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, std::vector<LeaderAndIsrTopicState> topic_states, std::vector<LeaderAndIsrLiveLeader> live_leaders, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, type_{0}, ungrouped_partition_states_{std::vector<LeaderAndIsrPartitionState>{}}, topic_states_{topic_states}, live_leaders_{live_leaders}, tagged_fields_{tagged_fields} {};
LeaderAndIsrRequest::LeaderAndIsrRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, int8_t type, std::vector<LeaderAndIsrTopicState> topic_states, std::vector<LeaderAndIsrLiveLeader> live_leaders, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, type_{type}, ungrouped_partition_states_{std::vector<LeaderAndIsrPartitionState>{}}, topic_states_{topic_states}, live_leaders_{live_leaders}, tagged_fields_{tagged_fields} {};
LeaderAndIsrRequest::LeaderAndIsrRequest(int32_t controller_id, bool is_k_raft_controller, int32_t controller_epoch, int64_t broker_epoch, int8_t type, std::vector<LeaderAndIsrTopicState> topic_states, std::vector<LeaderAndIsrLiveLeader> live_leaders, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{is_k_raft_controller}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, type_{type}, ungrouped_partition_states_{std::vector<LeaderAndIsrPartitionState>{}}, topic_states_{topic_states}, live_leaders_{live_leaders}, tagged_fields_{tagged_fields} {};


uint32_t LeaderAndIsrRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.computeSize(is_k_raft_controller_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(controller_epoch_);
  }
  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeSize(type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(ungrouped_partition_states_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeSize(topic_states_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(topic_states_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(live_leaders_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(live_leaders_);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t LeaderAndIsrRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaderAndIsrRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.encode(is_k_raft_controller_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(controller_epoch_, dst);
  }
  
  if (api_version >= 2 && api_version < 8) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encode(type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(ungrouped_partition_states_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encode(topic_states_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(topic_states_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(live_leaders_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(live_leaders_, dst);
  }
  
  if (api_version >= 4 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t LeaderAndIsrRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaderAndIsrRequest::operator==(const LeaderAndIsrRequest& rhs) const {

  return true
  && controller_id_ == rhs.controller_id_
  && is_k_raft_controller_ == rhs.is_k_raft_controller_
  && controller_epoch_ == rhs.controller_epoch_
  && broker_epoch_ == rhs.broker_epoch_
  && type_ == rhs.type_
  && ungrouped_partition_states_ == rhs.ungrouped_partition_states_
  && topic_states_ == rhs.topic_states_
  && live_leaders_ == rhs.live_leaders_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaPartitionV0::StopReplicaPartitionV0(std::string topic_name, int32_t partition_index): topic_name_{topic_name}, partition_index_{partition_index}, tagged_fields_{TaggedFields({})} {};


uint32_t StopReplicaPartitionV0::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaPartitionV0::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaPartitionV0::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaPartitionV0::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaPartitionV0::operator==(const StopReplicaPartitionV0& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaTopicV1::StopReplicaTopicV1(std::string name, std::vector<int32_t> partition_indexes): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{TaggedFields({})} {};
StopReplicaTopicV1::StopReplicaTopicV1(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaTopicV1::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(partition_indexes_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaTopicV1::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaTopicV1::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(partition_indexes_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaTopicV1::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaTopicV1::operator==(const StopReplicaTopicV1& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaPartitionState::StopReplicaPartitionState(int32_t partition_index, int32_t leader_epoch, bool delete_partition, TaggedFields tagged_fields): partition_index_{partition_index}, leader_epoch_{leader_epoch}, delete_partition_{delete_partition}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaPartitionState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(delete_partition_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaPartitionState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaPartitionState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(delete_partition_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaPartitionState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaPartitionState::operator==(const StopReplicaPartitionState& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && leader_epoch_ == rhs.leader_epoch_
  && delete_partition_ == rhs.delete_partition_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaTopicState::StopReplicaTopicState(std::string topic_name, std::vector<StopReplicaPartitionState> partition_states, TaggedFields tagged_fields): topic_name_{topic_name}, partition_states_{partition_states}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaTopicState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(partition_states_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaTopicState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaTopicState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(partition_states_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaTopicState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaTopicState::operator==(const StopReplicaTopicState& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_states_ == rhs.partition_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


StopReplicaRequest::StopReplicaRequest(int32_t controller_id, int32_t controller_epoch, bool delete_partitions, std::vector<StopReplicaPartitionV0> ungrouped_partitions): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{-1}, delete_partitions_{delete_partitions}, ungrouped_partitions_{ungrouped_partitions}, topics_{std::vector<StopReplicaTopicV1>{}}, topic_states_{std::vector<StopReplicaTopicState>{}}, tagged_fields_{TaggedFields({})} {};
StopReplicaRequest::StopReplicaRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, bool delete_partitions, std::vector<StopReplicaTopicV1> topics): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, delete_partitions_{delete_partitions}, ungrouped_partitions_{std::vector<StopReplicaPartitionV0>{}}, topics_{topics}, topic_states_{std::vector<StopReplicaTopicState>{}}, tagged_fields_{TaggedFields({})} {};
StopReplicaRequest::StopReplicaRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, bool delete_partitions, std::vector<StopReplicaTopicV1> topics, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, delete_partitions_{delete_partitions}, ungrouped_partitions_{std::vector<StopReplicaPartitionV0>{}}, topics_{topics}, topic_states_{std::vector<StopReplicaTopicState>{}}, tagged_fields_{tagged_fields} {};
StopReplicaRequest::StopReplicaRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, std::vector<StopReplicaTopicState> topic_states, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, delete_partitions_{false}, ungrouped_partitions_{std::vector<StopReplicaPartitionV0>{}}, topics_{std::vector<StopReplicaTopicV1>{}}, topic_states_{topic_states}, tagged_fields_{tagged_fields} {};
StopReplicaRequest::StopReplicaRequest(int32_t controller_id, bool is_k_raft_controller, int32_t controller_epoch, int64_t broker_epoch, std::vector<StopReplicaTopicState> topic_states, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{is_k_raft_controller}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, delete_partitions_{false}, ungrouped_partitions_{std::vector<StopReplicaPartitionV0>{}}, topics_{std::vector<StopReplicaTopicV1>{}}, topic_states_{topic_states}, tagged_fields_{tagged_fields} {};


uint32_t StopReplicaRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeSize(is_k_raft_controller_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(controller_epoch_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(delete_partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(ungrouped_partitions_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(topic_states_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t StopReplicaRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t StopReplicaRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encode(is_k_raft_controller_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(controller_epoch_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(delete_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(ungrouped_partitions_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(topic_states_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t StopReplicaRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool StopReplicaRequest::operator==(const StopReplicaRequest& rhs) const {

  return true
  && controller_id_ == rhs.controller_id_
  && is_k_raft_controller_ == rhs.is_k_raft_controller_
  && controller_epoch_ == rhs.controller_epoch_
  && broker_epoch_ == rhs.broker_epoch_
  && delete_partitions_ == rhs.delete_partitions_
  && ungrouped_partitions_ == rhs.ungrouped_partitions_
  && topics_ == rhs.topics_
  && topic_states_ == rhs.topic_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataPartitionState::UpdateMetadataPartitionState(std::string topic_name, int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t zk_version, std::vector<int32_t> replicas): topic_name_{topic_name}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, zk_version_{zk_version}, replicas_{replicas}, offline_replicas_{std::vector<int32_t>{}}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataPartitionState::UpdateMetadataPartitionState(std::string topic_name, int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t zk_version, std::vector<int32_t> replicas, std::vector<int32_t> offline_replicas): topic_name_{topic_name}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, zk_version_{zk_version}, replicas_{replicas}, offline_replicas_{offline_replicas}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataPartitionState::UpdateMetadataPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t zk_version, std::vector<int32_t> replicas, std::vector<int32_t> offline_replicas): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, zk_version_{zk_version}, replicas_{replicas}, offline_replicas_{offline_replicas}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataPartitionState::UpdateMetadataPartitionState(int32_t partition_index, int32_t controller_epoch, int32_t leader, int32_t leader_epoch, std::vector<int32_t> isr, int32_t zk_version, std::vector<int32_t> replicas, std::vector<int32_t> offline_replicas, TaggedFields tagged_fields): topic_name_{""}, partition_index_{partition_index}, controller_epoch_{controller_epoch}, leader_{leader}, leader_epoch_{leader_epoch}, isr_{isr}, zk_version_{zk_version}, replicas_{replicas}, offline_replicas_{offline_replicas}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataPartitionState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(controller_epoch_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(leader_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(isr_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(isr_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(zk_version_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(replicas_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(replicas_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(offline_replicas_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(offline_replicas_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataPartitionState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataPartitionState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(controller_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(leader_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(isr_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(isr_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(zk_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(replicas_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(replicas_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(offline_replicas_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(offline_replicas_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataPartitionState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataPartitionState::operator==(const UpdateMetadataPartitionState& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && controller_epoch_ == rhs.controller_epoch_
  && leader_ == rhs.leader_
  && leader_epoch_ == rhs.leader_epoch_
  && isr_ == rhs.isr_
  && zk_version_ == rhs.zk_version_
  && replicas_ == rhs.replicas_
  && offline_replicas_ == rhs.offline_replicas_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataTopicState::UpdateMetadataTopicState(std::string topic_name, std::vector<UpdateMetadataPartitionState> partition_states): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partition_states_{partition_states}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataTopicState::UpdateMetadataTopicState(std::string topic_name, std::vector<UpdateMetadataPartitionState> partition_states, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partition_states_{partition_states}, tagged_fields_{tagged_fields} {};
UpdateMetadataTopicState::UpdateMetadataTopicState(std::string topic_name, Uuid topic_id, std::vector<UpdateMetadataPartitionState> partition_states, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{topic_id}, partition_states_{partition_states}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataTopicState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeSize(topic_name_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(topic_name_);
  }
  
  if (api_version >= 7 && api_version < 9) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeSize(partition_states_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(partition_states_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataTopicState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataTopicState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encode(topic_name_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(topic_name_, dst);
  }
  
  if (api_version >= 7 && api_version < 9) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encode(partition_states_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(partition_states_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataTopicState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataTopicState::operator==(const UpdateMetadataTopicState& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && topic_id_ == rhs.topic_id_
  && partition_states_ == rhs.partition_states_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataEndpoint::UpdateMetadataEndpoint(int32_t port, std::string host, int16_t security_protocol): port_{port}, host_{host}, listener_{""}, security_protocol_{security_protocol}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataEndpoint::UpdateMetadataEndpoint(int32_t port, std::string host, std::string listener, int16_t security_protocol): port_{port}, host_{host}, listener_{listener}, security_protocol_{security_protocol}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataEndpoint::UpdateMetadataEndpoint(int32_t port, std::string host, std::string listener, int16_t security_protocol, TaggedFields tagged_fields): port_{port}, host_{host}, listener_{listener}, security_protocol_{security_protocol}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataEndpoint::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(host_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(listener_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(listener_);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.computeSize(security_protocol_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataEndpoint::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataEndpoint::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(host_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(listener_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(listener_, dst);
  }
  
  if (api_version >= 1 && api_version < 9) {
    written += encoder.encode(security_protocol_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataEndpoint::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataEndpoint::operator==(const UpdateMetadataEndpoint& rhs) const {

  return true
  && port_ == rhs.port_
  && host_ == rhs.host_
  && listener_ == rhs.listener_
  && security_protocol_ == rhs.security_protocol_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataBroker::UpdateMetadataBroker(int32_t id, std::string v0_host, int32_t v0_port): id_{id}, v0_host_{v0_host}, v0_port_{v0_port}, endpoints_{std::vector<UpdateMetadataEndpoint>{}}, rack_{{""}}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataBroker::UpdateMetadataBroker(int32_t id, std::vector<UpdateMetadataEndpoint> endpoints): id_{id}, v0_host_{""}, v0_port_{0}, endpoints_{endpoints}, rack_{{""}}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataBroker::UpdateMetadataBroker(int32_t id, std::vector<UpdateMetadataEndpoint> endpoints, absl::optional<std::string> rack): id_{id}, v0_host_{""}, v0_port_{0}, endpoints_{endpoints}, rack_{rack}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataBroker::UpdateMetadataBroker(int32_t id, std::vector<UpdateMetadataEndpoint> endpoints, absl::optional<std::string> rack, TaggedFields tagged_fields): id_{id}, v0_host_{""}, v0_port_{0}, endpoints_{endpoints}, rack_{rack}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataBroker::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(v0_host_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(v0_port_);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(endpoints_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(endpoints_);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.computeSize(rack_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(rack_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataBroker::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataBroker::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(v0_host_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(v0_port_, dst);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(endpoints_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(endpoints_, dst);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.encode(rack_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(rack_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataBroker::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataBroker::operator==(const UpdateMetadataBroker& rhs) const {

  return true
  && id_ == rhs.id_
  && v0_host_ == rhs.v0_host_
  && v0_port_ == rhs.v0_port_
  && endpoints_ == rhs.endpoints_
  && rack_ == rhs.rack_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateMetadataRequest::UpdateMetadataRequest(int32_t controller_id, int32_t controller_epoch, std::vector<UpdateMetadataPartitionState> ungrouped_partition_states, std::vector<UpdateMetadataBroker> live_brokers): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{-1}, ungrouped_partition_states_{ungrouped_partition_states}, topic_states_{std::vector<UpdateMetadataTopicState>{}}, live_brokers_{live_brokers}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataRequest::UpdateMetadataRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, std::vector<UpdateMetadataTopicState> topic_states, std::vector<UpdateMetadataBroker> live_brokers): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, ungrouped_partition_states_{std::vector<UpdateMetadataPartitionState>{}}, topic_states_{topic_states}, live_brokers_{live_brokers}, tagged_fields_{TaggedFields({})} {};
UpdateMetadataRequest::UpdateMetadataRequest(int32_t controller_id, int32_t controller_epoch, int64_t broker_epoch, std::vector<UpdateMetadataTopicState> topic_states, std::vector<UpdateMetadataBroker> live_brokers, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{false}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, ungrouped_partition_states_{std::vector<UpdateMetadataPartitionState>{}}, topic_states_{topic_states}, live_brokers_{live_brokers}, tagged_fields_{tagged_fields} {};
UpdateMetadataRequest::UpdateMetadataRequest(int32_t controller_id, bool is_k_raft_controller, int32_t controller_epoch, int64_t broker_epoch, std::vector<UpdateMetadataTopicState> topic_states, std::vector<UpdateMetadataBroker> live_brokers, TaggedFields tagged_fields): controller_id_{controller_id}, is_k_raft_controller_{is_k_raft_controller}, controller_epoch_{controller_epoch}, broker_epoch_{broker_epoch}, ungrouped_partition_states_{std::vector<UpdateMetadataPartitionState>{}}, topic_states_{topic_states}, live_brokers_{live_brokers}, tagged_fields_{tagged_fields} {};


uint32_t UpdateMetadataRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.computeSize(is_k_raft_controller_);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.computeSize(controller_epoch_);
  }
  
  if (api_version >= 5 && api_version < 9) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(ungrouped_partition_states_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeSize(topic_states_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(topic_states_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(live_brokers_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(live_brokers_);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateMetadataRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateMetadataRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 8 && api_version < 9) {
    written += encoder.encode(is_k_raft_controller_, dst);
  }
  
  if (api_version >= 0 && api_version < 9) {
    written += encoder.encode(controller_epoch_, dst);
  }
  
  if (api_version >= 5 && api_version < 9) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(ungrouped_partition_states_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encode(topic_states_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(topic_states_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(live_brokers_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(live_brokers_, dst);
  }
  
  if (api_version >= 6 && api_version < 9) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateMetadataRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateMetadataRequest::operator==(const UpdateMetadataRequest& rhs) const {

  return true
  && controller_id_ == rhs.controller_id_
  && is_k_raft_controller_ == rhs.is_k_raft_controller_
  && controller_epoch_ == rhs.controller_epoch_
  && broker_epoch_ == rhs.broker_epoch_
  && ungrouped_partition_states_ == rhs.ungrouped_partition_states_
  && topic_states_ == rhs.topic_states_
  && live_brokers_ == rhs.live_brokers_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControlledShutdownRequest::ControlledShutdownRequest(int32_t broker_id): broker_id_{broker_id}, broker_epoch_{-1}, tagged_fields_{TaggedFields({})} {};
ControlledShutdownRequest::ControlledShutdownRequest(int32_t broker_id, int64_t broker_epoch): broker_id_{broker_id}, broker_epoch_{broker_epoch}, tagged_fields_{TaggedFields({})} {};
ControlledShutdownRequest::ControlledShutdownRequest(int32_t broker_id, int64_t broker_epoch, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, tagged_fields_{tagged_fields} {};


uint32_t ControlledShutdownRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControlledShutdownRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControlledShutdownRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControlledShutdownRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControlledShutdownRequest::operator==(const ControlledShutdownRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitRequestPartition::OffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, absl::optional<std::string> committed_metadata): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{-1}, commit_timestamp_{-1}, committed_metadata_{committed_metadata}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequestPartition::OffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, int64_t commit_timestamp, absl::optional<std::string> committed_metadata): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{-1}, commit_timestamp_{commit_timestamp}, committed_metadata_{committed_metadata}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequestPartition::OffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> committed_metadata): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, commit_timestamp_{-1}, committed_metadata_{committed_metadata}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequestPartition::OffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> committed_metadata, TaggedFields tagged_fields): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, commit_timestamp_{-1}, committed_metadata_{committed_metadata}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitRequestPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(committed_offset_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeSize(committed_leader_epoch_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(commit_timestamp_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(committed_metadata_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(committed_metadata_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetCommitRequestPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitRequestPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(committed_offset_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encode(committed_leader_epoch_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(commit_timestamp_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(committed_metadata_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(committed_metadata_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetCommitRequestPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitRequestPartition::operator==(const OffsetCommitRequestPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && committed_offset_ == rhs.committed_offset_
  && committed_leader_epoch_ == rhs.committed_leader_epoch_
  && commit_timestamp_ == rhs.commit_timestamp_
  && committed_metadata_ == rhs.committed_metadata_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitRequestTopic::OffsetCommitRequestTopic(std::string name, std::vector<OffsetCommitRequestPartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequestTopic::OffsetCommitRequestTopic(std::string name, std::vector<OffsetCommitRequestPartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitRequestTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t OffsetCommitRequestTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitRequestTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t OffsetCommitRequestTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitRequestTopic::operator==(const OffsetCommitRequestTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetCommitRequest::OffsetCommitRequest(std::string group_id, std::vector<OffsetCommitRequestTopic> topics): group_id_{group_id}, generation_id_or_member_epoch_{-1}, member_id_{""}, group_instance_id_{absl::nullopt}, retention_time_ms_{-1}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequest::OffsetCommitRequest(std::string group_id, int32_t generation_id_or_member_epoch, std::string member_id, std::vector<OffsetCommitRequestTopic> topics): group_id_{group_id}, generation_id_or_member_epoch_{generation_id_or_member_epoch}, member_id_{member_id}, group_instance_id_{absl::nullopt}, retention_time_ms_{-1}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequest::OffsetCommitRequest(std::string group_id, int32_t generation_id_or_member_epoch, std::string member_id, int64_t retention_time_ms, std::vector<OffsetCommitRequestTopic> topics): group_id_{group_id}, generation_id_or_member_epoch_{generation_id_or_member_epoch}, member_id_{member_id}, group_instance_id_{absl::nullopt}, retention_time_ms_{retention_time_ms}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequest::OffsetCommitRequest(std::string group_id, int32_t generation_id_or_member_epoch, std::string member_id, absl::optional<std::string> group_instance_id, std::vector<OffsetCommitRequestTopic> topics): group_id_{group_id}, generation_id_or_member_epoch_{generation_id_or_member_epoch}, member_id_{member_id}, group_instance_id_{group_instance_id}, retention_time_ms_{-1}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetCommitRequest::OffsetCommitRequest(std::string group_id, int32_t generation_id_or_member_epoch, std::string member_id, absl::optional<std::string> group_instance_id, std::vector<OffsetCommitRequestTopic> topics, TaggedFields tagged_fields): group_id_{group_id}, generation_id_or_member_epoch_{generation_id_or_member_epoch}, member_id_{member_id}, group_instance_id_{group_instance_id}, retention_time_ms_{-1}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t OffsetCommitRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 1 && api_version < 10) {
    written += encoder.computeSize(generation_id_or_member_epoch_);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.computeSize(group_instance_id_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(group_instance_id_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeSize(retention_time_ms_);
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

uint32_t OffsetCommitRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetCommitRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 1 && api_version < 10) {
    written += encoder.encode(generation_id_or_member_epoch_, dst);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 7 && api_version < 8) {
    written += encoder.encode(group_instance_id_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(group_instance_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encode(retention_time_ms_, dst);
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

uint32_t OffsetCommitRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetCommitRequest::operator==(const OffsetCommitRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && generation_id_or_member_epoch_ == rhs.generation_id_or_member_epoch_
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && retention_time_ms_ == rhs.retention_time_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchRequestTopic::OffsetFetchRequestTopic(std::string name, std::vector<int32_t> partition_indexes): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{TaggedFields({})} {};
OffsetFetchRequestTopic::OffsetFetchRequestTopic(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchRequestTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(partition_indexes_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchRequestTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchRequestTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(partition_indexes_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchRequestTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchRequestTopic::operator==(const OffsetFetchRequestTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchRequestTopics::OffsetFetchRequestTopics(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchRequestTopics::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchRequestTopics::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchRequestTopics::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchRequestTopics::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchRequestTopics::operator==(const OffsetFetchRequestTopics& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchRequestGroup::OffsetFetchRequestGroup(std::string group_id, absl::optional<std::vector<OffsetFetchRequestTopics>> topics, TaggedFields tagged_fields): group_id_{group_id}, member_id_{absl::nullopt}, member_epoch_{-1}, topics_{topics}, tagged_fields_{tagged_fields} {};
OffsetFetchRequestGroup::OffsetFetchRequestGroup(std::string group_id, absl::optional<std::string> member_id, int32_t member_epoch, absl::optional<std::vector<OffsetFetchRequestTopics>> topics, TaggedFields tagged_fields): group_id_{group_id}, member_id_{member_id}, member_epoch_{member_epoch}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchRequestGroup::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.computeSize(member_epoch_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchRequestGroup::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchRequestGroup::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 9 && api_version < 10) {
    written += encoder.encode(member_epoch_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchRequestGroup::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchRequestGroup::operator==(const OffsetFetchRequestGroup& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && member_id_ == rhs.member_id_
  && member_epoch_ == rhs.member_epoch_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetFetchRequest::OffsetFetchRequest(std::string group_id, std::vector<OffsetFetchRequestTopic> topics): group_id_{group_id}, topics_{absl::make_optional(topics)}, groups_{std::vector<OffsetFetchRequestGroup>{}}, require_stable_{false}, tagged_fields_{TaggedFields({})} {};
OffsetFetchRequest::OffsetFetchRequest(std::string group_id, absl::optional<std::vector<OffsetFetchRequestTopic>> topics): group_id_{group_id}, topics_{topics}, groups_{std::vector<OffsetFetchRequestGroup>{}}, require_stable_{false}, tagged_fields_{TaggedFields({})} {};
OffsetFetchRequest::OffsetFetchRequest(std::string group_id, absl::optional<std::vector<OffsetFetchRequestTopic>> topics, TaggedFields tagged_fields): group_id_{group_id}, topics_{topics}, groups_{std::vector<OffsetFetchRequestGroup>{}}, require_stable_{false}, tagged_fields_{tagged_fields} {};
OffsetFetchRequest::OffsetFetchRequest(std::string group_id, absl::optional<std::vector<OffsetFetchRequestTopic>> topics, bool require_stable, TaggedFields tagged_fields): group_id_{group_id}, topics_{topics}, groups_{std::vector<OffsetFetchRequestGroup>{}}, require_stable_{require_stable}, tagged_fields_{tagged_fields} {};
OffsetFetchRequest::OffsetFetchRequest(std::vector<OffsetFetchRequestGroup> groups, bool require_stable, TaggedFields tagged_fields): group_id_{""}, topics_{{std::vector<OffsetFetchRequestTopic>{}}}, groups_{groups}, require_stable_{require_stable}, tagged_fields_{tagged_fields} {};


uint32_t OffsetFetchRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 7 && api_version < 10) {
    written += encoder.computeSize(require_stable_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetFetchRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetFetchRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 6 && api_version < 8) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 7 && api_version < 10) {
    written += encoder.encode(require_stable_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetFetchRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetFetchRequest::operator==(const OffsetFetchRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && topics_ == rhs.topics_
  && groups_ == rhs.groups_
  && require_stable_ == rhs.require_stable_
  && tagged_fields_ == rhs.tagged_fields_;
};


FindCoordinatorRequest::FindCoordinatorRequest(std::string key): key_{key}, key_type_{0}, coordinator_keys_{std::vector<std::string>{}}, tagged_fields_{TaggedFields({})} {};
FindCoordinatorRequest::FindCoordinatorRequest(std::string key, int8_t key_type): key_{key}, key_type_{key_type}, coordinator_keys_{std::vector<std::string>{}}, tagged_fields_{TaggedFields({})} {};
FindCoordinatorRequest::FindCoordinatorRequest(std::string key, int8_t key_type, TaggedFields tagged_fields): key_{key}, key_type_{key_type}, coordinator_keys_{std::vector<std::string>{}}, tagged_fields_{tagged_fields} {};
FindCoordinatorRequest::FindCoordinatorRequest(int8_t key_type, std::vector<std::string> coordinator_keys, TaggedFields tagged_fields): key_{""}, key_type_{key_type}, coordinator_keys_{coordinator_keys}, tagged_fields_{tagged_fields} {};


uint32_t FindCoordinatorRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(key_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(key_);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.computeSize(key_type_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(coordinator_keys_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FindCoordinatorRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FindCoordinatorRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(key_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(key_, dst);
  }
  
  if (api_version >= 1 && api_version < 6) {
    written += encoder.encode(key_type_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(coordinator_keys_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FindCoordinatorRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FindCoordinatorRequest::operator==(const FindCoordinatorRequest& rhs) const {

  return true
  && key_ == rhs.key_
  && key_type_ == rhs.key_type_
  && coordinator_keys_ == rhs.coordinator_keys_
  && tagged_fields_ == rhs.tagged_fields_;
};


JoinGroupRequestProtocol::JoinGroupRequestProtocol(std::string name, Bytes metadata): name_{name}, metadata_{metadata}, tagged_fields_{TaggedFields({})} {};
JoinGroupRequestProtocol::JoinGroupRequestProtocol(std::string name, Bytes metadata, TaggedFields tagged_fields): name_{name}, metadata_{metadata}, tagged_fields_{tagged_fields} {};


uint32_t JoinGroupRequestProtocol::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(name_);
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

uint32_t JoinGroupRequestProtocol::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t JoinGroupRequestProtocol::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(name_, dst);
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

uint32_t JoinGroupRequestProtocol::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool JoinGroupRequestProtocol::operator==(const JoinGroupRequestProtocol& rhs) const {

  return true
  && name_ == rhs.name_
  && metadata_ == rhs.metadata_
  && tagged_fields_ == rhs.tagged_fields_;
};


JoinGroupRequest::JoinGroupRequest(std::string group_id, int32_t session_timeout_ms, std::string member_id, std::string protocol_type, std::vector<JoinGroupRequestProtocol> protocols): group_id_{group_id}, session_timeout_ms_{session_timeout_ms}, rebalance_timeout_ms_{-1}, member_id_{member_id}, group_instance_id_{absl::nullopt}, protocol_type_{protocol_type}, protocols_{protocols}, reason_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
JoinGroupRequest::JoinGroupRequest(std::string group_id, int32_t session_timeout_ms, int32_t rebalance_timeout_ms, std::string member_id, std::string protocol_type, std::vector<JoinGroupRequestProtocol> protocols): group_id_{group_id}, session_timeout_ms_{session_timeout_ms}, rebalance_timeout_ms_{rebalance_timeout_ms}, member_id_{member_id}, group_instance_id_{absl::nullopt}, protocol_type_{protocol_type}, protocols_{protocols}, reason_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
JoinGroupRequest::JoinGroupRequest(std::string group_id, int32_t session_timeout_ms, int32_t rebalance_timeout_ms, std::string member_id, absl::optional<std::string> group_instance_id, std::string protocol_type, std::vector<JoinGroupRequestProtocol> protocols): group_id_{group_id}, session_timeout_ms_{session_timeout_ms}, rebalance_timeout_ms_{rebalance_timeout_ms}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{protocol_type}, protocols_{protocols}, reason_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
JoinGroupRequest::JoinGroupRequest(std::string group_id, int32_t session_timeout_ms, int32_t rebalance_timeout_ms, std::string member_id, absl::optional<std::string> group_instance_id, std::string protocol_type, std::vector<JoinGroupRequestProtocol> protocols, TaggedFields tagged_fields): group_id_{group_id}, session_timeout_ms_{session_timeout_ms}, rebalance_timeout_ms_{rebalance_timeout_ms}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{protocol_type}, protocols_{protocols}, reason_{absl::nullopt}, tagged_fields_{tagged_fields} {};
JoinGroupRequest::JoinGroupRequest(std::string group_id, int32_t session_timeout_ms, int32_t rebalance_timeout_ms, std::string member_id, absl::optional<std::string> group_instance_id, std::string protocol_type, std::vector<JoinGroupRequestProtocol> protocols, absl::optional<std::string> reason, TaggedFields tagged_fields): group_id_{group_id}, session_timeout_ms_{session_timeout_ms}, rebalance_timeout_ms_{rebalance_timeout_ms}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{protocol_type}, protocols_{protocols}, reason_{reason}, tagged_fields_{tagged_fields} {};


uint32_t JoinGroupRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.computeSize(session_timeout_ms_);
  }
  
  if (api_version >= 1 && api_version < 10) {
    written += encoder.computeSize(rebalance_timeout_ms_);
  }
  
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
    written += encoder.computeSize(protocol_type_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(protocols_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(protocols_);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.computeCompactSize(reason_);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t JoinGroupRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t JoinGroupRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 10) {
    written += encoder.encode(session_timeout_ms_, dst);
  }
  
  if (api_version >= 1 && api_version < 10) {
    written += encoder.encode(rebalance_timeout_ms_, dst);
  }
  
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
    written += encoder.encode(protocol_type_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(protocols_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(protocols_, dst);
  }
  
  if (api_version >= 8 && api_version < 10) {
    written += encoder.encodeCompact(reason_, dst);
  }
  
  if (api_version >= 6 && api_version < 10) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t JoinGroupRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool JoinGroupRequest::operator==(const JoinGroupRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && session_timeout_ms_ == rhs.session_timeout_ms_
  && rebalance_timeout_ms_ == rhs.rebalance_timeout_ms_
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && protocol_type_ == rhs.protocol_type_
  && protocols_ == rhs.protocols_
  && reason_ == rhs.reason_
  && tagged_fields_ == rhs.tagged_fields_;
};


HeartbeatRequest::HeartbeatRequest(std::string group_id, int32_t generation_id, std::string member_id): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
HeartbeatRequest::HeartbeatRequest(std::string group_id, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, tagged_fields_{TaggedFields({})} {};
HeartbeatRequest::HeartbeatRequest(std::string group_id, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id, TaggedFields tagged_fields): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, tagged_fields_{tagged_fields} {};


uint32_t HeartbeatRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(generation_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(group_instance_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(group_instance_id_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t HeartbeatRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t HeartbeatRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(generation_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(group_instance_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(group_instance_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t HeartbeatRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool HeartbeatRequest::operator==(const HeartbeatRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && generation_id_ == rhs.generation_id_
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && tagged_fields_ == rhs.tagged_fields_;
};


MemberIdentity::MemberIdentity(std::string member_id, absl::optional<std::string> group_instance_id): member_id_{member_id}, group_instance_id_{group_instance_id}, reason_{absl::nullopt}, tagged_fields_{TaggedFields({})} {};
MemberIdentity::MemberIdentity(std::string member_id, absl::optional<std::string> group_instance_id, TaggedFields tagged_fields): member_id_{member_id}, group_instance_id_{group_instance_id}, reason_{absl::nullopt}, tagged_fields_{tagged_fields} {};
MemberIdentity::MemberIdentity(std::string member_id, absl::optional<std::string> group_instance_id, absl::optional<std::string> reason, TaggedFields tagged_fields): member_id_{member_id}, group_instance_id_{group_instance_id}, reason_{reason}, tagged_fields_{tagged_fields} {};


uint32_t MemberIdentity::computeSize(const EncodingContext& encoder) const {
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
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(reason_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t MemberIdentity::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t MemberIdentity::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(reason_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t MemberIdentity::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool MemberIdentity::operator==(const MemberIdentity& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && reason_ == rhs.reason_
  && tagged_fields_ == rhs.tagged_fields_;
};


LeaveGroupRequest::LeaveGroupRequest(std::string group_id, std::string member_id): group_id_{group_id}, member_id_{member_id}, members_{std::vector<MemberIdentity>{}}, tagged_fields_{TaggedFields({})} {};
LeaveGroupRequest::LeaveGroupRequest(std::string group_id, std::vector<MemberIdentity> members): group_id_{group_id}, member_id_{""}, members_{members}, tagged_fields_{TaggedFields({})} {};
LeaveGroupRequest::LeaveGroupRequest(std::string group_id, std::vector<MemberIdentity> members, TaggedFields tagged_fields): group_id_{group_id}, member_id_{""}, members_{members}, tagged_fields_{tagged_fields} {};


uint32_t LeaveGroupRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(member_id_);
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

uint32_t LeaveGroupRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t LeaveGroupRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(member_id_, dst);
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

uint32_t LeaveGroupRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool LeaveGroupRequest::operator==(const LeaveGroupRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && member_id_ == rhs.member_id_
  && members_ == rhs.members_
  && tagged_fields_ == rhs.tagged_fields_;
};


SyncGroupRequestAssignment::SyncGroupRequestAssignment(std::string member_id, Bytes assignment): member_id_{member_id}, assignment_{assignment}, tagged_fields_{TaggedFields({})} {};
SyncGroupRequestAssignment::SyncGroupRequestAssignment(std::string member_id, Bytes assignment, TaggedFields tagged_fields): member_id_{member_id}, assignment_{assignment}, tagged_fields_{tagged_fields} {};


uint32_t SyncGroupRequestAssignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(member_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(member_id_);
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

uint32_t SyncGroupRequestAssignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SyncGroupRequestAssignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(member_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(member_id_, dst);
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

uint32_t SyncGroupRequestAssignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SyncGroupRequestAssignment::operator==(const SyncGroupRequestAssignment& rhs) const {

  return true
  && member_id_ == rhs.member_id_
  && assignment_ == rhs.assignment_
  && tagged_fields_ == rhs.tagged_fields_;
};


SyncGroupRequest::SyncGroupRequest(std::string group_id, int32_t generation_id, std::string member_id, std::vector<SyncGroupRequestAssignment> assignments): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{absl::nullopt}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignments_{assignments}, tagged_fields_{TaggedFields({})} {};
SyncGroupRequest::SyncGroupRequest(std::string group_id, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id, std::vector<SyncGroupRequestAssignment> assignments): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignments_{assignments}, tagged_fields_{TaggedFields({})} {};
SyncGroupRequest::SyncGroupRequest(std::string group_id, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id, std::vector<SyncGroupRequestAssignment> assignments, TaggedFields tagged_fields): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{absl::nullopt}, protocol_name_{absl::nullopt}, assignments_{assignments}, tagged_fields_{tagged_fields} {};
SyncGroupRequest::SyncGroupRequest(std::string group_id, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id, absl::optional<std::string> protocol_type, absl::optional<std::string> protocol_name, std::vector<SyncGroupRequestAssignment> assignments, TaggedFields tagged_fields): group_id_{group_id}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, protocol_type_{protocol_type}, protocol_name_{protocol_name}, assignments_{assignments}, tagged_fields_{tagged_fields} {};


uint32_t SyncGroupRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(generation_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
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
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_type_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(protocol_name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(assignments_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(assignments_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t SyncGroupRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SyncGroupRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(generation_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
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
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_type_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(protocol_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(assignments_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(assignments_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t SyncGroupRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SyncGroupRequest::operator==(const SyncGroupRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && generation_id_ == rhs.generation_id_
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && protocol_type_ == rhs.protocol_type_
  && protocol_name_ == rhs.protocol_name_
  && assignments_ == rhs.assignments_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeGroupsRequest::DescribeGroupsRequest(std::vector<std::string> groups): groups_{groups}, include_authorized_operations_{false}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsRequest::DescribeGroupsRequest(std::vector<std::string> groups, bool include_authorized_operations): groups_{groups}, include_authorized_operations_{include_authorized_operations}, tagged_fields_{TaggedFields({})} {};
DescribeGroupsRequest::DescribeGroupsRequest(std::vector<std::string> groups, bool include_authorized_operations, TaggedFields tagged_fields): groups_{groups}, include_authorized_operations_{include_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t DescribeGroupsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(groups_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(groups_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(include_authorized_operations_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeGroupsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeGroupsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(groups_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(groups_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(include_authorized_operations_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeGroupsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeGroupsRequest::operator==(const DescribeGroupsRequest& rhs) const {

  return true
  && groups_ == rhs.groups_
  && include_authorized_operations_ == rhs.include_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListGroupsRequest::ListGroupsRequest() {};
ListGroupsRequest::ListGroupsRequest(TaggedFields tagged_fields): states_filter_{std::vector<std::string>{}}, types_filter_{std::vector<std::string>{}}, tagged_fields_{tagged_fields} {};
ListGroupsRequest::ListGroupsRequest(std::vector<std::string> states_filter, TaggedFields tagged_fields): states_filter_{states_filter}, types_filter_{std::vector<std::string>{}}, tagged_fields_{tagged_fields} {};
ListGroupsRequest::ListGroupsRequest(std::vector<std::string> states_filter, std::vector<std::string> types_filter, TaggedFields tagged_fields): states_filter_{states_filter}, types_filter_{types_filter}, tagged_fields_{tagged_fields} {};


uint32_t ListGroupsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(states_filter_);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.computeCompactSize(types_filter_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListGroupsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListGroupsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(states_filter_, dst);
  }
  
  if (api_version >= 5 && api_version < 6) {
    written += encoder.encodeCompact(types_filter_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListGroupsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListGroupsRequest::operator==(const ListGroupsRequest& rhs) const {

  return true
  && states_filter_ == rhs.states_filter_
  && types_filter_ == rhs.types_filter_
  && tagged_fields_ == rhs.tagged_fields_;
};


SaslHandshakeRequest::SaslHandshakeRequest(std::string mechanism): mechanism_{mechanism} {};


uint32_t SaslHandshakeRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(mechanism_);
  }
  

  return written;
}

uint32_t SaslHandshakeRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SaslHandshakeRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(mechanism_, dst);
  }
  

  return written;
}

uint32_t SaslHandshakeRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SaslHandshakeRequest::operator==(const SaslHandshakeRequest& rhs) const {

  return true
  && mechanism_ == rhs.mechanism_;
};


ApiVersionsRequest::ApiVersionsRequest() {};
ApiVersionsRequest::ApiVersionsRequest(std::string client_software_name, std::string client_software_version, TaggedFields tagged_fields): client_software_name_{client_software_name}, client_software_version_{client_software_version}, tagged_fields_{tagged_fields} {};


uint32_t ApiVersionsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(client_software_name_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(client_software_version_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ApiVersionsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ApiVersionsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(client_software_name_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(client_software_version_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ApiVersionsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ApiVersionsRequest::operator==(const ApiVersionsRequest& rhs) const {

  return true
  && client_software_name_ == rhs.client_software_name_
  && client_software_version_ == rhs.client_software_version_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatableReplicaAssignment::CreatableReplicaAssignment(int32_t partition_index, std::vector<int32_t> broker_ids): partition_index_{partition_index}, broker_ids_{broker_ids}, tagged_fields_{TaggedFields({})} {};
CreatableReplicaAssignment::CreatableReplicaAssignment(int32_t partition_index, std::vector<int32_t> broker_ids, TaggedFields tagged_fields): partition_index_{partition_index}, broker_ids_{broker_ids}, tagged_fields_{tagged_fields} {};


uint32_t CreatableReplicaAssignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(broker_ids_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(broker_ids_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatableReplicaAssignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatableReplicaAssignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(broker_ids_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(broker_ids_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatableReplicaAssignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatableReplicaAssignment::operator==(const CreatableReplicaAssignment& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && broker_ids_ == rhs.broker_ids_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateableTopicConfig::CreateableTopicConfig(std::string name, absl::optional<std::string> value): name_{name}, value_{value}, tagged_fields_{TaggedFields({})} {};
CreateableTopicConfig::CreateableTopicConfig(std::string name, absl::optional<std::string> value, TaggedFields tagged_fields): name_{name}, value_{value}, tagged_fields_{tagged_fields} {};


uint32_t CreateableTopicConfig::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateableTopicConfig::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateableTopicConfig::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateableTopicConfig::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateableTopicConfig::operator==(const CreateableTopicConfig& rhs) const {

  return true
  && name_ == rhs.name_
  && value_ == rhs.value_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatableTopic::CreatableTopic(std::string name, int32_t num_partitions, int16_t replication_factor, std::vector<CreatableReplicaAssignment> assignments, std::vector<CreateableTopicConfig> configs): name_{name}, num_partitions_{num_partitions}, replication_factor_{replication_factor}, assignments_{assignments}, configs_{configs}, tagged_fields_{TaggedFields({})} {};
CreatableTopic::CreatableTopic(std::string name, int32_t num_partitions, int16_t replication_factor, std::vector<CreatableReplicaAssignment> assignments, std::vector<CreateableTopicConfig> configs, TaggedFields tagged_fields): name_{name}, num_partitions_{num_partitions}, replication_factor_{replication_factor}, assignments_{assignments}, configs_{configs}, tagged_fields_{tagged_fields} {};


uint32_t CreatableTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(num_partitions_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(replication_factor_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(assignments_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(assignments_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(configs_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(configs_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatableTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatableTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(num_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(replication_factor_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(assignments_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(assignments_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(configs_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(configs_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatableTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatableTopic::operator==(const CreatableTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && num_partitions_ == rhs.num_partitions_
  && replication_factor_ == rhs.replication_factor_
  && assignments_ == rhs.assignments_
  && configs_ == rhs.configs_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateTopicsRequest::CreateTopicsRequest(std::vector<CreatableTopic> topics, int32_t timeout_ms): topics_{topics}, timeout_ms_{timeout_ms}, validate_only_{false}, tagged_fields_{TaggedFields({})} {};
CreateTopicsRequest::CreateTopicsRequest(std::vector<CreatableTopic> topics, int32_t timeout_ms, bool validate_only): topics_{topics}, timeout_ms_{timeout_ms}, validate_only_{validate_only}, tagged_fields_{TaggedFields({})} {};
CreateTopicsRequest::CreateTopicsRequest(std::vector<CreatableTopic> topics, int32_t timeout_ms, bool validate_only, TaggedFields tagged_fields): topics_{topics}, timeout_ms_{timeout_ms}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t CreateTopicsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateTopicsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateTopicsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 8) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 1 && api_version < 8) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 5 && api_version < 8) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateTopicsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateTopicsRequest::operator==(const CreateTopicsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && timeout_ms_ == rhs.timeout_ms_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteTopicState::DeleteTopicState(absl::optional<std::string> name, Uuid topic_id, TaggedFields tagged_fields): name_{name}, topic_id_{topic_id}, tagged_fields_{tagged_fields} {};


uint32_t DeleteTopicState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.computeSize(topic_id_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteTopicState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteTopicState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.encode(topic_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteTopicState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteTopicState::operator==(const DeleteTopicState& rhs) const {

  return true
  && name_ == rhs.name_
  && topic_id_ == rhs.topic_id_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteTopicsRequest::DeleteTopicsRequest(std::vector<std::string> topic_names, int32_t timeout_ms): topics_{std::vector<DeleteTopicState>{}}, topic_names_{topic_names}, timeout_ms_{timeout_ms}, tagged_fields_{TaggedFields({})} {};
DeleteTopicsRequest::DeleteTopicsRequest(std::vector<std::string> topic_names, int32_t timeout_ms, TaggedFields tagged_fields): topics_{std::vector<DeleteTopicState>{}}, topic_names_{topic_names}, timeout_ms_{timeout_ms}, tagged_fields_{tagged_fields} {};
DeleteTopicsRequest::DeleteTopicsRequest(std::vector<DeleteTopicState> topics, int32_t timeout_ms, TaggedFields tagged_fields): topics_{topics}, topic_names_{std::vector<std::string>{}}, timeout_ms_{timeout_ms}, tagged_fields_{tagged_fields} {};


uint32_t DeleteTopicsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(topic_names_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(topic_names_);
  }
  
  if (api_version >= 0 && api_version < 7) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteTopicsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteTopicsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 6 && api_version < 7) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(topic_names_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(topic_names_, dst);
  }
  
  if (api_version >= 0 && api_version < 7) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 4 && api_version < 7) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteTopicsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteTopicsRequest::operator==(const DeleteTopicsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && topic_names_ == rhs.topic_names_
  && timeout_ms_ == rhs.timeout_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsPartition::DeleteRecordsPartition(int32_t partition_index, int64_t offset): partition_index_{partition_index}, offset_{offset}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsPartition::DeleteRecordsPartition(int32_t partition_index, int64_t offset, TaggedFields tagged_fields): partition_index_{partition_index}, offset_{offset}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(offset_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteRecordsPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(offset_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteRecordsPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsPartition::operator==(const DeleteRecordsPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && offset_ == rhs.offset_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsTopic::DeleteRecordsTopic(std::string name, std::vector<DeleteRecordsPartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsTopic::DeleteRecordsTopic(std::string name, std::vector<DeleteRecordsPartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t DeleteRecordsTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t DeleteRecordsTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsTopic::operator==(const DeleteRecordsTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteRecordsRequest::DeleteRecordsRequest(std::vector<DeleteRecordsTopic> topics, int32_t timeout_ms): topics_{topics}, timeout_ms_{timeout_ms}, tagged_fields_{TaggedFields({})} {};
DeleteRecordsRequest::DeleteRecordsRequest(std::vector<DeleteRecordsTopic> topics, int32_t timeout_ms, TaggedFields tagged_fields): topics_{topics}, timeout_ms_{timeout_ms}, tagged_fields_{tagged_fields} {};


uint32_t DeleteRecordsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteRecordsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteRecordsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteRecordsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteRecordsRequest::operator==(const DeleteRecordsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && timeout_ms_ == rhs.timeout_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


InitProducerIdRequest::InitProducerIdRequest(absl::optional<std::string> transactional_id, int32_t transaction_timeout_ms): transactional_id_{transactional_id}, transaction_timeout_ms_{transaction_timeout_ms}, producer_id_{-1}, producer_epoch_{-1}, tagged_fields_{TaggedFields({})} {};
InitProducerIdRequest::InitProducerIdRequest(absl::optional<std::string> transactional_id, int32_t transaction_timeout_ms, TaggedFields tagged_fields): transactional_id_{transactional_id}, transaction_timeout_ms_{transaction_timeout_ms}, producer_id_{-1}, producer_epoch_{-1}, tagged_fields_{tagged_fields} {};
InitProducerIdRequest::InitProducerIdRequest(absl::optional<std::string> transactional_id, int32_t transaction_timeout_ms, int64_t producer_id, int16_t producer_epoch, TaggedFields tagged_fields): transactional_id_{transactional_id}, transaction_timeout_ms_{transaction_timeout_ms}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, tagged_fields_{tagged_fields} {};


uint32_t InitProducerIdRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(transactional_id_);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.computeSize(transaction_timeout_ms_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t InitProducerIdRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t InitProducerIdRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(transactional_id_, dst);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 6) {
    written += encoder.encode(transaction_timeout_ms_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 2 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t InitProducerIdRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool InitProducerIdRequest::operator==(const InitProducerIdRequest& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && transaction_timeout_ms_ == rhs.transaction_timeout_ms_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetForLeaderPartition::OffsetForLeaderPartition(int32_t partition, int32_t leader_epoch): partition_{partition}, current_leader_epoch_{-1}, leader_epoch_{leader_epoch}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderPartition::OffsetForLeaderPartition(int32_t partition, int32_t current_leader_epoch, int32_t leader_epoch): partition_{partition}, current_leader_epoch_{current_leader_epoch}, leader_epoch_{leader_epoch}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderPartition::OffsetForLeaderPartition(int32_t partition, int32_t current_leader_epoch, int32_t leader_epoch, TaggedFields tagged_fields): partition_{partition}, current_leader_epoch_{current_leader_epoch}, leader_epoch_{leader_epoch}, tagged_fields_{tagged_fields} {};


uint32_t OffsetForLeaderPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeSize(current_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OffsetForLeaderPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetForLeaderPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encode(current_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OffsetForLeaderPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetForLeaderPartition::operator==(const OffsetForLeaderPartition& rhs) const {

  return true
  && partition_ == rhs.partition_
  && current_leader_epoch_ == rhs.current_leader_epoch_
  && leader_epoch_ == rhs.leader_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetForLeaderTopic::OffsetForLeaderTopic(std::string topic, std::vector<OffsetForLeaderPartition> partitions): topic_{topic}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderTopic::OffsetForLeaderTopic(std::string topic, std::vector<OffsetForLeaderPartition> partitions, TaggedFields tagged_fields): topic_{topic}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t OffsetForLeaderTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t OffsetForLeaderTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetForLeaderTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t OffsetForLeaderTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetForLeaderTopic::operator==(const OffsetForLeaderTopic& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetForLeaderEpochRequest::OffsetForLeaderEpochRequest(std::vector<OffsetForLeaderTopic> topics): replica_id_{-2}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderEpochRequest::OffsetForLeaderEpochRequest(int32_t replica_id, std::vector<OffsetForLeaderTopic> topics): replica_id_{replica_id}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
OffsetForLeaderEpochRequest::OffsetForLeaderEpochRequest(int32_t replica_id, std::vector<OffsetForLeaderTopic> topics, TaggedFields tagged_fields): replica_id_{replica_id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t OffsetForLeaderEpochRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(replica_id_);
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

uint32_t OffsetForLeaderEpochRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetForLeaderEpochRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(replica_id_, dst);
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

uint32_t OffsetForLeaderEpochRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetForLeaderEpochRequest::operator==(const OffsetForLeaderEpochRequest& rhs) const {

  return true
  && replica_id_ == rhs.replica_id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnTopic::AddPartitionsToTxnTopic(std::string name, std::vector<int32_t> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
AddPartitionsToTxnTopic::AddPartitionsToTxnTopic(std::string name, std::vector<int32_t> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(partitions_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(partitions_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(partitions_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnTopic::operator==(const AddPartitionsToTxnTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnTransaction::AddPartitionsToTxnTransaction(std::string transactional_id, int64_t producer_id, int16_t producer_epoch, bool verify_only, std::vector<AddPartitionsToTxnTopic> topics, TaggedFields tagged_fields): transactional_id_{transactional_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, verify_only_{verify_only}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnTransaction::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeSize(verify_only_);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTransaction::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnTransaction::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encode(verify_only_, dst);
  }
  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnTransaction::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnTransaction::operator==(const AddPartitionsToTxnTransaction& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && verify_only_ == rhs.verify_only_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddPartitionsToTxnRequest::AddPartitionsToTxnRequest(std::string v3_and_below_transactional_id, int64_t v3_and_below_producer_id, int16_t v3_and_below_producer_epoch, std::vector<AddPartitionsToTxnTopic> v3_and_below_topics): transactions_{std::vector<AddPartitionsToTxnTransaction>{}}, v3_and_below_transactional_id_{v3_and_below_transactional_id}, v3_and_below_producer_id_{v3_and_below_producer_id}, v3_and_below_producer_epoch_{v3_and_below_producer_epoch}, v3_and_below_topics_{v3_and_below_topics}, tagged_fields_{TaggedFields({})} {};
AddPartitionsToTxnRequest::AddPartitionsToTxnRequest(std::string v3_and_below_transactional_id, int64_t v3_and_below_producer_id, int16_t v3_and_below_producer_epoch, std::vector<AddPartitionsToTxnTopic> v3_and_below_topics, TaggedFields tagged_fields): transactions_{std::vector<AddPartitionsToTxnTransaction>{}}, v3_and_below_transactional_id_{v3_and_below_transactional_id}, v3_and_below_producer_id_{v3_and_below_producer_id}, v3_and_below_producer_epoch_{v3_and_below_producer_epoch}, v3_and_below_topics_{v3_and_below_topics}, tagged_fields_{tagged_fields} {};
AddPartitionsToTxnRequest::AddPartitionsToTxnRequest(std::vector<AddPartitionsToTxnTransaction> transactions, TaggedFields tagged_fields): transactions_{transactions}, v3_and_below_transactional_id_{""}, v3_and_below_producer_id_{0}, v3_and_below_producer_epoch_{0}, v3_and_below_topics_{std::vector<AddPartitionsToTxnTopic>{}}, tagged_fields_{tagged_fields} {};


uint32_t AddPartitionsToTxnRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.computeCompactSize(transactions_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(v3_and_below_transactional_id_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(v3_and_below_transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(v3_and_below_producer_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(v3_and_below_producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(v3_and_below_topics_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(v3_and_below_topics_);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddPartitionsToTxnRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 4 && api_version < 6) {
    written += encoder.encodeCompact(transactions_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(v3_and_below_transactional_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(v3_and_below_transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(v3_and_below_producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(v3_and_below_producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(v3_and_below_topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(v3_and_below_topics_, dst);
  }
  
  if (api_version >= 3 && api_version < 6) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddPartitionsToTxnRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddPartitionsToTxnRequest::operator==(const AddPartitionsToTxnRequest& rhs) const {

  return true
  && transactions_ == rhs.transactions_
  && v3_and_below_transactional_id_ == rhs.v3_and_below_transactional_id_
  && v3_and_below_producer_id_ == rhs.v3_and_below_producer_id_
  && v3_and_below_producer_epoch_ == rhs.v3_and_below_producer_epoch_
  && v3_and_below_topics_ == rhs.v3_and_below_topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AddOffsetsToTxnRequest::AddOffsetsToTxnRequest(std::string transactional_id, int64_t producer_id, int16_t producer_epoch, std::string group_id): transactional_id_{transactional_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, group_id_{group_id}, tagged_fields_{TaggedFields({})} {};
AddOffsetsToTxnRequest::AddOffsetsToTxnRequest(std::string transactional_id, int64_t producer_id, int16_t producer_epoch, std::string group_id, TaggedFields tagged_fields): transactional_id_{transactional_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, group_id_{group_id}, tagged_fields_{tagged_fields} {};


uint32_t AddOffsetsToTxnRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(transactional_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AddOffsetsToTxnRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AddOffsetsToTxnRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(transactional_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AddOffsetsToTxnRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AddOffsetsToTxnRequest::operator==(const AddOffsetsToTxnRequest& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && group_id_ == rhs.group_id_
  && tagged_fields_ == rhs.tagged_fields_;
};


EndTxnRequest::EndTxnRequest(std::string transactional_id, int64_t producer_id, int16_t producer_epoch, bool committed): transactional_id_{transactional_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, committed_{committed}, tagged_fields_{TaggedFields({})} {};
EndTxnRequest::EndTxnRequest(std::string transactional_id, int64_t producer_id, int16_t producer_epoch, bool committed, TaggedFields tagged_fields): transactional_id_{transactional_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, committed_{committed}, tagged_fields_{tagged_fields} {};


uint32_t EndTxnRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(transactional_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(committed_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t EndTxnRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndTxnRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(transactional_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(committed_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t EndTxnRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndTxnRequest::operator==(const EndTxnRequest& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && committed_ == rhs.committed_
  && tagged_fields_ == rhs.tagged_fields_;
};


WritableTxnMarkerTopic::WritableTxnMarkerTopic(std::string name, std::vector<int32_t> partition_indexes): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{TaggedFields({})} {};
WritableTxnMarkerTopic::WritableTxnMarkerTopic(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t WritableTxnMarkerTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_indexes_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WritableTxnMarkerTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WritableTxnMarkerTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_indexes_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WritableTxnMarkerTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WritableTxnMarkerTopic::operator==(const WritableTxnMarkerTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


WritableTxnMarker::WritableTxnMarker(int64_t producer_id, int16_t producer_epoch, bool transaction_result, std::vector<WritableTxnMarkerTopic> topics, int32_t coordinator_epoch): producer_id_{producer_id}, producer_epoch_{producer_epoch}, transaction_result_{transaction_result}, topics_{topics}, coordinator_epoch_{coordinator_epoch}, tagged_fields_{TaggedFields({})} {};
WritableTxnMarker::WritableTxnMarker(int64_t producer_id, int16_t producer_epoch, bool transaction_result, std::vector<WritableTxnMarkerTopic> topics, int32_t coordinator_epoch, TaggedFields tagged_fields): producer_id_{producer_id}, producer_epoch_{producer_epoch}, transaction_result_{transaction_result}, topics_{topics}, coordinator_epoch_{coordinator_epoch}, tagged_fields_{tagged_fields} {};


uint32_t WritableTxnMarker::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(transaction_result_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(coordinator_epoch_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t WritableTxnMarker::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WritableTxnMarker::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(transaction_result_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(coordinator_epoch_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t WritableTxnMarker::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WritableTxnMarker::operator==(const WritableTxnMarker& rhs) const {

  return true
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && transaction_result_ == rhs.transaction_result_
  && topics_ == rhs.topics_
  && coordinator_epoch_ == rhs.coordinator_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


WriteTxnMarkersRequest::WriteTxnMarkersRequest(std::vector<WritableTxnMarker> markers): markers_{markers}, tagged_fields_{TaggedFields({})} {};
WriteTxnMarkersRequest::WriteTxnMarkersRequest(std::vector<WritableTxnMarker> markers, TaggedFields tagged_fields): markers_{markers}, tagged_fields_{tagged_fields} {};


uint32_t WriteTxnMarkersRequest::computeSize(const EncodingContext& encoder) const {
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

uint32_t WriteTxnMarkersRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t WriteTxnMarkersRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t WriteTxnMarkersRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool WriteTxnMarkersRequest::operator==(const WriteTxnMarkersRequest& rhs) const {

  return true
  && markers_ == rhs.markers_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitRequestPartition::TxnOffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, absl::optional<std::string> committed_metadata): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{-1}, committed_metadata_{committed_metadata}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitRequestPartition::TxnOffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> committed_metadata): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, committed_metadata_{committed_metadata}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitRequestPartition::TxnOffsetCommitRequestPartition(int32_t partition_index, int64_t committed_offset, int32_t committed_leader_epoch, absl::optional<std::string> committed_metadata, TaggedFields tagged_fields): partition_index_{partition_index}, committed_offset_{committed_offset}, committed_leader_epoch_{committed_leader_epoch}, committed_metadata_{committed_metadata}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitRequestPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(committed_offset_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeSize(committed_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(committed_metadata_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(committed_metadata_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TxnOffsetCommitRequestPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitRequestPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(committed_offset_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encode(committed_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(committed_metadata_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(committed_metadata_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TxnOffsetCommitRequestPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitRequestPartition::operator==(const TxnOffsetCommitRequestPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && committed_offset_ == rhs.committed_offset_
  && committed_leader_epoch_ == rhs.committed_leader_epoch_
  && committed_metadata_ == rhs.committed_metadata_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitRequestTopic::TxnOffsetCommitRequestTopic(std::string name, std::vector<TxnOffsetCommitRequestPartition> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitRequestTopic::TxnOffsetCommitRequestTopic(std::string name, std::vector<TxnOffsetCommitRequestPartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitRequestTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t TxnOffsetCommitRequestTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitRequestTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t TxnOffsetCommitRequestTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitRequestTopic::operator==(const TxnOffsetCommitRequestTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


TxnOffsetCommitRequest::TxnOffsetCommitRequest(std::string transactional_id, std::string group_id, int64_t producer_id, int16_t producer_epoch, std::vector<TxnOffsetCommitRequestTopic> topics): transactional_id_{transactional_id}, group_id_{group_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, generation_id_{-1}, member_id_{}, group_instance_id_{absl::nullopt}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
TxnOffsetCommitRequest::TxnOffsetCommitRequest(std::string transactional_id, std::string group_id, int64_t producer_id, int16_t producer_epoch, int32_t generation_id, std::string member_id, absl::optional<std::string> group_instance_id, std::vector<TxnOffsetCommitRequestTopic> topics, TaggedFields tagged_fields): transactional_id_{transactional_id}, group_id_{group_id}, producer_id_{producer_id}, producer_epoch_{producer_epoch}, generation_id_{generation_id}, member_id_{member_id}, group_instance_id_{group_instance_id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t TxnOffsetCommitRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(transactional_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(transactional_id_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_id_);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.computeSize(producer_epoch_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(generation_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeCompactSize(group_instance_id_);
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

uint32_t TxnOffsetCommitRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TxnOffsetCommitRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(transactional_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(transactional_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 5) {
    written += encoder.encode(producer_epoch_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(generation_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encodeCompact(group_instance_id_, dst);
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

uint32_t TxnOffsetCommitRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TxnOffsetCommitRequest::operator==(const TxnOffsetCommitRequest& rhs) const {

  return true
  && transactional_id_ == rhs.transactional_id_
  && group_id_ == rhs.group_id_
  && producer_id_ == rhs.producer_id_
  && producer_epoch_ == rhs.producer_epoch_
  && generation_id_ == rhs.generation_id_
  && member_id_ == rhs.member_id_
  && group_instance_id_ == rhs.group_instance_id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeAclsRequest::DescribeAclsRequest(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{3}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DescribeAclsRequest::DescribeAclsRequest(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, int8_t pattern_type_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{pattern_type_filter}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DescribeAclsRequest::DescribeAclsRequest(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, int8_t pattern_type_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type, TaggedFields tagged_fields): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{pattern_type_filter}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{tagged_fields} {};


uint32_t DescribeAclsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resource_type_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(resource_name_filter_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(pattern_type_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(host_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(host_filter_);
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

uint32_t DescribeAclsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeAclsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resource_type_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(resource_name_filter_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(pattern_type_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(host_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(host_filter_, dst);
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

uint32_t DescribeAclsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeAclsRequest::operator==(const DescribeAclsRequest& rhs) const {

  return true
  && resource_type_filter_ == rhs.resource_type_filter_
  && resource_name_filter_ == rhs.resource_name_filter_
  && pattern_type_filter_ == rhs.pattern_type_filter_
  && principal_filter_ == rhs.principal_filter_
  && host_filter_ == rhs.host_filter_
  && operation_ == rhs.operation_
  && permission_type_ == rhs.permission_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


AclCreation::AclCreation(int8_t resource_type, std::string resource_name, std::string principal, std::string host, int8_t operation, int8_t permission_type): resource_type_{resource_type}, resource_name_{resource_name}, resource_pattern_type_{3}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
AclCreation::AclCreation(int8_t resource_type, std::string resource_name, int8_t resource_pattern_type, std::string principal, std::string host, int8_t operation, int8_t permission_type): resource_type_{resource_type}, resource_name_{resource_name}, resource_pattern_type_{resource_pattern_type}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
AclCreation::AclCreation(int8_t resource_type, std::string resource_name, int8_t resource_pattern_type, std::string principal, std::string host, int8_t operation, int8_t permission_type, TaggedFields tagged_fields): resource_type_{resource_type}, resource_name_{resource_name}, resource_pattern_type_{resource_pattern_type}, principal_{principal}, host_{host}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{tagged_fields} {};


uint32_t AclCreation::computeSize(const EncodingContext& encoder) const {
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
    written += encoder.computeSize(resource_pattern_type_);
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

uint32_t AclCreation::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AclCreation::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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
    written += encoder.encode(resource_pattern_type_, dst);
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

uint32_t AclCreation::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AclCreation::operator==(const AclCreation& rhs) const {

  return true
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && resource_pattern_type_ == rhs.resource_pattern_type_
  && principal_ == rhs.principal_
  && host_ == rhs.host_
  && operation_ == rhs.operation_
  && permission_type_ == rhs.permission_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateAclsRequest::CreateAclsRequest(std::vector<AclCreation> creations): creations_{creations}, tagged_fields_{TaggedFields({})} {};
CreateAclsRequest::CreateAclsRequest(std::vector<AclCreation> creations, TaggedFields tagged_fields): creations_{creations}, tagged_fields_{tagged_fields} {};


uint32_t CreateAclsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(creations_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(creations_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateAclsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateAclsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(creations_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(creations_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateAclsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateAclsRequest::operator==(const CreateAclsRequest& rhs) const {

  return true
  && creations_ == rhs.creations_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteAclsFilter::DeleteAclsFilter(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{3}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DeleteAclsFilter::DeleteAclsFilter(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, int8_t pattern_type_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{pattern_type_filter}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{TaggedFields({})} {};
DeleteAclsFilter::DeleteAclsFilter(int8_t resource_type_filter, absl::optional<std::string> resource_name_filter, int8_t pattern_type_filter, absl::optional<std::string> principal_filter, absl::optional<std::string> host_filter, int8_t operation, int8_t permission_type, TaggedFields tagged_fields): resource_type_filter_{resource_type_filter}, resource_name_filter_{resource_name_filter}, pattern_type_filter_{pattern_type_filter}, principal_filter_{principal_filter}, host_filter_{host_filter}, operation_{operation}, permission_type_{permission_type}, tagged_fields_{tagged_fields} {};


uint32_t DeleteAclsFilter::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resource_type_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(resource_name_filter_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(pattern_type_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(principal_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(principal_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(host_filter_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(host_filter_);
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

uint32_t DeleteAclsFilter::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteAclsFilter::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resource_type_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(resource_name_filter_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(pattern_type_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(principal_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(principal_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(host_filter_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(host_filter_, dst);
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

uint32_t DeleteAclsFilter::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteAclsFilter::operator==(const DeleteAclsFilter& rhs) const {

  return true
  && resource_type_filter_ == rhs.resource_type_filter_
  && resource_name_filter_ == rhs.resource_name_filter_
  && pattern_type_filter_ == rhs.pattern_type_filter_
  && principal_filter_ == rhs.principal_filter_
  && host_filter_ == rhs.host_filter_
  && operation_ == rhs.operation_
  && permission_type_ == rhs.permission_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteAclsRequest::DeleteAclsRequest(std::vector<DeleteAclsFilter> filters): filters_{filters}, tagged_fields_{TaggedFields({})} {};
DeleteAclsRequest::DeleteAclsRequest(std::vector<DeleteAclsFilter> filters, TaggedFields tagged_fields): filters_{filters}, tagged_fields_{tagged_fields} {};


uint32_t DeleteAclsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(filters_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(filters_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteAclsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteAclsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(filters_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(filters_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteAclsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteAclsRequest::operator==(const DeleteAclsRequest& rhs) const {

  return true
  && filters_ == rhs.filters_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsResource::DescribeConfigsResource(int8_t resource_type, std::string resource_name, absl::optional<std::vector<std::string>> configuration_keys): resource_type_{resource_type}, resource_name_{resource_name}, configuration_keys_{configuration_keys}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsResource::DescribeConfigsResource(int8_t resource_type, std::string resource_name, absl::optional<std::vector<std::string>> configuration_keys, TaggedFields tagged_fields): resource_type_{resource_type}, resource_name_{resource_name}, configuration_keys_{configuration_keys}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsResource::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
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
    written += encoder.computeSize(configuration_keys_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(configuration_keys_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsResource::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsResource::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
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
    written += encoder.encode(configuration_keys_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(configuration_keys_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsResource::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsResource::operator==(const DescribeConfigsResource& rhs) const {

  return true
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && configuration_keys_ == rhs.configuration_keys_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeConfigsRequest::DescribeConfigsRequest(std::vector<DescribeConfigsResource> resources): resources_{resources}, include_synonyms_{false}, include_documentation_{false}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsRequest::DescribeConfigsRequest(std::vector<DescribeConfigsResource> resources, bool include_synonyms): resources_{resources}, include_synonyms_{include_synonyms}, include_documentation_{false}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsRequest::DescribeConfigsRequest(std::vector<DescribeConfigsResource> resources, bool include_synonyms, bool include_documentation): resources_{resources}, include_synonyms_{include_synonyms}, include_documentation_{include_documentation}, tagged_fields_{TaggedFields({})} {};
DescribeConfigsRequest::DescribeConfigsRequest(std::vector<DescribeConfigsResource> resources, bool include_synonyms, bool include_documentation, TaggedFields tagged_fields): resources_{resources}, include_synonyms_{include_synonyms}, include_documentation_{include_documentation}, tagged_fields_{tagged_fields} {};


uint32_t DescribeConfigsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(resources_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(resources_);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.computeSize(include_synonyms_);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.computeSize(include_documentation_);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeConfigsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeConfigsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(resources_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(resources_, dst);
  }
  
  if (api_version >= 1 && api_version < 5) {
    written += encoder.encode(include_synonyms_, dst);
  }
  
  if (api_version >= 3 && api_version < 5) {
    written += encoder.encode(include_documentation_, dst);
  }
  
  if (api_version >= 4 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeConfigsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeConfigsRequest::operator==(const DescribeConfigsRequest& rhs) const {

  return true
  && resources_ == rhs.resources_
  && include_synonyms_ == rhs.include_synonyms_
  && include_documentation_ == rhs.include_documentation_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterableConfig::AlterableConfig(std::string name, absl::optional<std::string> value): name_{name}, value_{value}, tagged_fields_{TaggedFields({})} {};
AlterableConfig::AlterableConfig(std::string name, absl::optional<std::string> value, TaggedFields tagged_fields): name_{name}, value_{value}, tagged_fields_{tagged_fields} {};


uint32_t AlterableConfig::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterableConfig::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterableConfig::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterableConfig::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterableConfig::operator==(const AlterableConfig& rhs) const {

  return true
  && name_ == rhs.name_
  && value_ == rhs.value_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterConfigsResource::AlterConfigsResource(int8_t resource_type, std::string resource_name, std::vector<AlterableConfig> configs): resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{TaggedFields({})} {};
AlterConfigsResource::AlterConfigsResource(int8_t resource_type, std::string resource_name, std::vector<AlterableConfig> configs, TaggedFields tagged_fields): resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{tagged_fields} {};


uint32_t AlterConfigsResource::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(configs_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(configs_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterConfigsResource::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterConfigsResource::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(configs_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(configs_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterConfigsResource::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterConfigsResource::operator==(const AlterConfigsResource& rhs) const {

  return true
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && configs_ == rhs.configs_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterConfigsRequest::AlterConfigsRequest(std::vector<AlterConfigsResource> resources, bool validate_only): resources_{resources}, validate_only_{validate_only}, tagged_fields_{TaggedFields({})} {};
AlterConfigsRequest::AlterConfigsRequest(std::vector<AlterConfigsResource> resources, bool validate_only, TaggedFields tagged_fields): resources_{resources}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t AlterConfigsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resources_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(resources_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterConfigsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterConfigsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resources_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(resources_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterConfigsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterConfigsRequest::operator==(const AlterConfigsRequest& rhs) const {

  return true
  && resources_ == rhs.resources_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDirTopic::AlterReplicaLogDirTopic(std::string name, std::vector<int32_t> partitions): name_{name}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDirTopic::AlterReplicaLogDirTopic(std::string name, std::vector<int32_t> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDirTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t AlterReplicaLogDirTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDirTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t AlterReplicaLogDirTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDirTopic::operator==(const AlterReplicaLogDirTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDir::AlterReplicaLogDir(std::string path, std::vector<AlterReplicaLogDirTopic> topics): path_{path}, topics_{topics}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDir::AlterReplicaLogDir(std::string path, std::vector<AlterReplicaLogDirTopic> topics, TaggedFields tagged_fields): path_{path}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDir::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(path_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(path_);
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

uint32_t AlterReplicaLogDir::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDir::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(path_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(path_, dst);
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

uint32_t AlterReplicaLogDir::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDir::operator==(const AlterReplicaLogDir& rhs) const {

  return true
  && path_ == rhs.path_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterReplicaLogDirsRequest::AlterReplicaLogDirsRequest(std::vector<AlterReplicaLogDir> dirs): dirs_{dirs}, tagged_fields_{TaggedFields({})} {};
AlterReplicaLogDirsRequest::AlterReplicaLogDirsRequest(std::vector<AlterReplicaLogDir> dirs, TaggedFields tagged_fields): dirs_{dirs}, tagged_fields_{tagged_fields} {};


uint32_t AlterReplicaLogDirsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(dirs_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(dirs_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterReplicaLogDirsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(dirs_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(dirs_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterReplicaLogDirsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterReplicaLogDirsRequest::operator==(const AlterReplicaLogDirsRequest& rhs) const {

  return true
  && dirs_ == rhs.dirs_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribableLogDirTopic::DescribableLogDirTopic(std::string topic, std::vector<int32_t> partitions): topic_{topic}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
DescribableLogDirTopic::DescribableLogDirTopic(std::string topic, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_{topic}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DescribableLogDirTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(topic_);
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

uint32_t DescribableLogDirTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribableLogDirTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(topic_, dst);
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

uint32_t DescribableLogDirTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribableLogDirTopic::operator==(const DescribableLogDirTopic& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeLogDirsRequest::DescribeLogDirsRequest(absl::optional<std::vector<DescribableLogDirTopic>> topics): topics_{topics}, tagged_fields_{TaggedFields({})} {};
DescribeLogDirsRequest::DescribeLogDirsRequest(absl::optional<std::vector<DescribableLogDirTopic>> topics, TaggedFields tagged_fields): topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DescribeLogDirsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeLogDirsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeLogDirsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 5) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeLogDirsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeLogDirsRequest::operator==(const DescribeLogDirsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


SaslAuthenticateRequest::SaslAuthenticateRequest(Bytes auth_bytes): auth_bytes_{auth_bytes}, tagged_fields_{TaggedFields({})} {};
SaslAuthenticateRequest::SaslAuthenticateRequest(Bytes auth_bytes, TaggedFields tagged_fields): auth_bytes_{auth_bytes}, tagged_fields_{tagged_fields} {};


uint32_t SaslAuthenticateRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(auth_bytes_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(auth_bytes_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t SaslAuthenticateRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t SaslAuthenticateRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(auth_bytes_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(auth_bytes_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t SaslAuthenticateRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool SaslAuthenticateRequest::operator==(const SaslAuthenticateRequest& rhs) const {

  return true
  && auth_bytes_ == rhs.auth_bytes_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatePartitionsAssignment::CreatePartitionsAssignment(std::vector<int32_t> broker_ids): broker_ids_{broker_ids}, tagged_fields_{TaggedFields({})} {};
CreatePartitionsAssignment::CreatePartitionsAssignment(std::vector<int32_t> broker_ids, TaggedFields tagged_fields): broker_ids_{broker_ids}, tagged_fields_{tagged_fields} {};


uint32_t CreatePartitionsAssignment::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(broker_ids_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(broker_ids_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatePartitionsAssignment::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatePartitionsAssignment::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(broker_ids_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(broker_ids_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatePartitionsAssignment::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatePartitionsAssignment::operator==(const CreatePartitionsAssignment& rhs) const {

  return true
  && broker_ids_ == rhs.broker_ids_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatePartitionsTopic::CreatePartitionsTopic(std::string name, int32_t count, absl::optional<std::vector<CreatePartitionsAssignment>> assignments): name_{name}, count_{count}, assignments_{assignments}, tagged_fields_{TaggedFields({})} {};
CreatePartitionsTopic::CreatePartitionsTopic(std::string name, int32_t count, absl::optional<std::vector<CreatePartitionsAssignment>> assignments, TaggedFields tagged_fields): name_{name}, count_{count}, assignments_{assignments}, tagged_fields_{tagged_fields} {};


uint32_t CreatePartitionsTopic::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(count_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(assignments_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(assignments_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatePartitionsTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatePartitionsTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(count_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(assignments_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(assignments_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatePartitionsTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatePartitionsTopic::operator==(const CreatePartitionsTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && count_ == rhs.count_
  && assignments_ == rhs.assignments_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatePartitionsRequest::CreatePartitionsRequest(std::vector<CreatePartitionsTopic> topics, int32_t timeout_ms, bool validate_only): topics_{topics}, timeout_ms_{timeout_ms}, validate_only_{validate_only}, tagged_fields_{TaggedFields({})} {};
CreatePartitionsRequest::CreatePartitionsRequest(std::vector<CreatePartitionsTopic> topics, int32_t timeout_ms, bool validate_only, TaggedFields tagged_fields): topics_{topics}, timeout_ms_{timeout_ms}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t CreatePartitionsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topics_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreatePartitionsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatePartitionsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topics_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreatePartitionsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatePartitionsRequest::operator==(const CreatePartitionsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && timeout_ms_ == rhs.timeout_ms_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreatableRenewers::CreatableRenewers(std::string principal_type, std::string principal_name): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{TaggedFields({})} {};
CreatableRenewers::CreatableRenewers(std::string principal_type, std::string principal_name, TaggedFields tagged_fields): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{tagged_fields} {};


uint32_t CreatableRenewers::computeSize(const EncodingContext& encoder) const {
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

uint32_t CreatableRenewers::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreatableRenewers::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t CreatableRenewers::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreatableRenewers::operator==(const CreatableRenewers& rhs) const {

  return true
  && principal_type_ == rhs.principal_type_
  && principal_name_ == rhs.principal_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


CreateDelegationTokenRequest::CreateDelegationTokenRequest(std::vector<CreatableRenewers> renewers, int64_t max_lifetime_ms): owner_principal_type_{{""}}, owner_principal_name_{{""}}, renewers_{renewers}, max_lifetime_ms_{max_lifetime_ms}, tagged_fields_{TaggedFields({})} {};
CreateDelegationTokenRequest::CreateDelegationTokenRequest(std::vector<CreatableRenewers> renewers, int64_t max_lifetime_ms, TaggedFields tagged_fields): owner_principal_type_{{""}}, owner_principal_name_{{""}}, renewers_{renewers}, max_lifetime_ms_{max_lifetime_ms}, tagged_fields_{tagged_fields} {};
CreateDelegationTokenRequest::CreateDelegationTokenRequest(absl::optional<std::string> owner_principal_type, absl::optional<std::string> owner_principal_name, std::vector<CreatableRenewers> renewers, int64_t max_lifetime_ms, TaggedFields tagged_fields): owner_principal_type_{owner_principal_type}, owner_principal_name_{owner_principal_name}, renewers_{renewers}, max_lifetime_ms_{max_lifetime_ms}, tagged_fields_{tagged_fields} {};


uint32_t CreateDelegationTokenRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(owner_principal_type_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(owner_principal_name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(renewers_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(renewers_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(max_lifetime_ms_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t CreateDelegationTokenRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t CreateDelegationTokenRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(owner_principal_type_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(owner_principal_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(renewers_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(renewers_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(max_lifetime_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t CreateDelegationTokenRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool CreateDelegationTokenRequest::operator==(const CreateDelegationTokenRequest& rhs) const {

  return true
  && owner_principal_type_ == rhs.owner_principal_type_
  && owner_principal_name_ == rhs.owner_principal_name_
  && renewers_ == rhs.renewers_
  && max_lifetime_ms_ == rhs.max_lifetime_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


RenewDelegationTokenRequest::RenewDelegationTokenRequest(Bytes hmac, int64_t renew_period_ms): hmac_{hmac}, renew_period_ms_{renew_period_ms}, tagged_fields_{TaggedFields({})} {};
RenewDelegationTokenRequest::RenewDelegationTokenRequest(Bytes hmac, int64_t renew_period_ms, TaggedFields tagged_fields): hmac_{hmac}, renew_period_ms_{renew_period_ms}, tagged_fields_{tagged_fields} {};


uint32_t RenewDelegationTokenRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(hmac_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(hmac_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(renew_period_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t RenewDelegationTokenRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RenewDelegationTokenRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(hmac_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(hmac_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(renew_period_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t RenewDelegationTokenRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RenewDelegationTokenRequest::operator==(const RenewDelegationTokenRequest& rhs) const {

  return true
  && hmac_ == rhs.hmac_
  && renew_period_ms_ == rhs.renew_period_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


ExpireDelegationTokenRequest::ExpireDelegationTokenRequest(Bytes hmac, int64_t expiry_time_period_ms): hmac_{hmac}, expiry_time_period_ms_{expiry_time_period_ms}, tagged_fields_{TaggedFields({})} {};
ExpireDelegationTokenRequest::ExpireDelegationTokenRequest(Bytes hmac, int64_t expiry_time_period_ms, TaggedFields tagged_fields): hmac_{hmac}, expiry_time_period_ms_{expiry_time_period_ms}, tagged_fields_{tagged_fields} {};


uint32_t ExpireDelegationTokenRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(hmac_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(hmac_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(expiry_time_period_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ExpireDelegationTokenRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ExpireDelegationTokenRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(hmac_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(hmac_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(expiry_time_period_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ExpireDelegationTokenRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ExpireDelegationTokenRequest::operator==(const ExpireDelegationTokenRequest& rhs) const {

  return true
  && hmac_ == rhs.hmac_
  && expiry_time_period_ms_ == rhs.expiry_time_period_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeDelegationTokenOwner::DescribeDelegationTokenOwner(std::string principal_type, std::string principal_name): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{TaggedFields({})} {};
DescribeDelegationTokenOwner::DescribeDelegationTokenOwner(std::string principal_type, std::string principal_name, TaggedFields tagged_fields): principal_type_{principal_type}, principal_name_{principal_name}, tagged_fields_{tagged_fields} {};


uint32_t DescribeDelegationTokenOwner::computeSize(const EncodingContext& encoder) const {
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

uint32_t DescribeDelegationTokenOwner::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeDelegationTokenOwner::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t DescribeDelegationTokenOwner::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeDelegationTokenOwner::operator==(const DescribeDelegationTokenOwner& rhs) const {

  return true
  && principal_type_ == rhs.principal_type_
  && principal_name_ == rhs.principal_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeDelegationTokenRequest::DescribeDelegationTokenRequest(absl::optional<std::vector<DescribeDelegationTokenOwner>> owners): owners_{owners}, tagged_fields_{TaggedFields({})} {};
DescribeDelegationTokenRequest::DescribeDelegationTokenRequest(absl::optional<std::vector<DescribeDelegationTokenOwner>> owners, TaggedFields tagged_fields): owners_{owners}, tagged_fields_{tagged_fields} {};


uint32_t DescribeDelegationTokenRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(owners_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(owners_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeDelegationTokenRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeDelegationTokenRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(owners_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(owners_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeDelegationTokenRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeDelegationTokenRequest::operator==(const DescribeDelegationTokenRequest& rhs) const {

  return true
  && owners_ == rhs.owners_
  && tagged_fields_ == rhs.tagged_fields_;
};


DeleteGroupsRequest::DeleteGroupsRequest(std::vector<std::string> groups_names): groups_names_{groups_names}, tagged_fields_{TaggedFields({})} {};
DeleteGroupsRequest::DeleteGroupsRequest(std::vector<std::string> groups_names, TaggedFields tagged_fields): groups_names_{groups_names}, tagged_fields_{tagged_fields} {};


uint32_t DeleteGroupsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(groups_names_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(groups_names_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DeleteGroupsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DeleteGroupsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(groups_names_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(groups_names_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DeleteGroupsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DeleteGroupsRequest::operator==(const DeleteGroupsRequest& rhs) const {

  return true
  && groups_names_ == rhs.groups_names_
  && tagged_fields_ == rhs.tagged_fields_;
};


ElectLeadersRequestRequestTopicPartitions::ElectLeadersRequestRequestTopicPartitions(std::string topic, std::vector<int32_t> partitions): topic_{topic}, partitions_{partitions}, tagged_fields_{TaggedFields({})} {};
ElectLeadersRequestRequestTopicPartitions::ElectLeadersRequestRequestTopicPartitions(std::string topic, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_{topic}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ElectLeadersRequestRequestTopicPartitions::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topic_);
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

uint32_t ElectLeadersRequestRequestTopicPartitions::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ElectLeadersRequestRequestTopicPartitions::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topic_, dst);
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

uint32_t ElectLeadersRequestRequestTopicPartitions::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ElectLeadersRequestRequestTopicPartitions::operator==(const ElectLeadersRequestRequestTopicPartitions& rhs) const {

  return true
  && topic_ == rhs.topic_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ElectLeadersRequest::ElectLeadersRequest(absl::optional<std::vector<ElectLeadersRequestRequestTopicPartitions>> topic_partitions, int32_t timeout_ms): election_type_{0}, topic_partitions_{topic_partitions}, timeout_ms_{timeout_ms}, tagged_fields_{TaggedFields({})} {};
ElectLeadersRequest::ElectLeadersRequest(int8_t election_type, absl::optional<std::vector<ElectLeadersRequestRequestTopicPartitions>> topic_partitions, int32_t timeout_ms): election_type_{election_type}, topic_partitions_{topic_partitions}, timeout_ms_{timeout_ms}, tagged_fields_{TaggedFields({})} {};
ElectLeadersRequest::ElectLeadersRequest(int8_t election_type, absl::optional<std::vector<ElectLeadersRequestRequestTopicPartitions>> topic_partitions, int32_t timeout_ms, TaggedFields tagged_fields): election_type_{election_type}, topic_partitions_{topic_partitions}, timeout_ms_{timeout_ms}, tagged_fields_{tagged_fields} {};


uint32_t ElectLeadersRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.computeSize(election_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(topic_partitions_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(topic_partitions_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ElectLeadersRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ElectLeadersRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 1 && api_version < 3) {
    written += encoder.encode(election_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(topic_partitions_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(topic_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 2 && api_version < 3) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ElectLeadersRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ElectLeadersRequest::operator==(const ElectLeadersRequest& rhs) const {

  return true
  && election_type_ == rhs.election_type_
  && topic_partitions_ == rhs.topic_partitions_
  && timeout_ms_ == rhs.timeout_ms_
  && tagged_fields_ == rhs.tagged_fields_;
};


IncrementalAlterConfigsRequestAlterableConfig::IncrementalAlterConfigsRequestAlterableConfig(std::string name, int8_t config_operation, absl::optional<std::string> value): name_{name}, config_operation_{config_operation}, value_{value}, tagged_fields_{TaggedFields({})} {};
IncrementalAlterConfigsRequestAlterableConfig::IncrementalAlterConfigsRequestAlterableConfig(std::string name, int8_t config_operation, absl::optional<std::string> value, TaggedFields tagged_fields): name_{name}, config_operation_{config_operation}, value_{value}, tagged_fields_{tagged_fields} {};


uint32_t IncrementalAlterConfigsRequestAlterableConfig::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(config_operation_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(value_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(value_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequestAlterableConfig::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t IncrementalAlterConfigsRequestAlterableConfig::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(config_operation_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(value_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(value_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequestAlterableConfig::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool IncrementalAlterConfigsRequestAlterableConfig::operator==(const IncrementalAlterConfigsRequestAlterableConfig& rhs) const {

  return true
  && name_ == rhs.name_
  && config_operation_ == rhs.config_operation_
  && value_ == rhs.value_
  && tagged_fields_ == rhs.tagged_fields_;
};


IncrementalAlterConfigsRequestAlterConfigsResource::IncrementalAlterConfigsRequestAlterConfigsResource(int8_t resource_type, std::string resource_name, std::vector<IncrementalAlterConfigsRequestAlterableConfig> configs): resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{TaggedFields({})} {};
IncrementalAlterConfigsRequestAlterConfigsResource::IncrementalAlterConfigsRequestAlterConfigsResource(int8_t resource_type, std::string resource_name, std::vector<IncrementalAlterConfigsRequestAlterableConfig> configs, TaggedFields tagged_fields): resource_type_{resource_type}, resource_name_{resource_name}, configs_{configs}, tagged_fields_{tagged_fields} {};


uint32_t IncrementalAlterConfigsRequestAlterConfigsResource::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(resource_type_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(resource_name_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(resource_name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(configs_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(configs_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequestAlterConfigsResource::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t IncrementalAlterConfigsRequestAlterConfigsResource::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(resource_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(resource_name_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(resource_name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(configs_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(configs_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequestAlterConfigsResource::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool IncrementalAlterConfigsRequestAlterConfigsResource::operator==(const IncrementalAlterConfigsRequestAlterConfigsResource& rhs) const {

  return true
  && resource_type_ == rhs.resource_type_
  && resource_name_ == rhs.resource_name_
  && configs_ == rhs.configs_
  && tagged_fields_ == rhs.tagged_fields_;
};


IncrementalAlterConfigsRequest::IncrementalAlterConfigsRequest(std::vector<IncrementalAlterConfigsRequestAlterConfigsResource> resources, bool validate_only): resources_{resources}, validate_only_{validate_only}, tagged_fields_{TaggedFields({})} {};
IncrementalAlterConfigsRequest::IncrementalAlterConfigsRequest(std::vector<IncrementalAlterConfigsRequestAlterConfigsResource> resources, bool validate_only, TaggedFields tagged_fields): resources_{resources}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t IncrementalAlterConfigsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(resources_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(resources_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t IncrementalAlterConfigsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(resources_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(resources_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t IncrementalAlterConfigsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool IncrementalAlterConfigsRequest::operator==(const IncrementalAlterConfigsRequest& rhs) const {

  return true
  && resources_ == rhs.resources_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


ReassignablePartition::ReassignablePartition(int32_t partition_index, absl::optional<std::vector<int32_t>> replicas, TaggedFields tagged_fields): partition_index_{partition_index}, replicas_{replicas}, tagged_fields_{tagged_fields} {};


uint32_t ReassignablePartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(replicas_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ReassignablePartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReassignablePartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(replicas_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ReassignablePartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReassignablePartition::operator==(const ReassignablePartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && replicas_ == rhs.replicas_
  && tagged_fields_ == rhs.tagged_fields_;
};


ReassignableTopic::ReassignableTopic(std::string name, std::vector<ReassignablePartition> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t ReassignableTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t ReassignableTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ReassignableTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t ReassignableTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ReassignableTopic::operator==(const ReassignableTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterPartitionReassignmentsRequest::AlterPartitionReassignmentsRequest(int32_t timeout_ms, std::vector<ReassignableTopic> topics, TaggedFields tagged_fields): timeout_ms_{timeout_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t AlterPartitionReassignmentsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterPartitionReassignmentsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterPartitionReassignmentsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterPartitionReassignmentsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterPartitionReassignmentsRequest::operator==(const AlterPartitionReassignmentsRequest& rhs) const {

  return true
  && timeout_ms_ == rhs.timeout_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListPartitionReassignmentsTopics::ListPartitionReassignmentsTopics(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t ListPartitionReassignmentsTopics::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsTopics::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListPartitionReassignmentsTopics::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsTopics::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListPartitionReassignmentsTopics::operator==(const ListPartitionReassignmentsTopics& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListPartitionReassignmentsRequest::ListPartitionReassignmentsRequest(int32_t timeout_ms, absl::optional<std::vector<ListPartitionReassignmentsTopics>> topics, TaggedFields tagged_fields): timeout_ms_{timeout_ms}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t ListPartitionReassignmentsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListPartitionReassignmentsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListPartitionReassignmentsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListPartitionReassignmentsRequest::operator==(const ListPartitionReassignmentsRequest& rhs) const {

  return true
  && timeout_ms_ == rhs.timeout_ms_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


OffsetDeleteRequestPartition::OffsetDeleteRequestPartition(int32_t partition_index): partition_index_{partition_index} {};


uint32_t OffsetDeleteRequestPartition::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  

  return written;
}

uint32_t OffsetDeleteRequestPartition::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteRequestPartition::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  

  return written;
}

uint32_t OffsetDeleteRequestPartition::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteRequestPartition::operator==(const OffsetDeleteRequestPartition& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_;
};


OffsetDeleteRequestTopic::OffsetDeleteRequestTopic(std::string name, std::vector<OffsetDeleteRequestPartition> partitions): name_{name}, partitions_{partitions} {};


uint32_t OffsetDeleteRequestTopic::computeSize(const EncodingContext& encoder) const {
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

uint32_t OffsetDeleteRequestTopic::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteRequestTopic::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t OffsetDeleteRequestTopic::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteRequestTopic::operator==(const OffsetDeleteRequestTopic& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_;
};


OffsetDeleteRequest::OffsetDeleteRequest(std::string group_id, std::vector<OffsetDeleteRequestTopic> topics): group_id_{group_id}, topics_{topics} {};


uint32_t OffsetDeleteRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t OffsetDeleteRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OffsetDeleteRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t OffsetDeleteRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OffsetDeleteRequest::operator==(const OffsetDeleteRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && topics_ == rhs.topics_;
};


ComponentData::ComponentData(std::string entity_type, int8_t match_type, absl::optional<std::string> match): entity_type_{entity_type}, match_type_{match_type}, match_{match}, tagged_fields_{TaggedFields({})} {};
ComponentData::ComponentData(std::string entity_type, int8_t match_type, absl::optional<std::string> match, TaggedFields tagged_fields): entity_type_{entity_type}, match_type_{match_type}, match_{match}, tagged_fields_{tagged_fields} {};


uint32_t ComponentData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_type_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(match_type_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(match_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(match_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ComponentData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ComponentData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_type_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(match_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(match_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(match_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ComponentData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ComponentData::operator==(const ComponentData& rhs) const {

  return true
  && entity_type_ == rhs.entity_type_
  && match_type_ == rhs.match_type_
  && match_ == rhs.match_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClientQuotasRequest::DescribeClientQuotasRequest(std::vector<ComponentData> components, bool strict): components_{components}, strict_{strict}, tagged_fields_{TaggedFields({})} {};
DescribeClientQuotasRequest::DescribeClientQuotasRequest(std::vector<ComponentData> components, bool strict, TaggedFields tagged_fields): components_{components}, strict_{strict}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClientQuotasRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(components_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(components_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(strict_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClientQuotasRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClientQuotasRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(components_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(components_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(strict_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClientQuotasRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClientQuotasRequest::operator==(const DescribeClientQuotasRequest& rhs) const {

  return true
  && components_ == rhs.components_
  && strict_ == rhs.strict_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestEntityData::RequestEntityData(std::string entity_type, absl::optional<std::string> entity_name): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{TaggedFields({})} {};
RequestEntityData::RequestEntityData(std::string entity_type, absl::optional<std::string> entity_name, TaggedFields tagged_fields): entity_type_{entity_type}, entity_name_{entity_name}, tagged_fields_{tagged_fields} {};


uint32_t RequestEntityData::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestEntityData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestEntityData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestEntityData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestEntityData::operator==(const RequestEntityData& rhs) const {

  return true
  && entity_type_ == rhs.entity_type_
  && entity_name_ == rhs.entity_name_
  && tagged_fields_ == rhs.tagged_fields_;
};


OpData::OpData(std::string key, double value, bool remove): key_{key}, value_{value}, remove_{remove}, tagged_fields_{TaggedFields({})} {};
OpData::OpData(std::string key, double value, bool remove, TaggedFields tagged_fields): key_{key}, value_{value}, remove_{remove}, tagged_fields_{tagged_fields} {};


uint32_t OpData::computeSize(const EncodingContext& encoder) const {
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
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(remove_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t OpData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t OpData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(remove_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t OpData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool OpData::operator==(const OpData& rhs) const {

  return true
  && key_ == rhs.key_
  && value_ == rhs.value_
  && remove_ == rhs.remove_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestEntryData::RequestEntryData(std::vector<RequestEntityData> entity, std::vector<OpData> ops): entity_{entity}, ops_{ops}, tagged_fields_{TaggedFields({})} {};
RequestEntryData::RequestEntryData(std::vector<RequestEntityData> entity, std::vector<OpData> ops, TaggedFields tagged_fields): entity_{entity}, ops_{ops}, tagged_fields_{tagged_fields} {};


uint32_t RequestEntryData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entity_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entity_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(ops_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(ops_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t RequestEntryData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestEntryData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entity_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entity_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(ops_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(ops_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t RequestEntryData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestEntryData::operator==(const RequestEntryData& rhs) const {

  return true
  && entity_ == rhs.entity_
  && ops_ == rhs.ops_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterClientQuotasRequest::AlterClientQuotasRequest(std::vector<RequestEntryData> entries, bool validate_only): entries_{entries}, validate_only_{validate_only}, tagged_fields_{TaggedFields({})} {};
AlterClientQuotasRequest::AlterClientQuotasRequest(std::vector<RequestEntryData> entries, bool validate_only, TaggedFields tagged_fields): entries_{entries}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t AlterClientQuotasRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(entries_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(entries_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterClientQuotasRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterClientQuotasRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(entries_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(entries_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterClientQuotasRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterClientQuotasRequest::operator==(const AlterClientQuotasRequest& rhs) const {

  return true
  && entries_ == rhs.entries_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


UserName::UserName(std::string name, TaggedFields tagged_fields): name_{name}, tagged_fields_{tagged_fields} {};


uint32_t UserName::computeSize(const EncodingContext& encoder) const {
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

uint32_t UserName::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UserName::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t UserName::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UserName::operator==(const UserName& rhs) const {

  return true
  && name_ == rhs.name_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeUserScramCredentialsRequest::DescribeUserScramCredentialsRequest(absl::optional<std::vector<UserName>> users, TaggedFields tagged_fields): users_{users}, tagged_fields_{tagged_fields} {};


uint32_t DescribeUserScramCredentialsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(users_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeUserScramCredentialsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(users_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeUserScramCredentialsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeUserScramCredentialsRequest::operator==(const DescribeUserScramCredentialsRequest& rhs) const {

  return true
  && users_ == rhs.users_
  && tagged_fields_ == rhs.tagged_fields_;
};


ScramCredentialDeletion::ScramCredentialDeletion(std::string name, int8_t mechanism, TaggedFields tagged_fields): name_{name}, mechanism_{mechanism}, tagged_fields_{tagged_fields} {};


uint32_t ScramCredentialDeletion::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(mechanism_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ScramCredentialDeletion::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ScramCredentialDeletion::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(mechanism_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ScramCredentialDeletion::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ScramCredentialDeletion::operator==(const ScramCredentialDeletion& rhs) const {

  return true
  && name_ == rhs.name_
  && mechanism_ == rhs.mechanism_
  && tagged_fields_ == rhs.tagged_fields_;
};


ScramCredentialUpsertion::ScramCredentialUpsertion(std::string name, int8_t mechanism, int32_t iterations, Bytes salt, Bytes salted_password, TaggedFields tagged_fields): name_{name}, mechanism_{mechanism}, iterations_{iterations}, salt_{salt}, salted_password_{salted_password}, tagged_fields_{tagged_fields} {};


uint32_t ScramCredentialUpsertion::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(mechanism_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(iterations_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(salt_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(salted_password_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ScramCredentialUpsertion::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ScramCredentialUpsertion::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(mechanism_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(iterations_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(salt_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(salted_password_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ScramCredentialUpsertion::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ScramCredentialUpsertion::operator==(const ScramCredentialUpsertion& rhs) const {

  return true
  && name_ == rhs.name_
  && mechanism_ == rhs.mechanism_
  && iterations_ == rhs.iterations_
  && salt_ == rhs.salt_
  && salted_password_ == rhs.salted_password_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterUserScramCredentialsRequest::AlterUserScramCredentialsRequest(std::vector<ScramCredentialDeletion> deletions, std::vector<ScramCredentialUpsertion> upsertions, TaggedFields tagged_fields): deletions_{deletions}, upsertions_{upsertions}, tagged_fields_{tagged_fields} {};


uint32_t AlterUserScramCredentialsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(deletions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(upsertions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterUserScramCredentialsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(deletions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(upsertions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterUserScramCredentialsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterUserScramCredentialsRequest::operator==(const AlterUserScramCredentialsRequest& rhs) const {

  return true
  && deletions_ == rhs.deletions_
  && upsertions_ == rhs.upsertions_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteRequestRequestPartitionData::VoteRequestRequestPartitionData(int32_t partition_index, int32_t candidate_epoch, int32_t candidate_id, int32_t last_offset_epoch, int64_t last_offset, TaggedFields tagged_fields): partition_index_{partition_index}, candidate_epoch_{candidate_epoch}, candidate_id_{candidate_id}, last_offset_epoch_{last_offset_epoch}, last_offset_{last_offset}, tagged_fields_{tagged_fields} {};


uint32_t VoteRequestRequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(candidate_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(candidate_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(last_offset_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(last_offset_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t VoteRequestRequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteRequestRequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(candidate_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(candidate_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(last_offset_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(last_offset_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t VoteRequestRequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteRequestRequestPartitionData::operator==(const VoteRequestRequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && candidate_epoch_ == rhs.candidate_epoch_
  && candidate_id_ == rhs.candidate_id_
  && last_offset_epoch_ == rhs.last_offset_epoch_
  && last_offset_ == rhs.last_offset_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteRequestRequestTopicData::VoteRequestRequestTopicData(std::string topic_name, std::vector<VoteRequestRequestPartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t VoteRequestRequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t VoteRequestRequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteRequestRequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t VoteRequestRequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteRequestRequestTopicData::operator==(const VoteRequestRequestTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


VoteRequest::VoteRequest(absl::optional<std::string> cluster_id, std::vector<VoteRequestRequestTopicData> topics, TaggedFields tagged_fields): cluster_id_{cluster_id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t VoteRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(cluster_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t VoteRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t VoteRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(cluster_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t VoteRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool VoteRequest::operator==(const VoteRequest& rhs) const {

  return true
  && cluster_id_ == rhs.cluster_id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


BeginQuorumEpochRequestRequestPartitionData::BeginQuorumEpochRequestRequestPartitionData(int32_t partition_index, int32_t leader_id, int32_t leader_epoch): partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{leader_epoch} {};


uint32_t BeginQuorumEpochRequestRequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(leader_epoch_);
  }
  

  return written;
}

uint32_t BeginQuorumEpochRequestRequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochRequestRequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(leader_epoch_, dst);
  }
  

  return written;
}

uint32_t BeginQuorumEpochRequestRequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochRequestRequestPartitionData::operator==(const BeginQuorumEpochRequestRequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_;
};


BeginQuorumEpochRequestRequestTopicData::BeginQuorumEpochRequestRequestTopicData(std::string topic_name, std::vector<BeginQuorumEpochRequestRequestPartitionData> partitions): topic_name_{topic_name}, partitions_{partitions} {};


uint32_t BeginQuorumEpochRequestRequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t BeginQuorumEpochRequestRequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochRequestRequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t BeginQuorumEpochRequestRequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochRequestRequestTopicData::operator==(const BeginQuorumEpochRequestRequestTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_;
};


BeginQuorumEpochRequest::BeginQuorumEpochRequest(absl::optional<std::string> cluster_id, std::vector<BeginQuorumEpochRequestRequestTopicData> topics): cluster_id_{cluster_id}, topics_{topics} {};


uint32_t BeginQuorumEpochRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(cluster_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t BeginQuorumEpochRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BeginQuorumEpochRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(cluster_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t BeginQuorumEpochRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BeginQuorumEpochRequest::operator==(const BeginQuorumEpochRequest& rhs) const {

  return true
  && cluster_id_ == rhs.cluster_id_
  && topics_ == rhs.topics_;
};


EndQuorumEpochRequestRequestPartitionData::EndQuorumEpochRequestRequestPartitionData(int32_t partition_index, int32_t leader_id, int32_t leader_epoch, std::vector<int32_t> preferred_successors): partition_index_{partition_index}, leader_id_{leader_id}, leader_epoch_{leader_epoch}, preferred_successors_{preferred_successors} {};


uint32_t EndQuorumEpochRequestRequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
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
    written += encoder.computeSize(preferred_successors_);
  }
  

  return written;
}

uint32_t EndQuorumEpochRequestRequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochRequestRequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
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
    written += encoder.encode(preferred_successors_, dst);
  }
  

  return written;
}

uint32_t EndQuorumEpochRequestRequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochRequestRequestPartitionData::operator==(const EndQuorumEpochRequestRequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && leader_id_ == rhs.leader_id_
  && leader_epoch_ == rhs.leader_epoch_
  && preferred_successors_ == rhs.preferred_successors_;
};


EndQuorumEpochRequestRequestTopicData::EndQuorumEpochRequestRequestTopicData(std::string topic_name, std::vector<EndQuorumEpochRequestRequestPartitionData> partitions): topic_name_{topic_name}, partitions_{partitions} {};


uint32_t EndQuorumEpochRequestRequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t EndQuorumEpochRequestRequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochRequestRequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t EndQuorumEpochRequestRequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochRequestRequestTopicData::operator==(const EndQuorumEpochRequestRequestTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_;
};


EndQuorumEpochRequest::EndQuorumEpochRequest(absl::optional<std::string> cluster_id, std::vector<EndQuorumEpochRequestRequestTopicData> topics): cluster_id_{cluster_id}, topics_{topics} {};


uint32_t EndQuorumEpochRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(cluster_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(topics_);
  }
  

  return written;
}

uint32_t EndQuorumEpochRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EndQuorumEpochRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(cluster_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(topics_, dst);
  }
  

  return written;
}

uint32_t EndQuorumEpochRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EndQuorumEpochRequest::operator==(const EndQuorumEpochRequest& rhs) const {

  return true
  && cluster_id_ == rhs.cluster_id_
  && topics_ == rhs.topics_;
};


DescribeQuorumRequestRequestPartitionData::DescribeQuorumRequestRequestPartitionData(int32_t partition_index, TaggedFields tagged_fields): partition_index_{partition_index}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumRequestRequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeQuorumRequestRequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumRequestRequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeQuorumRequestRequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumRequestRequestPartitionData::operator==(const DescribeQuorumRequestRequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeQuorumRequestRequestTopicData::DescribeQuorumRequestRequestTopicData(std::string topic_name, std::vector<DescribeQuorumRequestRequestPartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumRequestRequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t DescribeQuorumRequestRequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumRequestRequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t DescribeQuorumRequestRequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumRequestRequestTopicData::operator==(const DescribeQuorumRequestRequestTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeQuorumRequest::DescribeQuorumRequest(std::vector<DescribeQuorumRequestRequestTopicData> topics, TaggedFields tagged_fields): topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DescribeQuorumRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeQuorumRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeQuorumRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeQuorumRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeQuorumRequest::operator==(const DescribeQuorumRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


BrokerState::BrokerState(int32_t broker_id, int64_t broker_epoch, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, tagged_fields_{tagged_fields} {};


uint32_t BrokerState::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BrokerState::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BrokerState::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BrokerState::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BrokerState::operator==(const BrokerState& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestPartitionData::RequestPartitionData(int32_t partition_index, int32_t leader_epoch, std::vector<int32_t> new_isr, int32_t partition_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, leader_epoch_{leader_epoch}, new_isr_{new_isr}, new_isr_with_epochs_{std::vector<BrokerState>{}}, leader_recovery_state_{0}, partition_epoch_{partition_epoch}, tagged_fields_{tagged_fields} {};
RequestPartitionData::RequestPartitionData(int32_t partition_index, int32_t leader_epoch, std::vector<int32_t> new_isr, int8_t leader_recovery_state, int32_t partition_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, leader_epoch_{leader_epoch}, new_isr_{new_isr}, new_isr_with_epochs_{std::vector<BrokerState>{}}, leader_recovery_state_{leader_recovery_state}, partition_epoch_{partition_epoch}, tagged_fields_{tagged_fields} {};
RequestPartitionData::RequestPartitionData(int32_t partition_index, int32_t leader_epoch, std::vector<BrokerState> new_isr_with_epochs, int8_t leader_recovery_state, int32_t partition_epoch, TaggedFields tagged_fields): partition_index_{partition_index}, leader_epoch_{leader_epoch}, new_isr_{std::vector<int32_t>{}}, new_isr_with_epochs_{new_isr_with_epochs}, leader_recovery_state_{leader_recovery_state}, partition_epoch_{partition_epoch}, tagged_fields_{tagged_fields} {};


uint32_t RequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.computeCompactSize(new_isr_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeCompactSize(new_isr_with_epochs_);
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

uint32_t RequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 3) {
    written += encoder.encodeCompact(new_isr_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encodeCompact(new_isr_with_epochs_, dst);
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

uint32_t RequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestPartitionData::operator==(const RequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && leader_epoch_ == rhs.leader_epoch_
  && new_isr_ == rhs.new_isr_
  && new_isr_with_epochs_ == rhs.new_isr_with_epochs_
  && leader_recovery_state_ == rhs.leader_recovery_state_
  && partition_epoch_ == rhs.partition_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestTopicData::RequestTopicData(std::string topic_name, std::vector<RequestPartitionData> partitions, TaggedFields tagged_fields): topic_name_{topic_name}, topic_id_{Uuid{0, 0}}, partitions_{partitions}, tagged_fields_{tagged_fields} {};
RequestTopicData::RequestTopicData(Uuid topic_id, std::vector<RequestPartitionData> partitions, TaggedFields tagged_fields): topic_name_{""}, topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t RequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestTopicData::operator==(const RequestTopicData& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


AlterPartitionRequest::AlterPartitionRequest(int32_t broker_id, int64_t broker_epoch, std::vector<RequestTopicData> topics, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t AlterPartitionRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AlterPartitionRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AlterPartitionRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AlterPartitionRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AlterPartitionRequest::operator==(const AlterPartitionRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


FeatureUpdateKey::FeatureUpdateKey(std::string feature, int16_t max_version_level, bool allow_downgrade, TaggedFields tagged_fields): feature_{feature}, max_version_level_{max_version_level}, allow_downgrade_{allow_downgrade}, upgrade_type_{1}, tagged_fields_{tagged_fields} {};
FeatureUpdateKey::FeatureUpdateKey(std::string feature, int16_t max_version_level, int8_t upgrade_type, TaggedFields tagged_fields): feature_{feature}, max_version_level_{max_version_level}, allow_downgrade_{false}, upgrade_type_{upgrade_type}, tagged_fields_{tagged_fields} {};


uint32_t FeatureUpdateKey::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(feature_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(max_version_level_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(allow_downgrade_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(upgrade_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FeatureUpdateKey::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FeatureUpdateKey::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(feature_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(max_version_level_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(allow_downgrade_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(upgrade_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FeatureUpdateKey::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FeatureUpdateKey::operator==(const FeatureUpdateKey& rhs) const {

  return true
  && feature_ == rhs.feature_
  && max_version_level_ == rhs.max_version_level_
  && allow_downgrade_ == rhs.allow_downgrade_
  && upgrade_type_ == rhs.upgrade_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


UpdateFeaturesRequest::UpdateFeaturesRequest(int32_t timeout_ms, std::vector<FeatureUpdateKey> feature_updates, TaggedFields tagged_fields): timeout_ms_{timeout_ms}, feature_updates_{feature_updates}, validate_only_{false}, tagged_fields_{tagged_fields} {};
UpdateFeaturesRequest::UpdateFeaturesRequest(int32_t timeout_ms, std::vector<FeatureUpdateKey> feature_updates, bool validate_only, TaggedFields tagged_fields): timeout_ms_{timeout_ms}, feature_updates_{feature_updates}, validate_only_{validate_only}, tagged_fields_{tagged_fields} {};


uint32_t UpdateFeaturesRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(feature_updates_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(validate_only_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UpdateFeaturesRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UpdateFeaturesRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(feature_updates_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(validate_only_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UpdateFeaturesRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UpdateFeaturesRequest::operator==(const UpdateFeaturesRequest& rhs) const {

  return true
  && timeout_ms_ == rhs.timeout_ms_
  && feature_updates_ == rhs.feature_updates_
  && validate_only_ == rhs.validate_only_
  && tagged_fields_ == rhs.tagged_fields_;
};


EnvelopeRequest::EnvelopeRequest(Bytes request_data, absl::optional<Bytes> request_principal, Bytes client_host_address, TaggedFields tagged_fields): request_data_{request_data}, request_principal_{request_principal}, client_host_address_{client_host_address}, tagged_fields_{tagged_fields} {};


uint32_t EnvelopeRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(request_data_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(request_principal_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(client_host_address_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t EnvelopeRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t EnvelopeRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(request_data_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(request_principal_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(client_host_address_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t EnvelopeRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool EnvelopeRequest::operator==(const EnvelopeRequest& rhs) const {

  return true
  && request_data_ == rhs.request_data_
  && request_principal_ == rhs.request_principal_
  && client_host_address_ == rhs.client_host_address_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestSnapshotId::RequestSnapshotId(int64_t end_offset, int32_t epoch, TaggedFields tagged_fields): end_offset_{end_offset}, epoch_{epoch}, tagged_fields_{tagged_fields} {};


uint32_t RequestSnapshotId::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestSnapshotId::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestSnapshotId::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestSnapshotId::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestSnapshotId::operator==(const RequestSnapshotId& rhs) const {

  return true
  && end_offset_ == rhs.end_offset_
  && epoch_ == rhs.epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestPartitionSnapshot::RequestPartitionSnapshot(int32_t partition, int32_t current_leader_epoch, RequestSnapshotId snapshot_id, int64_t position, TaggedFields tagged_fields): partition_{partition}, current_leader_epoch_{current_leader_epoch}, snapshot_id_{snapshot_id}, position_{position}, tagged_fields_{tagged_fields} {};


uint32_t RequestPartitionSnapshot::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(current_leader_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(snapshot_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(position_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t RequestPartitionSnapshot::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestPartitionSnapshot::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(current_leader_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(snapshot_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(position_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t RequestPartitionSnapshot::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestPartitionSnapshot::operator==(const RequestPartitionSnapshot& rhs) const {

  return true
  && partition_ == rhs.partition_
  && current_leader_epoch_ == rhs.current_leader_epoch_
  && snapshot_id_ == rhs.snapshot_id_
  && position_ == rhs.position_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestTopicSnapshot::RequestTopicSnapshot(std::string name, std::vector<RequestPartitionSnapshot> partitions, TaggedFields tagged_fields): name_{name}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t RequestTopicSnapshot::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestTopicSnapshot::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestTopicSnapshot::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestTopicSnapshot::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestTopicSnapshot::operator==(const RequestTopicSnapshot& rhs) const {

  return true
  && name_ == rhs.name_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


FetchSnapshotRequest::FetchSnapshotRequest(int32_t replica_id, int32_t max_bytes, std::vector<RequestTopicSnapshot> topics, TaggedFields tagged_fields): replica_id_{replica_id}, max_bytes_{max_bytes}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t FetchSnapshotRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(replica_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(max_bytes_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t FetchSnapshotRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t FetchSnapshotRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(replica_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(max_bytes_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t FetchSnapshotRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool FetchSnapshotRequest::operator==(const FetchSnapshotRequest& rhs) const {

  return true
  && replica_id_ == rhs.replica_id_
  && max_bytes_ == rhs.max_bytes_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeClusterRequest::DescribeClusterRequest(bool include_cluster_authorized_operations, TaggedFields tagged_fields): include_cluster_authorized_operations_{include_cluster_authorized_operations}, endpoint_type_{1}, tagged_fields_{tagged_fields} {};
DescribeClusterRequest::DescribeClusterRequest(bool include_cluster_authorized_operations, int8_t endpoint_type, TaggedFields tagged_fields): include_cluster_authorized_operations_{include_cluster_authorized_operations}, endpoint_type_{endpoint_type}, tagged_fields_{tagged_fields} {};


uint32_t DescribeClusterRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(include_cluster_authorized_operations_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(endpoint_type_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeClusterRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeClusterRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(include_cluster_authorized_operations_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(endpoint_type_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeClusterRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeClusterRequest::operator==(const DescribeClusterRequest& rhs) const {

  return true
  && include_cluster_authorized_operations_ == rhs.include_cluster_authorized_operations_
  && endpoint_type_ == rhs.endpoint_type_
  && tagged_fields_ == rhs.tagged_fields_;
};


TopicRequest::TopicRequest(std::string name, std::vector<int32_t> partition_indexes, TaggedFields tagged_fields): name_{name}, partition_indexes_{partition_indexes}, tagged_fields_{tagged_fields} {};


uint32_t TopicRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(partition_indexes_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t TopicRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t TopicRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(partition_indexes_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t TopicRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool TopicRequest::operator==(const TopicRequest& rhs) const {

  return true
  && name_ == rhs.name_
  && partition_indexes_ == rhs.partition_indexes_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeProducersRequest::DescribeProducersRequest(std::vector<TopicRequest> topics, TaggedFields tagged_fields): topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t DescribeProducersRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeProducersRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeProducersRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeProducersRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeProducersRequest::operator==(const DescribeProducersRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


Listener::Listener(std::string name, std::string host, uint16_t port, int16_t security_protocol, TaggedFields tagged_fields): name_{name}, host_{host}, port_{port}, security_protocol_{security_protocol}, tagged_fields_{tagged_fields} {};


uint32_t Listener::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(security_protocol_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t Listener::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t Listener::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(security_protocol_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t Listener::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool Listener::operator==(const Listener& rhs) const {

  return true
  && name_ == rhs.name_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && security_protocol_ == rhs.security_protocol_
  && tagged_fields_ == rhs.tagged_fields_;
};


Feature::Feature(std::string name, int16_t min_supported_version, int16_t max_supported_version, TaggedFields tagged_fields): name_{name}, min_supported_version_{min_supported_version}, max_supported_version_{max_supported_version}, tagged_fields_{tagged_fields} {};


uint32_t Feature::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(min_supported_version_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(max_supported_version_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t Feature::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t Feature::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(min_supported_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(max_supported_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t Feature::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool Feature::operator==(const Feature& rhs) const {

  return true
  && name_ == rhs.name_
  && min_supported_version_ == rhs.min_supported_version_
  && max_supported_version_ == rhs.max_supported_version_
  && tagged_fields_ == rhs.tagged_fields_;
};


BrokerRegistrationRequest::BrokerRegistrationRequest(int32_t broker_id, std::string cluster_id, Uuid incarnation_id, std::vector<Listener> listeners, std::vector<Feature> features, absl::optional<std::string> rack, TaggedFields tagged_fields): broker_id_{broker_id}, cluster_id_{cluster_id}, incarnation_id_{incarnation_id}, listeners_{listeners}, features_{features}, rack_{rack}, is_migrating_zk_broker_{false}, log_dirs_{std::vector<Uuid>{}}, previous_broker_epoch_{-1}, tagged_fields_{tagged_fields} {};
BrokerRegistrationRequest::BrokerRegistrationRequest(int32_t broker_id, std::string cluster_id, Uuid incarnation_id, std::vector<Listener> listeners, std::vector<Feature> features, absl::optional<std::string> rack, bool is_migrating_zk_broker, TaggedFields tagged_fields): broker_id_{broker_id}, cluster_id_{cluster_id}, incarnation_id_{incarnation_id}, listeners_{listeners}, features_{features}, rack_{rack}, is_migrating_zk_broker_{is_migrating_zk_broker}, log_dirs_{std::vector<Uuid>{}}, previous_broker_epoch_{-1}, tagged_fields_{tagged_fields} {};
BrokerRegistrationRequest::BrokerRegistrationRequest(int32_t broker_id, std::string cluster_id, Uuid incarnation_id, std::vector<Listener> listeners, std::vector<Feature> features, absl::optional<std::string> rack, bool is_migrating_zk_broker, std::vector<Uuid> log_dirs, TaggedFields tagged_fields): broker_id_{broker_id}, cluster_id_{cluster_id}, incarnation_id_{incarnation_id}, listeners_{listeners}, features_{features}, rack_{rack}, is_migrating_zk_broker_{is_migrating_zk_broker}, log_dirs_{log_dirs}, previous_broker_epoch_{-1}, tagged_fields_{tagged_fields} {};
BrokerRegistrationRequest::BrokerRegistrationRequest(int32_t broker_id, std::string cluster_id, Uuid incarnation_id, std::vector<Listener> listeners, std::vector<Feature> features, absl::optional<std::string> rack, bool is_migrating_zk_broker, std::vector<Uuid> log_dirs, int64_t previous_broker_epoch, TaggedFields tagged_fields): broker_id_{broker_id}, cluster_id_{cluster_id}, incarnation_id_{incarnation_id}, listeners_{listeners}, features_{features}, rack_{rack}, is_migrating_zk_broker_{is_migrating_zk_broker}, log_dirs_{log_dirs}, previous_broker_epoch_{previous_broker_epoch}, tagged_fields_{tagged_fields} {};


uint32_t BrokerRegistrationRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(cluster_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeSize(incarnation_id_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(listeners_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(features_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(rack_);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.computeSize(is_migrating_zk_broker_);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.computeCompactSize(log_dirs_);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.computeSize(previous_broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BrokerRegistrationRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BrokerRegistrationRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(cluster_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encode(incarnation_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(listeners_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(features_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(rack_, dst);
  }
  
  if (api_version >= 1 && api_version < 4) {
    written += encoder.encode(is_migrating_zk_broker_, dst);
  }
  
  if (api_version >= 2 && api_version < 4) {
    written += encoder.encodeCompact(log_dirs_, dst);
  }
  
  if (api_version >= 3 && api_version < 4) {
    written += encoder.encode(previous_broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 4) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BrokerRegistrationRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BrokerRegistrationRequest::operator==(const BrokerRegistrationRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && cluster_id_ == rhs.cluster_id_
  && incarnation_id_ == rhs.incarnation_id_
  && listeners_ == rhs.listeners_
  && features_ == rhs.features_
  && rack_ == rhs.rack_
  && is_migrating_zk_broker_ == rhs.is_migrating_zk_broker_
  && log_dirs_ == rhs.log_dirs_
  && previous_broker_epoch_ == rhs.previous_broker_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


BrokerHeartbeatRequest::BrokerHeartbeatRequest(int32_t broker_id, int64_t broker_epoch, int64_t current_metadata_offset, bool want_fence, bool want_shut_down, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, current_metadata_offset_{current_metadata_offset}, want_fence_{want_fence}, want_shut_down_{want_shut_down}, tagged_fields_{tagged_fields} {};


uint32_t BrokerHeartbeatRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(current_metadata_offset_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(want_fence_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeSize(want_shut_down_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t BrokerHeartbeatRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t BrokerHeartbeatRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(current_metadata_offset_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(want_fence_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encode(want_shut_down_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t BrokerHeartbeatRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool BrokerHeartbeatRequest::operator==(const BrokerHeartbeatRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && current_metadata_offset_ == rhs.current_metadata_offset_
  && want_fence_ == rhs.want_fence_
  && want_shut_down_ == rhs.want_shut_down_
  && tagged_fields_ == rhs.tagged_fields_;
};


UnregisterBrokerRequest::UnregisterBrokerRequest(int32_t broker_id, TaggedFields tagged_fields): broker_id_{broker_id}, tagged_fields_{tagged_fields} {};


uint32_t UnregisterBrokerRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t UnregisterBrokerRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t UnregisterBrokerRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t UnregisterBrokerRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool UnregisterBrokerRequest::operator==(const UnregisterBrokerRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTransactionsRequest::DescribeTransactionsRequest(std::vector<std::string> transactional_ids, TaggedFields tagged_fields): transactional_ids_{transactional_ids}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTransactionsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(transactional_ids_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTransactionsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTransactionsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(transactional_ids_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTransactionsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTransactionsRequest::operator==(const DescribeTransactionsRequest& rhs) const {

  return true
  && transactional_ids_ == rhs.transactional_ids_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListTransactionsRequest::ListTransactionsRequest(std::vector<std::string> state_filters, std::vector<int64_t> producer_id_filters, TaggedFields tagged_fields): state_filters_{state_filters}, producer_id_filters_{producer_id_filters}, duration_filter_{-1}, tagged_fields_{tagged_fields} {};
ListTransactionsRequest::ListTransactionsRequest(std::vector<std::string> state_filters, std::vector<int64_t> producer_id_filters, int64_t duration_filter, TaggedFields tagged_fields): state_filters_{state_filters}, producer_id_filters_{producer_id_filters}, duration_filter_{duration_filter}, tagged_fields_{tagged_fields} {};


uint32_t ListTransactionsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(state_filters_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(producer_id_filters_);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.computeSize(duration_filter_);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListTransactionsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListTransactionsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(state_filters_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(producer_id_filters_, dst);
  }
  
  if (api_version >= 1 && api_version < 2) {
    written += encoder.encode(duration_filter_, dst);
  }
  
  if (api_version >= 0 && api_version < 2) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListTransactionsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListTransactionsRequest::operator==(const ListTransactionsRequest& rhs) const {

  return true
  && state_filters_ == rhs.state_filters_
  && producer_id_filters_ == rhs.producer_id_filters_
  && duration_filter_ == rhs.duration_filter_
  && tagged_fields_ == rhs.tagged_fields_;
};


AllocateProducerIdsRequest::AllocateProducerIdsRequest(int32_t broker_id, int64_t broker_epoch, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, tagged_fields_{tagged_fields} {};


uint32_t AllocateProducerIdsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AllocateProducerIdsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AllocateProducerIdsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AllocateProducerIdsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AllocateProducerIdsRequest::operator==(const AllocateProducerIdsRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestTopicPartitions::RequestTopicPartitions(Uuid topic_id, std::vector<int32_t> partitions, TaggedFields tagged_fields): topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t RequestTopicPartitions::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestTopicPartitions::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestTopicPartitions::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestTopicPartitions::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestTopicPartitions::operator==(const RequestTopicPartitions& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupHeartbeatRequest::ConsumerGroupHeartbeatRequest(std::string group_id, std::string member_id, int32_t member_epoch, absl::optional<std::string> instance_id, absl::optional<std::string> rack_id, int32_t rebalance_timeout_ms, absl::optional<std::vector<std::string>> subscribed_topic_names, absl::optional<std::string> server_assignor, absl::optional<std::vector<RequestTopicPartitions>> topic_partitions, TaggedFields tagged_fields): group_id_{group_id}, member_id_{member_id}, member_epoch_{member_epoch}, instance_id_{instance_id}, rack_id_{rack_id}, rebalance_timeout_ms_{rebalance_timeout_ms}, subscribed_topic_names_{subscribed_topic_names}, server_assignor_{server_assignor}, topic_partitions_{topic_partitions}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupHeartbeatRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(group_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(member_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(member_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(instance_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(rack_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(rebalance_timeout_ms_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(subscribed_topic_names_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(server_assignor_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topic_partitions_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupHeartbeatRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(group_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(member_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(member_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(instance_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(rack_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(rebalance_timeout_ms_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(subscribed_topic_names_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(server_assignor_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topic_partitions_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupHeartbeatRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupHeartbeatRequest::operator==(const ConsumerGroupHeartbeatRequest& rhs) const {

  return true
  && group_id_ == rhs.group_id_
  && member_id_ == rhs.member_id_
  && member_epoch_ == rhs.member_epoch_
  && instance_id_ == rhs.instance_id_
  && rack_id_ == rhs.rack_id_
  && rebalance_timeout_ms_ == rhs.rebalance_timeout_ms_
  && subscribed_topic_names_ == rhs.subscribed_topic_names_
  && server_assignor_ == rhs.server_assignor_
  && topic_partitions_ == rhs.topic_partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


ConsumerGroupDescribeRequest::ConsumerGroupDescribeRequest(std::vector<std::string> group_ids, bool include_authorized_operations, TaggedFields tagged_fields): group_ids_{group_ids}, include_authorized_operations_{include_authorized_operations}, tagged_fields_{tagged_fields} {};


uint32_t ConsumerGroupDescribeRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(group_ids_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(include_authorized_operations_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ConsumerGroupDescribeRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ConsumerGroupDescribeRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(group_ids_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(include_authorized_operations_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ConsumerGroupDescribeRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ConsumerGroupDescribeRequest::operator==(const ConsumerGroupDescribeRequest& rhs) const {

  return true
  && group_ids_ == rhs.group_ids_
  && include_authorized_operations_ == rhs.include_authorized_operations_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControllerRegistrationRequestListener::ControllerRegistrationRequestListener(std::string name, std::string host, uint16_t port, int16_t security_protocol, TaggedFields tagged_fields): name_{name}, host_{host}, port_{port}, security_protocol_{security_protocol}, tagged_fields_{tagged_fields} {};


uint32_t ControllerRegistrationRequestListener::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(host_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(port_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(security_protocol_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequestListener::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControllerRegistrationRequestListener::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(host_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(port_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(security_protocol_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequestListener::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControllerRegistrationRequestListener::operator==(const ControllerRegistrationRequestListener& rhs) const {

  return true
  && name_ == rhs.name_
  && host_ == rhs.host_
  && port_ == rhs.port_
  && security_protocol_ == rhs.security_protocol_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControllerRegistrationRequestFeature::ControllerRegistrationRequestFeature(std::string name, int16_t min_supported_version, int16_t max_supported_version, TaggedFields tagged_fields): name_{name}, min_supported_version_{min_supported_version}, max_supported_version_{max_supported_version}, tagged_fields_{tagged_fields} {};


uint32_t ControllerRegistrationRequestFeature::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(name_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(min_supported_version_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(max_supported_version_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequestFeature::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControllerRegistrationRequestFeature::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(name_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(min_supported_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(max_supported_version_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequestFeature::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControllerRegistrationRequestFeature::operator==(const ControllerRegistrationRequestFeature& rhs) const {

  return true
  && name_ == rhs.name_
  && min_supported_version_ == rhs.min_supported_version_
  && max_supported_version_ == rhs.max_supported_version_
  && tagged_fields_ == rhs.tagged_fields_;
};


ControllerRegistrationRequest::ControllerRegistrationRequest(int32_t controller_id, Uuid incarnation_id, bool zk_migration_ready, std::vector<ControllerRegistrationRequestListener> listeners, std::vector<ControllerRegistrationRequestFeature> features, TaggedFields tagged_fields): controller_id_{controller_id}, incarnation_id_{incarnation_id}, zk_migration_ready_{zk_migration_ready}, listeners_{listeners}, features_{features}, tagged_fields_{tagged_fields} {};


uint32_t ControllerRegistrationRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(controller_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(incarnation_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(zk_migration_ready_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(listeners_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(features_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ControllerRegistrationRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(controller_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(incarnation_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(zk_migration_ready_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(listeners_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(features_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ControllerRegistrationRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ControllerRegistrationRequest::operator==(const ControllerRegistrationRequest& rhs) const {

  return true
  && controller_id_ == rhs.controller_id_
  && incarnation_id_ == rhs.incarnation_id_
  && zk_migration_ready_ == rhs.zk_migration_ready_
  && listeners_ == rhs.listeners_
  && features_ == rhs.features_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsRequestRequestPartitionData::AssignReplicasToDirsRequestRequestPartitionData(int32_t partition_index, TaggedFields tagged_fields): partition_index_{partition_index}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsRequestRequestPartitionData::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(partition_index_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsRequestRequestPartitionData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsRequestRequestPartitionData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(partition_index_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsRequestRequestPartitionData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsRequestRequestPartitionData::operator==(const AssignReplicasToDirsRequestRequestPartitionData& rhs) const {

  return true
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsRequestRequestTopicData::AssignReplicasToDirsRequestRequestTopicData(Uuid topic_id, std::vector<AssignReplicasToDirsRequestRequestPartitionData> partitions, TaggedFields tagged_fields): topic_id_{topic_id}, partitions_{partitions}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsRequestRequestTopicData::computeSize(const EncodingContext& encoder) const {
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

uint32_t AssignReplicasToDirsRequestRequestTopicData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsRequestRequestTopicData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t AssignReplicasToDirsRequestRequestTopicData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsRequestRequestTopicData::operator==(const AssignReplicasToDirsRequestRequestTopicData& rhs) const {

  return true
  && topic_id_ == rhs.topic_id_
  && partitions_ == rhs.partitions_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestDirectoryData::RequestDirectoryData(Uuid id, std::vector<AssignReplicasToDirsRequestRequestTopicData> topics, TaggedFields tagged_fields): id_{id}, topics_{topics}, tagged_fields_{tagged_fields} {};


uint32_t RequestDirectoryData::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestDirectoryData::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestDirectoryData::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestDirectoryData::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestDirectoryData::operator==(const RequestDirectoryData& rhs) const {

  return true
  && id_ == rhs.id_
  && topics_ == rhs.topics_
  && tagged_fields_ == rhs.tagged_fields_;
};


AssignReplicasToDirsRequest::AssignReplicasToDirsRequest(int32_t broker_id, int64_t broker_epoch, std::vector<RequestDirectoryData> directories, TaggedFields tagged_fields): broker_id_{broker_id}, broker_epoch_{broker_epoch}, directories_{directories}, tagged_fields_{tagged_fields} {};


uint32_t AssignReplicasToDirsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(broker_id_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(broker_epoch_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(directories_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t AssignReplicasToDirsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(broker_id_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(broker_epoch_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(directories_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t AssignReplicasToDirsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool AssignReplicasToDirsRequest::operator==(const AssignReplicasToDirsRequest& rhs) const {

  return true
  && broker_id_ == rhs.broker_id_
  && broker_epoch_ == rhs.broker_epoch_
  && directories_ == rhs.directories_
  && tagged_fields_ == rhs.tagged_fields_;
};


ListClientMetricsResourcesRequest::ListClientMetricsResourcesRequest(TaggedFields tagged_fields): tagged_fields_{tagged_fields} {};


uint32_t ListClientMetricsResourcesRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t ListClientMetricsResourcesRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t ListClientMetricsResourcesRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t ListClientMetricsResourcesRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool ListClientMetricsResourcesRequest::operator==(const ListClientMetricsResourcesRequest& rhs) const {

  return true
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTopicPartitionsRequestTopicRequest::DescribeTopicPartitionsRequestTopicRequest(std::string name, TaggedFields tagged_fields): name_{name}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTopicPartitionsRequestTopicRequest::computeSize(const EncodingContext& encoder) const {
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

uint32_t DescribeTopicPartitionsRequestTopicRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTopicPartitionsRequestTopicRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t DescribeTopicPartitionsRequestTopicRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTopicPartitionsRequestTopicRequest::operator==(const DescribeTopicPartitionsRequestTopicRequest& rhs) const {

  return true
  && name_ == rhs.name_
  && tagged_fields_ == rhs.tagged_fields_;
};


RequestCursor::RequestCursor(std::string topic_name, int32_t partition_index, TaggedFields tagged_fields): topic_name_{topic_name}, partition_index_{partition_index}, tagged_fields_{tagged_fields} {};


uint32_t RequestCursor::computeSize(const EncodingContext& encoder) const {
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

uint32_t RequestCursor::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t RequestCursor::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
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

uint32_t RequestCursor::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool RequestCursor::operator==(const RequestCursor& rhs) const {

  return true
  && topic_name_ == rhs.topic_name_
  && partition_index_ == rhs.partition_index_
  && tagged_fields_ == rhs.tagged_fields_;
};


DescribeTopicPartitionsRequest::DescribeTopicPartitionsRequest(std::vector<DescribeTopicPartitionsRequestTopicRequest> topics, int32_t response_partition_limit, absl::optional<RequestCursor> cursor, TaggedFields tagged_fields): topics_{topics}, response_partition_limit_{response_partition_limit}, cursor_{cursor}, tagged_fields_{tagged_fields} {};


uint32_t DescribeTopicPartitionsRequest::computeSize(const EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(topics_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(response_partition_limit_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeSize(cursor_);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.computeCompactSize(tagged_fields_);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsRequest::computeCompactSize(const EncodingContext& encoder) const {
  return computeSize(encoder);
}


uint32_t DescribeTopicPartitionsRequest::encode(Buffer::Instance& dst, EncodingContext& encoder) const {
  const int16_t api_version = encoder.apiVersion();
  uint32_t written{0};

  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(topics_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(response_partition_limit_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encode(cursor_, dst);
  }
  
  if (api_version >= 0 && api_version < 1) {
    written += encoder.encodeCompact(tagged_fields_, dst);
  }
  

  return written;
}

uint32_t DescribeTopicPartitionsRequest::encodeCompact(Buffer::Instance& dst, EncodingContext& encoder) const {
  return encode(dst, encoder);
}


bool DescribeTopicPartitionsRequest::operator==(const DescribeTopicPartitionsRequest& rhs) const {

  return true
  && topics_ == rhs.topics_
  && response_partition_limit_ == rhs.response_partition_limit_
  && cursor_ == rhs.cursor_
  && tagged_fields_ == rhs.tagged_fields_;
};

}}}}