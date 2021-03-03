#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_
#include <string.h>

class TcpConnection: public EventHandler{
public:
    TcpConnection(int epoll_fd, int socket_fd);
    ~TcpConnection(); 
    virtual void handle_event();
private:
    int _socket_fd;
    Channel* _channel;
};
#endif // _TCP_CONNECTION_H_