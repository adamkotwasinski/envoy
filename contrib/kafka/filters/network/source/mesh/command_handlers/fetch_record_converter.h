#pragma once

#include <memory>
#include <vector>

#include "source/common/common/logger.h"

#include "contrib/kafka/filters/network/source/kafka_types.h"
#include "contrib/kafka/filters/network/source/external/responses.h"
#include "contrib/kafka/filters/network/source/mesh/inbound_record.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchResponsePayloadProcessor : private Logger::Loggable<Logger::Id::kafka> {
public:

    std::vector<FetchableTopicResponse> transform(const std::map<KafkaPartition, std::vector<InboundRecordSharedPtr>>& arg) const;

private:

    void print(const Bytes& arg, const std::string ctx = "arg") const;

    void append(Bytes& out, const InboundRecordSharedPtr& ptr) const;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
