#ifndef _ECHO_SERVER_H
#define _ECHO_SERVER_H
#include <iostream>
#include "Declare.h"
#include "TcpServer.h"
#include "IUser.h"

using namespace std;

class EchoServer : public IUser{
public:
    EchoServer(EventLoop* loop);
    ~EchoServer();
    void start();
    virtual void onConnect(TcpConnection* connection);
    virtual void onMessage(TcpConnection* connection, string* data);
private:
    EventLoop* _loop;
    TcpServer _server;
};

#endif // _ECHO_SERVER_H