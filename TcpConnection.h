#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Declare.h"
#include "IUser.h"
#include "IChannelCallBack.h"


#define MAX_BUF_SIZE 100

using namespace std;
class TcpConnection: public IChannelCallBack{
public:
    TcpConnection(EventLoop* loop, int socket_fd);
    ~TcpConnection(); 
    virtual void handle_event(int socket_fd);
    void send(const string& data);
    void set_user(IUser* user);
    void connectEstablish();
private:
    int _socket_fd;
    Channel* _channel;
    EventLoop* _loop;
    IUser* _user;
};
#endif // _TCP_CONNECTION_H_