#pragma once

#include "common/common/logger.h"

#include "extensions/filters/network/kafka/external/requests.h"
#include "extensions/filters/network/kafka/external/responses.h"

#include "extensions/filters/network/kafka/mesh/clustering.h"
#include "extensions/filters/network/kafka/mesh/upstream_kafka_facade.h"

#include <map>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

/**
 * Callback to be implemented by entities that are interested when the request has finished and has answer ready.
 */
// Impl note: Filter is interested in requests that originated in a given filter, because it can then send answers.
class AbstractRequestListener {
public:

  virtual ~AbstractRequestListener() = default;

  // Notified the listener, that the request finally has an answer ready.
  // Usually this means that the request has been sent to upstream Kafka clsuters and we got answers
  // (unless it's something that could be responded to locally).
  // IMPL: we do not need to pass request here, as filters need to answer in-order.
  // What means that we always need to check if first answer is ready, even if the latter are already finished.
  virtual void onRequestReadyForAnswer() PURE;

};

/**
 * Represents single downstream client request.
 * Responsible for performing the work on multiple upstream clusters and aggregating the results.
 */
class AbstractInFlightRequest {
public:

  virtual ~AbstractInFlightRequest() = default;

  virtual void invoke(UpstreamKafkaFacade&, const ClusteringLogic&) PURE;

  virtual bool finished() const PURE;

  virtual AbstractResponseSharedPtr computeAnswer() const PURE;

};

using AbstractInFlightRequestSharedPtr = std::shared_ptr<AbstractInFlightRequest>;

////////////////////////////////////////////////////////////////////////////////////////////////////
// The things below should be in their own header.
////////////////////////////////////////////////////////////////////////////////////////////////////

class ApiVersionsRequestHolder: public AbstractInFlightRequest {
public:

  ApiVersionsRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<ApiVersionsRequest>> request);

  void invoke(UpstreamKafkaFacade&, const ClusteringLogic&) override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

private:

  // Filter that originated this produce request.
  AbstractRequestListener& filter_;

  // Original request.
  const std::shared_ptr<Request<ApiVersionsRequest>> request_;

};

class MetadataRequestHolder: public AbstractInFlightRequest {
public:

  MetadataRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<MetadataRequest>> request);

  void invoke(UpstreamKafkaFacade&, const ClusteringLogic&) override;

  bool finished() const override;

  AbstractResponseSharedPtr computeAnswer() const override;

private:

  // Filter that originated this produce request.
  AbstractRequestListener& filter_;

  // Original request.
  const std::shared_ptr<Request<MetadataRequest>> request_;

};

/**
 * Kafka 'Produce' request, that is aimed at particular cluster.
 * A single downstream client that sends a Produce request can map into multiple PRFCs,
 * as the topics can be hosted on different clusters.
 */
class ProduceRequestHolder: public AbstractInFlightRequest, public ProduceFinishCb, public std::enable_shared_from_this<ProduceRequestHolder>, private Logger::Loggable<Logger::Id::kafka> {
public:

  ProduceRequestHolder(AbstractRequestListener& filter, const std::shared_ptr<Request<ProduceRequest>> request);

  // AbstractInFlightRequest
  void invoke(UpstreamKafkaFacade&, const ClusteringLogic&) override;

  // AbstractInFlightRequest
  bool finished() const override;

  // AbstractInFlightRequest
  AbstractResponseSharedPtr computeAnswer() const override;

  // ProduceFinishCb
  bool accept(const DeliveryMemento& memento) override;

private:

  struct RecordFootmark {

    std::string topic_;
    int32_t partition_;
    absl::string_view key_;
    absl::string_view value_;

    int16_t error_code_;
    uint32_t saved_offset_;

    RecordFootmark(const std::string& topic, const int32_t partition, const absl::string_view key, const absl::string_view value):
      topic_{topic}, partition_{partition}, key_{key}, value_{value}, error_code_{0}, saved_offset_{0} {};

  };

  static std::vector<RecordFootmark> computeFootmarks(const std::string& topic, const int32_t partition, const Bytes& records);

  void notifyFilter();

  // Filter that originated this produce request.
  AbstractRequestListener& filter_;

  // Original request.
  const std::shared_ptr<Request<ProduceRequest>> request_;

  // How many responses from Kafka Producer handling our request do we expect.
  int expected_responses_;

  std::vector<RecordFootmark> footmarks_;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
