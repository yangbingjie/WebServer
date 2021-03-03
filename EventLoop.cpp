#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
EventLoop::EventLoop():_killed(false), _epoll(new Epoll()){// TODO Memory Leak

}
EventLoop::~EventLoop(){

}
void EventLoop::loop(){
    while (!_killed){
        vector<Channel*>channel_array;
        _epoll->poll(&channel_array);
        vector<Channel*>::iterator iter;
        for(iter = channel_array.begin(); iter != channel_array.end(); ++iter){
            (*iter)->handle_event();            
        }
    }
}
void EventLoop::update(Channel* channel){
    _epoll->update(channel);
}