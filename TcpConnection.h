#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "Declare.h"
#include "IChannelCallBack.h"


#define MAX_BUF_SIZE 100

using namespace std;
class TcpConnection: public IChannelCallBack{
public:
    TcpConnection(EventLoop* loop, int socket_fd);
    ~TcpConnection(); 
    virtual void handle_event(int socket_fd);
private:
    int _socket_fd;
    Channel* _channel;
    EventLoop* _loop;
};
#endif // _TCP_CONNECTION_H_