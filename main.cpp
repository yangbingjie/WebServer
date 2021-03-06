#include <iostream>
#include "EventLoop.h"
#include "EchoServer.h"
using namespace std;

int main(){
    
    EventLoop eventloop;
    EchoServer server(&eventloop);
    server.start();
    eventloop.loop();
    return 0;
}