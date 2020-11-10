#include "extensions/filters/network/kafka/mesh/command_handlers/api_versions.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {
namespace {

class MockAbstractRequestListener : public AbstractRequestListener {
public:
  MOCK_METHOD(void, onRequest, (InFlightRequestSharedPtr));
  MOCK_METHOD(void, onRequestReadyForAnswer, ());
};

class MockUpstreamKafkaFacade : public UpstreamKafkaFacade {
public:
  MOCK_METHOD(RichKafkaProducer&, getProducerForTopic, (const std::string&));
};

TEST(ApiVersionsTest, shouldBeAlwaysReadyForAnswer) {
  // given
  MockAbstractRequestListener filter;
  EXPECT_CALL(filter, onRequestReadyForAnswer());
  const RequestHeader header = {0, 0, 0, absl::nullopt};
  const ApiVersionsRequest data = {};
  const auto message = std::make_shared<Request<ApiVersionsRequest>>(header, data);
  ApiVersionsRequestHolder testee = {filter, message};

  // when, then - invoking should immediately notify the filter.
  MockUpstreamKafkaFacade upstream_kafka_facade;
  testee.invoke(upstream_kafka_facade);

  // when, then - should always be considered finished.
  const bool finished = testee.finished();
  EXPECT_TRUE(finished);

  // when, then - the computed result is always contains correct data (confirmed by integration
  // tests).
  const auto answer = testee.computeAnswer();
  EXPECT_EQ(answer->metadata_.api_key_, header.api_key_);
  EXPECT_EQ(answer->metadata_.correlation_id_, header.correlation_id_);
}

} // namespace
} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
