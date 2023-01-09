#include "zmqHelper.hpp"
#include <cstring>

namespace zmq_helper {
namespace {

int socketSend(void *socket, const char *string) {
  int size = zmq_send(socket, string, strlen(string), 0);
  return size;
}

int socketSendmore(void *socket, const char *string) {
  int size = zmq_send(socket, string, strlen(string), ZMQ_SNDMORE);
  return size;
}

std::optional<std::string> socketRecv(void *socket, uint buffSize = 256) {
  char *buffer = new char[buffSize];
  int size = zmq_recv(socket, buffer, buffSize - 1, 0);
  if (size == -1)
    return std::nullopt;
  buffer[size < buffSize ? size : buffSize - 1] = '\0';
  std::optional<std::string> retStr(buffer);
  delete[] buffer;
  return retStr;
}
} // namespace

void send(void *socket, const std::string str, const std::string topic) {
  socketSendmore(socket, topic.c_str());
  socketSendmore(socket, std::to_string(str.size()).c_str());
  socketSend(socket, str.c_str());
}

std::optional<std::string> receive(void *socket) {
  //  Read envelope with address
  if (!socketRecv(socket)){
    return std::nullopt;
  }
  auto dataSize = socketRecv(socket);
  if (!dataSize)
    return std::nullopt;
  return socketRecv(socket, std::stoi(dataSize.value()));
}
} // namespace zmq_helper