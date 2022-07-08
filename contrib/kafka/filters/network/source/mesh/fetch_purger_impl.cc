#include "contrib/kafka/filters/network/source/mesh/fetch_purger_impl.h"

#include <thread>

#include "envoy/event/dispatcher.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// ThreadLocalFetchPurger

class ThreadLocalFetchPurger : public FetchPurger, public ThreadLocal::ThreadLocalObject, private Logger::Loggable<Logger::Id::kafka> {
public:
    ThreadLocalFetchPurger(Event::Dispatcher& dispatcher);

    Event::TimerPtr track(/* tmp */ int32_t id, int32_t timeout) override;

    void boom(/* tmp */ int32_t id);
private:
    Event::Dispatcher& dispatcher_;
};

ThreadLocalFetchPurger::ThreadLocalFetchPurger(Event::Dispatcher& dispatcher): dispatcher_{dispatcher} {
    ENVOY_LOG(info, "ThreadLocalFetchPurger ctor in {}", std::this_thread::get_id());
}

Event::TimerPtr ThreadLocalFetchPurger::track(/* tmp */ int32_t id, int32_t timeout) {
    ENVOY_LOG(info, "TLFP tracking rq {} in {}", id, std::this_thread::get_id());

    auto callback = [this, id]() -> void { 
      ENVOY_LOG(info, "callback for {}", id);
    };
    auto event = dispatcher_.createTimer(callback);
    event->enableTimer(std::chrono::milliseconds(timeout));
    return event;
};

// FetchPurger

FetchPurgerImpl::FetchPurgerImpl(ThreadLocal::SlotAllocator& slot_allocator): tls_{slot_allocator.allocateSlot()} {
    ENVOY_LOG(info, "FetchPurgerImpl ctor in {}", std::this_thread::get_id());

    ThreadLocal::Slot::InitializeCb cb =
      [](Event::Dispatcher& dispatcher) -> ThreadLocal::ThreadLocalObjectSharedPtr { return std::make_shared<ThreadLocalFetchPurger>(dispatcher); };
    tls_->set(cb);
}

Event::TimerPtr FetchPurgerImpl::track(/* tmp */ int32_t id, int32_t timeout) {
    ENVOY_LOG(info, "FPI tracking rq {} in {}", id, std::this_thread::get_id());
    return tls_->getTyped<ThreadLocalFetchPurger>().track(id, timeout);
};


} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy