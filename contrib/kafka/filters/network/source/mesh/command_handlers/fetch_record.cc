#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record.h"

#include "contrib/kafka/filters/network/source/mesh/command_handlers/crc.h"

#include "source/common/buffer/buffer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

void FetchResponsePayloadProcessor::print(const Bytes& arg, std::string ctx) const {
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < arg.size(); ++i) {
        int32_t v = static_cast<int32_t>(arg[i]);
        oss << v << ", ";
    }
    oss << "]";
    ENVOY_LOG(info, "{} ({}) = {}", ctx, arg.size(), oss.str());
}

Bytes computeCrc(const void* data, const size_t len) {   
    kafka_crc32c_t crc;
 
    crc = kafka_crc32c_init();
    crc = kafka_crc32c_update(crc, data, len);
    crc = kafka_crc32c_finalize(crc);

    std::cout << "crc = " << crc << std::endl;

    crc = htobe32(crc);

    Bytes result;
    unsigned char* raw = reinterpret_cast<unsigned char*>(&crc);
    result.insert(result.end(), raw, raw + sizeof(crc));
    return result;
}

std::vector<FetchableTopicResponse> FetchResponsePayloadProcessor::transform(const std::map<KafkaPartition, std::vector<RdKafkaMessagePtr>>& arg) const {

    std::map<KafkaPartition, Bytes> partition_to_bytes;
    for (const auto& e : arg) {
        const KafkaPartition kp = e.first;
        const std::vector<RdKafkaMessagePtr>& partition_records = e.second;
        for (const auto& r : partition_records) {
            ENVOY_LOG(info, "processing record {}-{} / {}", r->topic_name(), r->partition(), r->offset());
            Bytes& partition_outbound_bytes = partition_to_bytes[kp];
            append(partition_outbound_bytes, r);
        }
    }

    // https://kafka.apache.org/documentation/#recordbatch
    /*
    baseOffset: int64
    batchLength: int32
    partitionLeaderEpoch: int32 / 4
    magic: int8 (current magic value is 2) / 5
    crc: int32 / 9
    attributes: int16 / 11
        bit 0~2:
            0: no compression
            1: gzip
            2: snappy
            3: lz4
            4: zstd
        bit 3: timestampType
        bit 4: isTransactional (0 means not transactional)
        bit 5: isControlBatch (0 means not a control batch)
        bit 6: hasDeleteHorizonMs (0 means baseTimestamp is not set as the delete horizon for compaction)
        bit 7~15: unused
    lastOffsetDelta: int32 / 15
    baseTimestamp: int64 / 23
    maxTimestamp: int64 / 31
    producerId: int64 / 39
    producerEpoch: int16 / 41
    baseSequence: int32 / 45
    records: [Record]
    */
    for (auto& e : partition_to_bytes) {
        const Bytes& orig = e.second;
        Bytes new_ones = {};

        int64_t base_offset = htobe64(0);
        unsigned char* base_offset_b = reinterpret_cast<unsigned char*>(&base_offset);
        new_ones.insert(new_ones.end(), base_offset_b, base_offset_b + sizeof(base_offset));

        // batch length placeholder
        new_ones.insert(new_ones.end(), {13, 13, 13, 13});

        // all other cool attributes
        std::vector zeros(45, 0);
        new_ones.insert(new_ones.end(), zeros.begin(), zeros.end());

        Bytes what = { 0, 0, 0, static_cast<uint8_t>(arg.find(e.first)->second.back()->offset()) };
        // put something into lastOffsetDelta
        std::copy(what.begin(), what.end(), new_ones.begin() + 8 + 4 + 11);

        // records (count)
        const KafkaPartition kp = e.first;
        int32_t record_count = htobe32(arg.find(kp)->second.size());
        unsigned char* record_count_b = reinterpret_cast<unsigned char*>(&record_count);
        new_ones.insert(new_ones.end(), record_count_b, record_count_b + sizeof(record_count));
        ENVOY_LOG(info, "there are {} records for {}-{}", be32toh(record_count), kp.first, kp.second);

        // records
        new_ones.insert(new_ones.end(), orig.begin(), orig.end());
        print(new_ones, "with records");

        // SET BATCH LEN
        int32_t batch_len = htobe32(new_ones.size() - (sizeof(base_offset) + sizeof(batch_len)));
        unsigned char* batch_len_b = reinterpret_cast<unsigned char*>(&batch_len);
        std::copy(batch_len_b, batch_len_b + sizeof(batch_len), new_ones.begin() + sizeof(base_offset));
        print(new_ones, "batch len set");

        // SET MAGIC
        uint32_t magic_offset = sizeof(base_offset) + sizeof(batch_len) + sizeof(int32_t /* PL epoch */);
        new_ones[magic_offset] = 2;

        // CRC
        uint32_t crc_offset = magic_offset + 1;
        Bytes crc = computeCrc(&(*(new_ones.begin() + crc_offset + 4)), new_ones.size() - (crc_offset + 4));
        std::copy(crc.begin(), crc.end(), new_ones.begin() + crc_offset);
        print(new_ones, "magic + CRC set");

        // haha
        e.second = new_ones;
    }

    std::map<std::string, std::vector<FetchResponseResponsePartitionData>> topic_to_frrpd;
    for (const auto& e : partition_to_bytes) {
        const std::string& topic_name = e.first.first;
        const int32_t partition = e.first.second;
        std::vector<FetchResponseResponsePartitionData>& frrpds = topic_to_frrpd[topic_name];

        // We finally construct FRRPD...
        const int16_t error_code = 0;
        const int64_t high_watermark = 0;
        const auto frrpd = FetchResponseResponsePartitionData{partition, error_code, high_watermark, absl::make_optional(e.second)};

        frrpds.push_back(frrpd);
    }

    std::vector<FetchableTopicResponse> result;
    for (const auto& e : topic_to_frrpd) {
        const std::string& topic_name = e.first;
        const auto ftr = FetchableTopicResponse{ topic_name, e.second };

        result.push_back(ftr);
    }

    return result;
}

uint32_t writeUnsignedVarint(uint32_t arg, Buffer::Instance& dst) {
    uint32_t value = arg;

    uint32_t elements_with_1 = 0;
    // As long as there are bits set on indexes 8 or higher (counting from 1).
    while ((value & ~(0x7f)) != 0) {
        // Save next 7-bit batch with highest bit set.
        const uint8_t el = (value & 0x7f) | 0x80;
        dst.add(&el, sizeof(uint8_t));
        value >>= 7;
        elements_with_1++;
    }

    // After the loop has finished, we are certain that bit 8 = 0, so we can just add final element.
    const uint8_t el = value;
    dst.add(&el, sizeof(uint8_t));

    return elements_with_1 + 1;
}

uint32_t writeVarint(int32_t arg, Buffer::Instance& dst) {
    return writeUnsignedVarint((arg << 1) ^ (arg >> 31), dst);
}

// THIS IMPL IS BROKEN
uint32_t writeVarlong(int64_t arg, Buffer::Instance& dst) {
    int64_t value = arg;

    uint32_t elements_with_1 = 0;
    // As long as there are bits set on indexes 8 or higher (counting from 1).
    while ((value & ~(0x7f)) != 0) {
        // Save next 7-bit batch with highest bit set.
        const uint8_t el = (value & 0x7f) | 0x80;
        dst.add(&el, sizeof(uint8_t));
        value >>= 7;
        elements_with_1++;
    }

    // After the loop has finished, we are certain that bit 8 = 0, so we can just add final element.
    const uint8_t el = value;
    dst.add(&el, sizeof(uint8_t));

    return elements_with_1 + 1;
}

static int32_t shared_offset_delta = 77;

void FetchResponsePayloadProcessor::append(Bytes& out, const RdKafkaMessagePtr& ptr) const {

    Buffer::OwnedImpl b_out;

    uint32_t written = 0;

    // https://github.com/apache/kafka/blob/2.4.1/clients/src/main/java/org/apache/kafka/common/record/DefaultRecord.java#L179

    // attributes: int8
    const int8_t attributes = 0;
    b_out.add(&attributes, sizeof(int8_t));
    written += 1;
    
    // timestampDelta: varlong
    const int64_t timestamp_delta = 0;
    written += writeVarlong(timestamp_delta, b_out);

    // offsetDelta: varint
    const int32_t offset_delta = ptr->offset();
    written += writeVarint(offset_delta, b_out);

    // keyLength: varint
    const int32_t key_length = 0;
    written += writeVarint(key_length, b_out);

    // key: byte[]
    // ???

    // valueLen: varint
    const int32_t value_length = ptr->len();
    written += writeVarint(value_length, b_out);

    // value: byte[]
    b_out.add(ptr->payload(), value_length);
    written += value_length;

    // Headers => [Header]
    // headerKeyLength: varint
    // headerKey: String
    // headerValueLength: varint
    // Value: byte[]
    written += writeVarint(0, b_out);

    ENVOY_LOG(info, "len of record {}-{}/{} = {}", ptr->topic_name(), ptr->partition(), ptr->offset(), written);

    Buffer::OwnedImpl len_buf;
    writeVarint(written, len_buf);
    b_out.prepend(len_buf);

    void* rawi = b_out.linearize(b_out.length());
    unsigned char* raw = static_cast<unsigned char*>(rawi);

    ENVOY_LOG(info, "final len of record {}-{}/{} = {}", ptr->topic_name(), ptr->partition(), ptr->offset(), b_out.length());
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < b_out.length(); ++i) {
        int32_t v = static_cast<int32_t>(raw[i]);
        oss << v << ", ";
    }
    oss << "]";
    ENVOY_LOG(info, "record = {}", oss.str());

    out.insert(out.end(), raw, raw + b_out.length());
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
