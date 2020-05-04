#pragma once

#include "common/common/logger.h"

#include "envoy/extensions/filters/network/kafka_mesh/v3/kafka_mesh.pb.h"
#include "envoy/extensions/filters/network/kafka_mesh/v3/kafka_mesh.pb.validate.h"

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

using KafkaMeshProtoConfig = envoy::extensions::filters::network::kafka_mesh::v3::KafkaMesh;

class Magic: private Logger::Loggable<Logger::Id::kafka> {
public:


  Magic(const KafkaMeshProtoConfig& config);

};

using MagicSharedPtr = std::shared_ptr<Magic>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
