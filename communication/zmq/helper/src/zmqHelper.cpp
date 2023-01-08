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

std::string socketRecv(void *socket, uint buffSize = 256) {
  char *buffer = new char[buffSize];
  int size = zmq_recv(socket, buffer, buffSize - 1, 0);
  if (size == -1)
    return NULL;
  buffer[size < buffSize ? size : buffSize - 1] = '\0';
  std::string retStr(buffer);
  delete[] buffer;
  return retStr;
}
} // namespace

void send(void *socket, const std::string str, const std::string topic) {
  socketSendmore(socket, topic.c_str());
  socketSendmore(socket, std::to_string(str.size()).c_str());
  socketSend(socket, str.c_str());
}

std::string receive(void *socket) {
  //  Read envelope with address
  socketRecv(socket);
  //  Read message contents
  std::string dataSize = socketRecv(socket);
  return socketRecv(socket, std::stoi(dataSize));
}
} // namespace zmq_helper