#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <vector>
#include <map>
#include <iostream>
#include "Declare.h"
#include "IAcceptorCallBack.h"
using namespace std;

class TcpServer : public IAcceptorCallBack{
public:
    TcpServer(EventLoop* loop);
    ~TcpServer();
    void start();
    int create_socket();
    virtual void newConnection(int connect_fd);
private:
    map<int, TcpConnection*> _connections;
    Acceptor* _acceptor;
    EventLoop* _loop;
};
#endif // _TCP_SERVER_H_