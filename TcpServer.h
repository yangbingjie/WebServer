#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <unistd.h>
#include <fstream>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include "Channel.h"
using namespace std;

#define PORT 6978
#define MAX_LISTEN 10
#define MAX_BUF_SIZE 100
#define MAX_EVENTS 100
class TcpServer: public IChannelCallBack{
public:
    TcpServer();
    ~TcpServer();
    void start();
    int create_socket();
    virtual void handle_events(int socket_fd);
private:
    int _epoll_fd;
    int _listen_fd;
    struct epoll_event _events[MAX_EVENTS];
};
#endif // _TCP_SERVER_H_