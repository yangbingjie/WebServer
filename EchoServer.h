#ifndef _ECHO_SERVER_H
#define _ECHO_SERVER_H
#include <iostream>
#include "Declare.h"
#include "TcpServer.h"
#include "IUser.h"
#include "IRun.h"

using namespace std;

class EchoServer : public IUser, public IRun{
public:
    EchoServer(EventLoop* loop);
    ~EchoServer();
    void start();
    virtual void onConnect(TcpConnection* connection);
    virtual void onMessage(TcpConnection* connection, Buffer* data);
    virtual void onWriteComplate(TcpConnection* connection);
    virtual void run(void* args);
private:
    EventLoop* _loop;
    TcpServer _server;
    long _timer;
    int _index;
};

#endif // _ECHO_SERVER_H