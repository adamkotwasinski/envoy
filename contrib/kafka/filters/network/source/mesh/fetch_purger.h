#pragma once

#include <memory>

#include "envoy/common/pure.h"

#include "envoy/event/timer.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class FetchPurger {
public:
    virtual ~FetchPurger() = default;

    virtual Event::TimerPtr track(Event::TimerCb callback, int32_t timeout) PURE;
};

using FetchPurgerSharedPtr = std::shared_ptr<FetchPurger>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy