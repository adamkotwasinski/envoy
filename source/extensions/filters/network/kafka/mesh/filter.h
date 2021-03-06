#pragma once

#include "envoy/common/time.h"
#include "envoy/network/filter.h"
#include "envoy/stats/scope.h"

#include "common/common/logger.h"

#include "extensions/filters/network/kafka/external/requests.h"
#include "extensions/filters/network/kafka/mesh/abstract_command.h"
#include "extensions/filters/network/kafka/mesh/clustering.h"
#include "extensions/filters/network/kafka/mesh/splitter.h"
#include "extensions/filters/network/kafka/mesh/upstream_kafka_facade.h"
#include "extensions/filters/network/kafka/request_codec.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class KafkaMeshFilter : public Network::ReadFilter,
                        public Network::ConnectionCallbacks,
                        public AbstractRequestListener,
                        private Logger::Loggable<Logger::Id::kafka> {
public:
  /**
   * Main constructor.
   */
  KafkaMeshFilter(const ClusteringConfiguration& clustering_configuration,
                  UpstreamKafkaFacade& upstream_kafka_facade);

  /**
   * Visible for testing.
   */
  KafkaMeshFilter(const ClusteringConfiguration& clustering_configuration,
                  UpstreamKafkaFacade& upstream_kafka_facade,
                  RequestDecoderSharedPtr request_decoder);

  ~KafkaMeshFilter() override;

  // Network::ReadFilter
  Network::FilterStatus onNewConnection() override;
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override;
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;

  // Network::ConnectionCallbacks
  void onEvent(Network::ConnectionEvent event) override;
  void onAboveWriteBufferHighWatermark() override;
  void onBelowWriteBufferLowWatermark() override;

  // AbstractRequestListener
  void onRequest(InFlightRequestSharedPtr request) override;
  void onRequestReadyForAnswer() override;

  std::list<InFlightRequestSharedPtr>& getRequestsInFlightForTest();

private:
  /**
   * Helper method invoked when connection gets dropped.
   */
  void abandonAllInFlightRequests();

  const RequestDecoderSharedPtr request_decoder_;
  UpstreamKafkaFacade& upstream_kafka_facade_;

  Network::ReadFilterCallbacks* read_filter_callbacks_;

  std::list<InFlightRequestSharedPtr> requests_in_flight_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
