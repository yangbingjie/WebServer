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
#include "IRun.h"
#include "Buffer.h"
#include "IChannelCallBack.h"


#define MAX_BUF_SIZE 100

using namespace std;
class TcpConnection: public IChannelCallBack, public IRun{
public:
    TcpConnection(EventLoop* loop, int socket_fd);
    ~TcpConnection(); 
    virtual void run(void* args);
    virtual void handle_read();
    virtual void handle_write();
    void send(const string& data);
    void set_user(IUser* user);
    void connectEstablish();
private:
    int _socket_fd;
    Channel* _connect_channel;
    EventLoop* _loop;
    IUser* _user;
    Buffer _out_buffer;
    Buffer _in_buffer;
};
#endif // _TCP_CONNECTION_H_