#include "zmqHelper.hpp"
#include <unistd.h>
#include "TestMsg.pb.h"

int main (void)
{
    TestMsg superStruct;
    superStruct.set_d(14.643);
    superStruct.set_u(124);
    superStruct.set_i(-142);

    std::string serializedData;
    superStruct.SerializeToString(&serializedData);
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind (publisher, "tcp://localhost:5563");


    MySuperStruct superStructChanged;
    superStructChanged.set_d(-14.643);
    superStructChanged.set_u(4);
    superStructChanged.set_i(-2);

    std::string serializedDataChanged;
    superStructChanged.SerializeToString(&serializedDataChanged);
    while (1) {
        //  Write two messages, each with an envelope and content
        zmq_helper::send(publisher, serializedData, "A");
        zmq_helper::send(publisher, serializedDataChanged, "B");
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}