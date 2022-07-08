#include "contrib/kafka/filters/network/source/mesh/fetch_purger_impl.h"

#include <thread>

#include "envoy/event/dispatcher.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

class ThreadLocalFetchPurger : public FetchPurger, public ThreadLocal::ThreadLocalObject, private Logger::Loggable<Logger::Id::kafka> {
public:
    ThreadLocalFetchPurger(Event::Dispatcher& dispatcher);

    Event::TimerPtr track(Event::TimerCb callback, int32_t timeout) override;
private:
    Event::Dispatcher& dispatcher_;
};

ThreadLocalFetchPurger::ThreadLocalFetchPurger(Event::Dispatcher& dispatcher): dispatcher_{dispatcher} {
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    ENVOY_LOG(info, "ThreadLocalFetchPurger ctor in {}", oss.str());
}

Event::TimerPtr ThreadLocalFetchPurger::track(Event::TimerCb callback, int32_t timeout) {
    auto event = dispatcher_.createTimer(callback);
    event->enableTimer(std::chrono::milliseconds(timeout));
    return event;
};

FetchPurgerImpl::FetchPurgerImpl(ThreadLocal::SlotAllocator& slot_allocator): tls_{slot_allocator.allocateSlot()} {
    ThreadLocal::Slot::InitializeCb cb =
      [](Event::Dispatcher& dispatcher) -> ThreadLocal::ThreadLocalObjectSharedPtr { return std::make_shared<ThreadLocalFetchPurger>(dispatcher); };
    tls_->set(cb);
}

Event::TimerPtr FetchPurgerImpl::track(Event::TimerCb callback, int32_t timeout) {
    return tls_->getTyped<ThreadLocalFetchPurger>().track(callback, timeout);
};

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy