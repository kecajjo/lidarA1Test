#include "publisher.hpp"
#include "TestMsg.pb.h"
#include <unistd.h>

int main(void) {
  TestMsg superStruct;
  superStruct.set_d(14.643);
  superStruct.set_u(124);
  for (int i = 0; i < 5; i++) {
    auto *ray = superStruct.add_i();
    ray->set_i(i);
  }
  auto aPub = zmq_helper::Publisher<TestMsg>("tcp://*:5555");
  TestMsg superStructChanged;
  superStructChanged.set_d(-14.643);
  superStructChanged.set_u(4);
  for (int i = 0; i < 5; i++) {
    auto *ray = superStructChanged.add_i();
    ray->set_i(i);
  }
  std::cout << superStructChanged.i(2).i() <<std::endl;

  while (1) {
    //  Write two messages, each with an envelope and content
    aPub.publish(superStruct, "A");
    aPub.publish(superStructChanged, "B");
    sleep(1);
  }
  return 0;
}
