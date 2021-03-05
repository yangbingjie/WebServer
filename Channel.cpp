#include "Channel.h"
#include "EventLoop.h"
Channel::Channel(EventLoop* loop, int fd):_loop(loop),
 _fd(fd),_events(0),_revents(0), _callbacks(NULL), _index(-1){
}
Channel::~Channel(){

}
void Channel::handle_event(){
    if(_revents & EPOLLIN){
        _callbacks->handle_read();
    }else if (_revents & EPOLLOUT){
        _callbacks->handle_write();
    }
}
void Channel::enable_read(){
    _events |= EPOLLIN;
    update();
}
void Channel::update(){
    _loop->update(this);
}
bool Channel::is_writing(){
    return _events & EPOLLOUT;
}
void Channel::disable_write(){
    _events &= ~EPOLLOUT;
    update();
}
void Channel::enable_write(){
    _events |= EPOLLOUT;
    update();
}
void Channel::set_index(int index){
    _index = index;
}
int Channel::get_index(){return _index;}