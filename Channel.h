#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <fcntl.h>
#include <iostream>
#include <sys/epoll.h>

#include "IChannelCallBack.h"

class Channel{
public:
    Channel(int epoll_fd, int socket_fd);
    ~Channel();
    void handle_events();
    void enable_read();
    void set_callback(IChannelCallBack* callback){
        _callbacks = callback;
    }
    void set_revents(int revents){
        _revents = revents;
    }
private:
    void update();
    int _epoll_fd;
    int _socket_fd;
    int _events; // requested event
    int _revents; // returned events
    IChannelCallBack* _callbacks;
};

#endif // _CHANNEL_H_