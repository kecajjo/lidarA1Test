#include "zmqHelper.hpp"
#include <string>

namespace zmq_helper {
template <class T> class Publisher {
public:
  Publisher(const std::string address) {
    context = zmq_ctx_new();
    publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, address.c_str());
  }

  ~Publisher() {
    zmq_close(publisher);
    zmq_ctx_destroy(context);
  }

  void publish(const T data, const std::string topic) const{
    std::string serializedData;
    data.SerializeToString(&serializedData);
    send(publisher, serializedData, topic);
  }

private:
  void *context;
  void *publisher;
};
} // namespace zmq_helper