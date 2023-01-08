#pragma once

#include <zmq.h>
#include <string>

namespace zmq_helper{

void send(void *socket, std::string str, std::string topic);
std::string receive(void *socket);

}