#include "contrib/kafka/filters/network/source/mesh/command_handlers/fetch_record_converter.h"

#include "source/common/buffer/buffer_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

std::vector<FetchableTopicResponse> FetchRecordConverterImpl::convert(const INPUT&) const {

  // TODO (adam.kotwasinski) This needs to be actually implemented.
  return {};
}

const FetchRecordConverter& FetchRecordConverterImpl::getDefaultInstance() {
  CONSTRUCT_ON_FIRST_USE(FetchRecordConverterImpl);
}

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
