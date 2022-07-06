#pragma once

#include "contrib/kafka/filters/network/source/external/requests.h"
#include "contrib/kafka/filters/network/source/mesh/abstract_command.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_client.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchRequestHolder : public BaseInFlightRequest,
                           public RecordCb,
                           public std::enable_shared_from_this<FetchRequestHolder> {
public:
  FetchRequestHolder(AbstractRequestListener& filter, SharedConsumerManager& consumer_manager, const std::shared_ptr<Request<FetchRequest>> request);

  void startProcessing() override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

  // RecordCb
  void accept() override;

private:
  // Provides access to upstream-pointing consumers.
  SharedConsumerManager& consumer_manager_;
  // Original request.
  const std::shared_ptr<Request<FetchRequest>> request_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
