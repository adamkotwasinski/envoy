#include "source/extensions/filters/network/kafka/mesh/command_handlers/api_versions.h"

#include "source/extensions/filters/network/kafka/external/requests.h"
#include "source/extensions/filters/network/kafka/external/responses.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// These constants define which versions of requests this "Kafka server" will understand.

// As we can process only record format 2 (which itself is pretty old coming from Kafka 1.0), we are going to handle only produce requests with versions higher than 5.
constexpr int16_t MIN_PRODUCE_SUPPORTED = 5;
constexpr int16_t MAX_PRODUCE_SUPPORTED = PRODUCE_REQUEST_MAX_VERSION; /* Generated value. */
// Metadata v1 was introduced at the same time as Produce v5, so let's use them together.
constexpr int16_t MIN_METADATA_SUPPORTED = 1;
constexpr int16_t MAX_METADATA_SUPPORTED = METADATA_REQUEST_MAX_VERSION; /* Generated value. */

ApiVersionsRequestHolder::ApiVersionsRequestHolder(
    AbstractRequestListener& filter, const std::shared_ptr<Request<ApiVersionsRequest>> request)
    : BaseInFlightRequest{filter}, request_{request} {}

// Api Versions requests are immediately ready for answer (as they do not need to reach upstream).
void ApiVersionsRequestHolder::startProcessing() { notifyFilter(); }

// Because these requests can be trivially handled, they are okay to be sent downstream at any time.
bool ApiVersionsRequestHolder::finished() const { return true; }

AbstractResponseSharedPtr ApiVersionsRequestHolder::computeAnswer() const {
  const auto& header = request_->request_header_;
  const ResponseMetadata metadata = {header.api_key_, header.api_version_, header.correlation_id_};

  const int16_t error_code = 0;
  const ApiVersionsResponseKey produce_entry = {PRODUCE_REQUEST_API_KEY, MIN_PRODUCE_SUPPORTED, MAX_PRODUCE_SUPPORTED};
  const ApiVersionsResponseKey metadata_entry = {METADATA_REQUEST_API_KEY, MIN_METADATA_SUPPORTED, MAX_METADATA_SUPPORTED};
  const ApiVersionsResponse real_response = {error_code, {produce_entry, metadata_entry}};

  return std::make_shared<Response<ApiVersionsResponse>>(metadata, real_response);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
