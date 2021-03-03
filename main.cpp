#include <iostream>
#include "EventLoop.h"
#include "TcpServer.h"
using namespace std;

int main(){
    EventLoop eventloop;
    TcpServer tcpServer(&eventloop);
    tcpServer.start();
    eventloop.loop();
    return 0;
}