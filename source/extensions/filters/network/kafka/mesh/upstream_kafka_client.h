#pragma once

#include "common/common/logger.h"

#include "envoy/event/dispatcher.h"

#include "librdkafka/rdkafkacpp.h"

#include <thread>
#include <deque>

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

// Trivial memento that keeps the information about how given request was delivered:
// in case of success this means offset (if acks > 0), or error code.
struct DeliveryMemento {

  // Pointer to byte array that was passed to Kafka producer.
  // This is used to find the original
  // Important: we do not free this memory, it's still part of the 'Request' object two levels above.
  const void* data_;

  // Kafka producer error code.
  const RdKafka::ErrorCode error_code_;

  // Offset (only meaningful if ec == 0).
  const int64_t offset_;
};

class ProduceFinishCb {
public:

  virtual ~ProduceFinishCb() = default;

  virtual bool accept(const DeliveryMemento& memento) PURE;

};

using ProduceFinishCbSharedPtr = std::shared_ptr<ProduceFinishCb>;

class KafkaProducerWrapper: public RdKafka::DeliveryReportCb, private Logger::Loggable<Logger::Id::kafka> {
public:

  KafkaProducerWrapper(Event::Dispatcher& dispatcher, Thread::ThreadFactory& thread_factory, const std::string& bootstrap_servers);

  /**
   * Submits given payload to be sent to given topic:partition.
   * If successful, after successful delivery 'dr_cb' method will be invoked by separate thread (via prod
   *
   * @param origin origin of payload to be notified when
   */
  RdKafka::ErrorCode send(const ProduceFinishCbSharedPtr origin, const std::string& topic, const int32_t partition, const absl::string_view key, const absl::string_view value);

  void processDelivery(const DeliveryMemento& memento);

  void checkDeliveryReports();

  // RdKafka::DeliveryReportCb
  void dr_cb(RdKafka::Message& message);

private:
  ProduceFinishCbSharedPtr getMatching(const RdKafka::Message& message);

  Event::Dispatcher& dispatcher_;

  std::list<ProduceFinishCbSharedPtr> unfinished_produce_requests_;

  // Real Kafka producer (thread-safe).
  // Invoked by Envoy handler thread (to produce), and internal poller (to poll for delivery events).
  std::unique_ptr<RdKafka::Producer> producer_;

  // Separate that's responsible for continuously polling for new Kafka producer events, until it is stopped.
  // Polling results in invoking 'dr_cb' method.
  Thread::ThreadPtr poller_thread_;
};

using KafkaProducerWrapperPtr = std::unique_ptr<KafkaProducerWrapper>;

} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
