#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::vector<FetchableTopicResponse> FetchResponsePayloadProcessor::transform(const std::vector<RdKafkaMessagePtr>& arg) const {
    //ENVOY_LOG(info, "Transforming {} records", arg.size());
    std::vector<FetchableTopicResponse> result;

    for (const auto& message : arg) {
        //ENVOY_LOG(info, "Processing {}/{}", message->partition(), message->offset());
    }

    return result;
    // The librdkafka messages are finally freed here.
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
