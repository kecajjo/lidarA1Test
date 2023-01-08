#pragma once

#include <zmq.h>
#include <string>

namespace zmq_helper{

void send(void *socket, const std::string str, const std::string topic);
std::string receive(void *socket);

}