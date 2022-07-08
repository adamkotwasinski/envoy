#pragma once

#include "contrib/kafka/filters/network/source/mesh/fetch_purger.h"

#include "envoy/thread_local/thread_local.h"

#include "source/common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchPurgerImpl : public FetchPurger, private Logger::Loggable<Logger::Id::kafka> {
public:
    FetchPurgerImpl(ThreadLocal::SlotAllocator& slot_allocator);

    Event::TimerPtr track(/* tmp */ int32_t id, int32_t timeout) override;

private:
    ThreadLocal::SlotPtr tls_;

};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy