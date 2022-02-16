#pragma once

#include "source/common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FilterConsumerManager {
public:
    virtual ~FilterConsumerManager() = default;

    virtual int64_t listOffsets(std::string topic, int32_t partition) PURE;

    virtual void fetchRecords(std::string topic, int32_t partition, int64_t offset) PURE;
};

class FilterConsumerManagerImpl: public FilterConsumerManager, private Logger::Loggable<Logger::Id::kafka> {
public:
    FilterConsumerManagerImpl();

    int64_t listOffsets(std::string topic, int32_t partition) override;

    void fetchRecords(std::string topic, int32_t partition, int64_t offset) override;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy