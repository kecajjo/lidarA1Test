#include "zmqHelper.hpp"
#include <cstring>
#include <iostream>

namespace zmq_helper {
namespace {

int socketSend(void *socket, const char *string, uint len) {
  int size = zmq_send(socket, string, len, 0);
  return size;
}

int socketSendmore(void *socket, const char *string, uint len) {
  int size = zmq_send(socket, string, len, ZMQ_SNDMORE);
  return size;
}

std::optional<std::string> socketRecv(void *socket) {
  char *buffer = new char[256];
  int size = zmq_recv(socket, buffer, 256 - 1, 0);
  if (size == -1)
    return std::nullopt;
  buffer[size < 256 ? size : 256 - 1] = '\0';
  std::optional<std::string> retStr(buffer);
  delete[] buffer;
  return retStr;
}
std::optional<std::string> socketRecv(void *socket, uint buffSize) {
  char *buffer = new char[buffSize+1];
  int size = zmq_recv(socket, buffer, buffSize, 0);
  if (size == -1)
    return std::nullopt;
  buffer[size < buffSize+1 ? size : buffSize] = '\0';
  std::optional<std::string> retStr(std::string(buffer, buffSize));
  std::cout << "size: " << retStr.value().size() << std::endl;
  delete[] buffer;
  return retStr;
}
} // namespace

void send(void *socket, const std::string str, const std::string topic) {
  socketSendmore(socket, topic.c_str(), topic.size());
  socketSendmore(socket, std::to_string(str.size()).c_str(), std::to_string(str.size()).size());
  socketSend(socket, str.c_str(), str.size());
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