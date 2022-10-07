#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::vector<FetchableTopicResponse> FetchResponsePayloadProcessor::transform(const std::vector<RdKafkaMessagePtr>& arg) const {
    ENVOY_LOG(info, "Transforming {} records", arg.size());
    std::vector<FetchableTopicResponse> result;

    std::map<std::string, FetchableTopicResponse> topic_to_ftr;

    std::map<std::pair<std::string, int32_t>, Bytes> records;

    for (const auto& message : arg) {
        ENVOY_LOG(info, "Processing {}-{}/{}", message->topic_name(), message->partition(), message->offset());

        const auto& topic_name = message->topic_name();
        const auto partition = message->partition();

        FetchableTopicResponse ftr_candidate = { topic_name, {}, TaggedFields{}};
        auto ftr = topic_to_ftr.emplace(topic_name, ftr_candidate);
        
        std::pair<std::string, int32_t> pk = {topic_name, partition};
        append(records[pk], message);
    }

    ENVOY_LOG(info, "there are {} topics, {} partition responses", topic_to_ftr.size(), records.size());
    for (const auto& e : records) {
        ENVOY_LOG(info, "{}-{} -> {}", e.first.first, e.first.second, e.second.size());
    }

    return result;
    // The librdkafka messages are finally freed here.
}

void FetchResponsePayloadProcessor::append(Bytes& out, const RdKafkaMessagePtr& ptr) const {
    out.push_back(0);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
