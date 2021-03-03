#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <unistd.h>
#include <fstream>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include "Channel.h"
using namespace std;

#define PORT 6978
#define MAX_LISTEN 10
#define MAX_BUF_SIZE 100
#define MAX_EVENTS 100
class TcpServer {
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