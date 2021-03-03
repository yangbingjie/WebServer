#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_
#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include "Channel.h"
#include "IChannelCallBack.h"
#include "IAcceptorCallBack.h"

#define PORT 6978
#define MAX_LISTEN 10
#define MAX_EVENTS 100
using namespace std;
class Acceptor: public IChannelCallBack{
public:
    Acceptor(int epoll_fd);
    ~Acceptor();
    virtual void handle_event(int socket_fd);
    void start();
    int create_socket();
    void set_callback(IAcceptorCallBack* callback);
private:
    int _epoll_fd;
    int _listen_fd;
    Channel* _channel;
    IAcceptorCallBack* _callbacks;
};
#endif // _ACCEPTOR_H_