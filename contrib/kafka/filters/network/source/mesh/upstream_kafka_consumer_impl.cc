#include "contrib/kafka/filters/network/source/mesh/upstream_kafka_consumer_impl.h"

#include "contrib/kafka/filters/network/source/mesh/librdkafka_utils_impl.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Kafka {
namespace Mesh {

<<<<<<< HEAD
RichKafkaConsumer::RichKafkaConsumer(InboundRecordProcessor& record_processor,
                                     Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration)
    : RichKafkaConsumer(record_processor, thread_factory, topic, partition_count, configuration,
                        LibRdKafkaUtilsImpl::getDefaultInstance()){};

RichKafkaConsumer::RichKafkaConsumer(InboundRecordProcessor& record_processor,
=======
RichKafkaConsumer::RichKafkaConsumer(StoreCb& store_cb,
                                     Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration)
    : RichKafkaConsumer(store_cb, thread_factory, topic, partition_count, configuration,
                        LibRdKafkaUtilsImpl::getDefaultInstance()){};

RichKafkaConsumer::RichKafkaConsumer(StoreCb& store_cb,
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
                                     Thread::ThreadFactory& thread_factory,
                                     const std::string& topic, int32_t partition_count,
                                     const RawKafkaConfig& configuration,
                                     const LibRdKafkaUtils& utils)
<<<<<<< HEAD
    : record_processor_{record_processor}, topic_{topic} {
=======
    : store_cb_{store_cb}, topic_{topic} {
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)

  // Create consumer configuration object.
  std::unique_ptr<RdKafka::Conf> conf =
      std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));

  std::string errstr;

  // Setup consumer custom properties.
  for (const auto& e : configuration) {
    ENVOY_LOG(info, "Setting consumer property {}={}", e.first, e.second);
    if (utils.setConfProperty(*conf, e.first, e.second, errstr) != RdKafka::Conf::CONF_OK) {
      throw EnvoyException(absl::StrCat("Could not set consumer property [", e.first, "] to [",
                                        e.second, "]:", errstr));
    }
  }

<<<<<<< HEAD
  // We create the consumer.
=======
  // XXX
  if (utils.setConfProperty(*conf, "queued.max.messages.kbytes", "10", errstr) != RdKafka::Conf::CONF_OK) {
    throw EnvoyException(errstr);
  }
  if (utils.setConfProperty(*conf, "fetch.message.max.bytes", "1000", errstr) != RdKafka::Conf::CONF_OK) {
    throw EnvoyException(errstr);
  }

  // Finally, we create the producer.
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
  consumer_ = utils.createConsumer(conf.get(), errstr);
  if (!consumer_) {
    throw EnvoyException(absl::StrCat("Could not create consumer:", errstr));
  }
<<<<<<< HEAD

  // We assign all topic partitions to the consumer.
=======
  
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
  for (auto pt = 0; pt < partition_count; ++pt) {
    // We consume records from the beginning of each partition.
    const int64_t initial_offset = 0;
    const RdKafkaPartitionRawPtr topic_partition =
        RdKafka::TopicPartition::create(topic, pt, initial_offset);
    ENVOY_LOG(debug, "Assigning {}-{}", topic, pt);
    assignment_.push_back(topic_partition);
  }
  consumer_->assign(assignment_);

  // Start the poller thread.
  poller_thread_active_ = true;
  std::function<void()> thread_routine = [this]() -> void { pollContinuously(); };
  poller_thread_ = thread_factory.createThread(thread_routine);
}

RichKafkaConsumer::~RichKafkaConsumer() {
  ENVOY_LOG(debug, "Closing Kafka consumer [{}]", topic_);

  poller_thread_active_ = false;
  // This should take at most INTEREST_TIMEOUT_MS + POLL_TIMEOUT_MS.
  poller_thread_->join();

  consumer_->unassign();
  consumer_->close();
  RdKafka::TopicPartition::destroy(assignment_); // XXX

  ENVOY_LOG(debug, "Kafka consumer [{}] closed succesfully", topic_);
}

<<<<<<< HEAD
// How long a thread should wait for interest before checking if it's cancelled.
constexpr int32_t INTEREST_TIMEOUT_MS = 1000;

// How long a consumer should poll Kafka for messages.
constexpr int32_t POLL_TIMEOUT_MS = 1000;

// Large values are okay, but make the Envoy shutdown take longer
// (as there is no good way to interrupt a 'consume' call).
// XXX (adam.kotwasinski) This should be made configurable.

void RichKafkaConsumer::pollContinuously() {
  while (poller_thread_active_) {

    // It makes no sense to poll and receive records if there is no interest right now,
    // so we can just block instead.
    bool can_poll = record_processor_.waitUntilInterest(topic_, INTEREST_TIMEOUT_MS);
    if (!can_poll) {
      // There is nothing to do, so we keep checking again.
      // Also we happen to check if we were closed - this makes Envoy shutdown bit faster.
      continue;
    }

    // There is interest in messages present in this topic, so we can start polling.
    std::vector<InboundRecordSharedPtr> records = receiveRecordBatch();
    for (auto& record : records) {
      record_processor_.receive(record);
=======
void RichKafkaConsumer::pollContinuously() {
  while (poller_thread_active_) {
    if (store_cb_.hasInterest(topic_)) { // There should be a partition check here.
      std::vector<RdKafkaMessagePtr> kafka_messages = receiveMessageBatch();
      if (0 != kafka_messages.size()) {
        for (auto& kafka_message : kafka_messages) {
          store_cb_.receive(kafka_message);
        }
      }
    } else {
      // There's no interest in any messages, just sleep for now.
      std::this_thread::sleep_for(std::chrono::seconds(1)); // XXX this should not be a sleep, we should sleep on condition "there are callbacks"
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
    }
  }
  ENVOY_LOG(debug, "Poller thread for consumer [{}] finished", topic_);
}

<<<<<<< HEAD
// Helper method, gets rid of librdkafka.
static InboundRecordSharedPtr transform(std::unique_ptr<RdKafka::Message> arg) {
  auto topic = arg->topic_name();
  auto partition = arg->partition();
  auto offset = arg->offset();
  return std::make_shared<InboundRecord>(topic, partition, offset);
}
=======
const static int32_t BUFFER_DRAIN_VOLUME = 4;
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)

// How many records should be drained out of consumer in one go.
constexpr int32_t BUFFER_DRAIN_VOLUME = 4;

std::vector<InboundRecordSharedPtr> RichKafkaConsumer::receiveRecordBatch() {
  // This message kicks off librdkafka consumer's Fetch requests and delivers a message.
<<<<<<< HEAD
  auto message = std::unique_ptr<RdKafka::Message>(consumer_->consume(POLL_TIMEOUT_MS));
=======
  ENVOY_LOG(info, "fetch! {}", topic_);
  RdKafkaMessagePtr message = std::shared_ptr<RdKafka::Message>(consumer_->consume(1000));
>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
  switch (message->err()) {
  case RdKafka::ERR_NO_ERROR: {

<<<<<<< HEAD
    // We got a message.
    std::vector<InboundRecordSharedPtr> result;

    auto inbound_record = transform(std::move(message));
    ENVOY_LOG(trace, "Received Kafka message (first one): {}", inbound_record->toString());

    result.push_back(inbound_record);

    // We got a message, there could be something left in the buffer, so we try to drain it by
    // consuming without waiting. See: https://github.com/edenhill/librdkafka/discussions/3897
    while (result.size() < BUFFER_DRAIN_VOLUME) {
      auto buffered_message = std::unique_ptr<RdKafka::Message>(consumer_->consume(0));
      if (RdKafka::ERR_NO_ERROR == buffered_message->err()) {
        // There was a message in the buffer.
        auto inbound_buffered = transform(std::move(buffered_message));
        ENVOY_LOG(trace, "Received Kafka message (buffered): {}", inbound_buffered->toString());
        result.push_back(inbound_buffered);
      } else {
        // Buffer is empty / consumer is failing - there is nothing more to consume.
        break;
      }
    } // while

    return result;
  }
  case RdKafka::ERR__TIMED_OUT: {
    // Nothing extraordinary, there is nothing coming from upstream cluster.
    ENVOY_LOG(trace, "Timed out in [{}]", topic_);
    return {};
  }
  default: {
    ENVOY_LOG(trace, "Received other error in [{}]: {} / {}", topic_, message->err(),
              RdKafka::err2str(message->err()));
    return {};
  }
  } // switch
}

=======
      // We got a message, there could be something left in the buffer, so we try to drain it by
      // consuming without waiting. See: https://github.com/edenhill/librdkafka/discussions/3897
      while (result.size() < BUFFER_DRAIN_VOLUME) {
        int i = 0;
        RdKafkaMessagePtr buffered_message = std::unique_ptr<RdKafka::Message>(consumer_->consume(0));
        if (RdKafka::ERR_NO_ERROR == buffered_message->err()) {
          // There was a message in the buffer.
          ENVOY_LOG(info, "Received buffered message: {}-{}, offset={}", buffered_message->topic_name(), buffered_message->partition(), buffered_message->offset());
          result.push_back(buffered_message);
          i++;
        } else {
          ENVOY_LOG(info, "buffer drained! {}", i);
          // Buffer is empty / consumer is failing - there is nothing more to consume.
          break;
        }
      }
      return result;
    }
    case RdKafka::ERR__TIMED_OUT: {
      ENVOY_LOG(info, "Timed out in [{}]", topic_);
      return {};
    }
    default: {
      ENVOY_LOG(info, "Received other error: {} / {}", message->err(), RdKafka::err2str(message->err()));
      return {};
    }
  }
}

>>>>>>> 0b7aeca135 (kafka: move callback/undelivered message tracking to SCM)
} // namespace Mesh
} // namespace Kafka
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
