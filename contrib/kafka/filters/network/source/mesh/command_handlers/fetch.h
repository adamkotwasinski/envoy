#pragma once

#include "contrib/kafka/filters/network/source/external/requests.h"
#include "contrib/kafka/filters/network/source/mesh/abstract_command.h"
#include "contrib/kafka/filters/network/source/mesh/filter_consumer_manager_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchRequestHolder : public BaseInFlightRequest {
public:
  FetchRequestHolder(AbstractRequestListener& filter, FilterConsumerManager& consumer_manager, const std::shared_ptr<Request<FetchRequest>> request);

  void startProcessing() override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

private:
  // Provides access to upstream-pointing consumers.
  FilterConsumerManager& consumer_manager_;
  // Original request.
  const std::shared_ptr<Request<FetchRequest>> request_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
