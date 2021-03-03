#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_
#include "IChannelCallBack.h"

class EventHandler : public IAcceptorCallBack{
public:
    EventHandler(int epoll_fd):_epoll_fd(epoll_fd){}
    virtual void handle_event(int socket_fd){};
    ~EventHandler(){}
private:
    int _epoll_fd;
};

#endif // _EVENT_HANDLER_H_