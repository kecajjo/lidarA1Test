#include "subscriber.hpp"
#include "TestMsg.pb.h"

void callback(std::unique_ptr<TestMsg> msg){
    printf ("%lf %d %u\n", msg->d(), msg->i(), msg->u());
}

int main (void)
{

    auto sub = zmq_helper::Subscriber<TestMsg>("tcp://192.168.0.157:5555", "B", callback);
    while(1){
        ;
    }
    return 0;
}