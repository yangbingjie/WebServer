#include "Epoll.h"
#include "Channel.h"
Epoll::Epoll(){
    _epoll_fd = epoll_create(1);
    if (_epoll_fd < 0){
        cout << "Epoll create error: " << errno << endl;
    }
}
Epoll::~Epoll(){}
void Epoll::poll(vector<Channel*>*channel_array){
    int fds = epoll_wait(_epoll_fd, _events, MAX_EVENTS , -1);
    if (fds == -1){
        cout << "Epoll wait error: " << errno << endl;
    }
    for(int i = 0; i < fds; ++i){
        Channel * pChannel = static_cast<Channel*>(_events[i].data.ptr);
        pChannel->set_revents(_events[i].events);
        channel_array->push_back(pChannel);
    }
}
void Epoll::update(Channel* channel){
    struct epoll_event ev;
    ev.data.ptr = channel;
    ev.events = channel->get_event();
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, channel->get_socket(), &ev);
}