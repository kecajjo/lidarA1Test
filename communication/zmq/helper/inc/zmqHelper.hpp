#pragma once

#include <zmq.h>
#include <string>
#include <optional>

namespace zmq_helper{

void send(void *socket, const std::string str, const std::string topic);
std::optional<std::string> receive(void *socket);

}