#include "zmqHelper.hpp"
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <atomic>

namespace zmq_helper {
template <class T> class Subscriber {
public:
  Subscriber(const std::string address, const std::string topic,
             const std::function<void(std::unique_ptr<T>)> callback)
      : t{callback_wrapper, std::ref(stop), address, topic, callback} {
      }
  ~Subscriber(){
    stop = true;
    t.join();
  }

private:
  std::atomic<bool> stop = false;
  std::thread t;

  static void
  callback_wrapper(std::atomic<bool>& stop, const std::string address,
                   const std::string topic,
                   const std::function<void(std::unique_ptr<T>)> callback) {
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int32_t timeout_ms = 100;
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, topic.c_str(), 1);
    zmq_setsockopt(subscriber, ZMQ_RCVTIMEO, &timeout_ms, sizeof(timeout_ms));
    size_t s = sizeof(timeout_ms);
    zmq_connect(subscriber, address.c_str());
    while (!stop) {
      std::optional<std::string> serializedData = receive(subscriber);
      if (!serializedData){
        continue;
      }
      std::unique_ptr<T> data = std::make_unique<T>();
      data->ParseFromString(serializedData.value());
      callback(std::move(data));
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
  }
};
} // namespace zmq_helper