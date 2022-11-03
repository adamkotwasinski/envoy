#pragma once

#include "contrib/kafka/filters/network/source/external/requests.h"
#include "contrib/kafka/filters/network/source/mesh/abstract_command.h"
#include "contrib/kafka/filters/network/source/mesh/shared_consumer_manager.h"
#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer.h"
#include "contrib/kafka/filters/network/source/mesh/inbound_record.h"
#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record_converter.h"
#include "contrib/kafka/filters/network/source/mesh/fetch_purger.h"

#include "envoy/event/timer.h"

#include "absl/synchronization/mutex.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchRequestHolder : public BaseInFlightRequest,
                           public RecordCb,
                           public std::enable_shared_from_this<FetchRequestHolder> {
public:
  FetchRequestHolder(AbstractRequestListener& filter, SharedConsumerManager& consumer_manager, FetchPurger& fetch_purger,
                     const std::shared_ptr<Request<FetchRequest>> request);

  void startProcessing() override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

  // Invoked by timer as this requests's time runs out.
  // It is possible that this request has already been finished (there was data to send),
  // then this method does nothing.
  void markFinishedByTimer();

  // XXX
  // Whether the given fetch request should be sent downstream.
  // Typical cases are:
  // - it has enough records (meeting request's minimal requirements),
  // - enough time has passed.
  // bool isEligibleForSendingDownstream() const;

  // RecordCb
  Reply receive(InboundRecordSharedPtr message) override;

  // RecordCb
  TopicToPartitionsMap interest() const override;

  // RecordCb
  std::string debugId() const override;

private:

  // Invoked internally when we want to mark this Fetch request as done.
  // This means: we are no longer interested in future messages and might need to unregister ourselves.
  void cleanup(bool unregister);

  // Provides access to upstream-pointing consumers.
  SharedConsumerManager& consumer_manager_;
  // Registers this fetch request's timeout just in case we get no data from upstream.
  FetchPurger& fetch_purger_;
  // Original request.
  const std::shared_ptr<Request<FetchRequest>> request_;

  mutable absl::Mutex state_mutex_;
  // Whether this request has finished processing and is ready for sending upstream.
  bool finished_ ABSL_GUARDED_BY(state_mutex_) = false;
  // The messages to send downstream.
  std::map<KafkaPartition, std::vector<InboundRecordSharedPtr>> messages_ ABSL_GUARDED_BY(state_mutex_);

  // Timeout timer.
  Event::TimerPtr timer_;
  // Translates librdkafka objects into bytes to be sent downstream.
  const FetchResponsePayloadProcessor processor_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
