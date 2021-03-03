#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <vector>
#include <map>
#include "Acceptor.h"
#include "TcpConnection.h"
using namespace std;

class TcpServer : public IAcceptorCallBack{
public:
    TcpServer();
    ~TcpServer();
    void start();
    int create_socket();
    virtual void newConnection(int connect_fd);
private:
    int _epoll_fd;
    int _listen_fd;
    struct epoll_event _events[MAX_EVENTS];
    map<int, TcpConnection*> _connections;
    Acceptor* _acceptor;
};
#endif // _TCP_SERVER_H_