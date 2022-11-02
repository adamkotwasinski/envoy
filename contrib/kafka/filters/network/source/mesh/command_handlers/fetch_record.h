#pragma once

#include <memory>
#include <vector>

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/external/responses.h"

// FIXME
#include "librdkafka/rdkafkacpp.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// FIXME its triplicate now!
using RdKafkaMessagePtr = std::shared_ptr<RdKafka::Message>;

class FetchResponsePayloadProcessor : private Logger::Loggable<Logger::Id::kafka> {
public:

    std::vector<FetchableTopicResponse> transform(const std::vector<RdKafkaMessagePtr>& arg) const;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
