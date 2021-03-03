#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "Channel.h"

#define MAX_BUF_SIZE 100

using namespace std;
class TcpConnection: public IChannelCallBack{
public:
    TcpConnection(int epoll_fd, int socket_fd);
    ~TcpConnection(); 
    virtual void handle_event(int socket_fd);
private:
    int _epoll_fd;
    int _socket_fd;
    Channel* _channel;
};
#endif // _TCP_CONNECTION_H_