#ifndef _MY_EPOLL_H_
#define _MY_EPOLL_H_
#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <errno.h>
#include "Declare.h"

#define MAX_EVENTS 100
using namespace std;

class Epoll{
public:
    Epoll();
    ~Epoll();
    void poll(vector<Channel*>*channel_array);
    void update(Channel* channel);
private:
    int _epoll_fd;
    struct epoll_event _events[MAX_EVENTS];
};

#endif // _EPOLL_H_