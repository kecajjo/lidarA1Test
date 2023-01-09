#include "publisher.hpp"
#include <unistd.h>
#include "TestMsg.pb.h"

int main (void)
{
    TestMsg superStruct;
    superStruct.set_d(14.643);
    superStruct.set_u(124);
    superStruct.set_i(-142);
    auto aPub = zmq_helper::Publisher<TestMsg>("ipc:///tmp/0");
    TestMsg superStructChanged;
    superStructChanged.set_d(-14.643);
    superStructChanged.set_u(4);
    superStructChanged.set_i(-2);

    while (1) {
        //  Write two messages, each with an envelope and content
        aPub.publish(superStruct, "A");
        aPub.publish(superStructChanged, "B");
        sleep (1);
    }
    return 0;
}
