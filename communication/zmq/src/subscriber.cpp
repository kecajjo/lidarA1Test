#include "zmqHelper.hpp"
#include "TestMsg.pb.h"

int main (void)
{
    //  Prepare our context and subscriber
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:5563");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "B", 1);

    while (1) {
        std::string contents = zmq_helper::receive(subscriber)
        MySuperStruct superStruct;
        superStruct.ParseFromString(contents);
        printf ("%d %i %u\n", superStruct.d(), superStruct.i(), superStruct.u());
    }
    //  We never get here, but clean up anyhow
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}