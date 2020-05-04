#pragma once

#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class ClusteringLogic: private Logger::Loggable<Logger::Id::kafka> {
public:

  ClusteringLogic();

  std::string computeClusterForTopic(const std::string& topic) const;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
