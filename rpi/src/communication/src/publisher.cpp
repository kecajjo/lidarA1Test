#include "zhelpers.h"
#include <unistd.h>
#include "pc2d.pb.h"

int main (void)
{
    MySuperStruct superStruct;
    superStruct.set_superstring("My Super Extra String");
    superStruct.set_superint(124);
    superStruct.set_superfloat(142.54);

    std::string serializedData;
    superStruct.SerializeToString(&serializedData);
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind (publisher, "tcp://*:5563");


    MySuperStruct superStructChanged;
    superStructChanged.set_superstring("You can see me!!!");
    superStructChanged.set_superint(1111111);
    superStructChanged.set_superfloat(457.43532);

    std::string serializedDataChanged;
    superStructChanged.SerializeToString(&serializedDataChanged);
    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, "A");
        char *tmp1 = const_cast<char *>(serializedData.c_str());
        s_send (publisher, tmp1);
        s_sendmore (publisher, "B");
        char* tmp2 = const_cast<char *>(serializedDataChanged.c_str());
        s_send (publisher, tmp2);
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}