#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_
#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "IChannelCallBack.h"
#include "IAcceptorCallBack.h"
#include "Declare.h"

#define PORT 6978
#define MAX_LISTEN 10 
using namespace std;
class Acceptor: public IChannelCallBack{
public:
    Acceptor(EventLoop* loop);
    ~Acceptor();
    virtual void handle_read();
    virtual void handle_write();
    void start();
    int create_socket();
    void set_callback(IAcceptorCallBack* callback);
private:
    int _listen_fd;
    Channel* _channel;
    IAcceptorCallBack* _callbacks;
    EventLoop* _loop;
};
#endif // _ACCEPTOR_H_