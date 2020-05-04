#include "extensions/filters/network/kafka/mesh/clustering.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

ClusteringLogic::ClusteringLogic() {}

std::string ClusteringLogic::computeClusterForTopic(const std::string& topic) const {
  if (topic.rfind("apples", 0) == 0) {
    return "localkafka_m1";
  } else {
    return "localkafka_m2";
  }
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
