#ifndef _ECHO_SERVER_H
#define _ECHO_SERVER_H
#include <iostream>
#include "Declare.h"
#include "TcpServer.h"
#include "IUser.h"
#include "IRun.h"
#include "ThreadPool.h"


using namespace std;

class EchoServer : public IUser, public IRun2, public IRun0{
public:
    EchoServer(EventLoop* loop);
    ~EchoServer();
    void start();
    virtual void onConnect(TcpConnection* connection);
    virtual void onMessage(TcpConnection* connection, Buffer* data);
    virtual void onWriteComplate(TcpConnection* connection);
    virtual void run2(const string& str, void* tcp);
    virtual void run0();
    int fib(int n);
private:
    EventLoop* _loop;
    TcpServer _server;
    long _timer;
    int _index;
    ThreadPool _thread_pool;
};

#endif // _ECHO_SERVER_H