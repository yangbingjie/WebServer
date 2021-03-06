#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <iostream>
#include <sys/epoll.h>
#include "IChannelCallBack.h"
#include "Declare.h"

class Channel{
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();
    void handle_event();
    void enable_read();
    void set_callback(IChannelCallBack* callback){
        _callbacks = callback;
    }
    void set_revents(int revents){
        _revents = revents;
    }
    int get_event(){return _events;}
    int get_fd(){return _fd;}
    void update();
    bool is_writing();
    void disable_write();
    void enable_write();
    void set_index(int index);
    int get_index();
private:
    int _fd;
    int _events; // requested event
    int _revents; // returned events
    IChannelCallBack* _callbacks;
    EventLoop* _loop;
    int _index;
};

#endif // _CHANNEL_H_