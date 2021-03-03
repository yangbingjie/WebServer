#include "Channel.h"

Channel::Channel(int epoll_fd, int socket_fd):_epoll_fd(epoll_fd),
 _socket_fd(socket_fd),_events(0),_revents(0), _callbacks(NULL){

}
Channel::~Channel(){

}
void Channel::handle_events(){
    if(_revents & EPOLLIN){
        _callbacks->handle_events(_socket_fd);
    }
}
void Channel::enable_read(){
    _events |= EPOLLIN;
    update();
}
void Channel::update(){
    struct epoll_event ev;
    ev.data.ptr = this;
    ev.events = _events;
    epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _socket_fd, &ev);
}