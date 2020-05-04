#pragma once

#include "envoy/common/time.h"
#include "envoy/network/filter.h"
#include "envoy/stats/scope.h"

#include "common/common/logger.h"

#include "extensions/filters/network/kafka/external/request_metrics.h"
#include "extensions/filters/network/kafka/external/response_metrics.h"
#include "extensions/filters/network/kafka/parser.h"
#include "extensions/filters/network/kafka/request_codec.h"
#include "extensions/filters/network/kafka/response_codec.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class KafkaMeshFilter : public Network::ReadFilter, private Logger::Loggable<Logger::Id::kafka> {
public:
  KafkaMeshFilter();

  // Network::ReadFilter
  Network::FilterStatus onNewConnection() override;
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override;
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;

  RequestDecoderSharedPtr getRequestDecoderForTest();
  ResponseDecoderSharedPtr getResponseDecoderForTest();

private:
  const ResponseDecoderSharedPtr response_decoder_;
  const RequestDecoderSharedPtr request_decoder_;
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
