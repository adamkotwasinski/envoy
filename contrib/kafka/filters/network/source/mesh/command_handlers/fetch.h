#pragma once

#include "contrib/kafka/filters/network/source/external/requests.h"
#include "contrib/kafka/filters/network/source/mesh/abstract_command.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"
#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchRequestHolder : public BaseInFlightRequest,
                           public RecordCb,
                           public std::enable_shared_from_this<FetchRequestHolder> {
public:
  FetchRequestHolder(AbstractRequestListener& filter, SharedConsumerManager& consumer_manager,
                     const std::shared_ptr<Request<FetchRequest>> request);

  void startProcessing() override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

  // Whether the given fetch request should be sent downstream.
  // Typical cases are:
  // - it has enough records (meeting request's minimal requirements),
  // - enough time has passed.
  bool isEligibleForSendingDownstream() const;

  // RecordCb
  bool receive(RdKafkaMessagePtr message) override;

private:
  // Provides access to upstream-pointing consumers.
  SharedConsumerManager& consumer_manager_;
  // Original request.
  const std::shared_ptr<Request<FetchRequest>> request_;
  // The messages to send downstream.
  std::vector<RdKafkaMessagePtr> messages_;
  // Translates librdkafka objects into bytes to be sent downstream.
  const FetchResponsePayloadProcessor processor_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
