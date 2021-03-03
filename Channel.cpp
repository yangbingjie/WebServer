#include "Channel.h"
#include "EventLoop.h"
Channel::Channel(EventLoop* loop, int socket_fd):_loop(loop), _socket_fd(socket_fd),_events(0),_revents(0), _callbacks(NULL){

}
Channel::~Channel(){

}
void Channel::handle_event(){
    if(_revents & EPOLLIN){
        _callbacks->handle_event(_socket_fd);
    }
}
void Channel::enable_read(){
    _events |= EPOLLIN;
    update();
}
void Channel::update(){
    _loop->update(this);
}