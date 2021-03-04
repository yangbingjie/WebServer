#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
EventLoop::EventLoop():_killed(false), _epoll(new Epoll()){// TODO Memory Leak
    _event_fd = create_eventfd();
}
EventLoop::~EventLoop(){

}
int EventLoop::create_eventfd(){
    int event_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(event_fd < 0){
        cout << "Eventfd create error" << endl;
    }
    return event_fd;
}
void EventLoop::loop(){
    while (!_killed){
        vector<Channel*>channel_array;
        _epoll->poll(&channel_array);
        vector<Channel*>::iterator iter;
        for(iter = channel_array.begin(); iter != channel_array.end(); ++iter){
            (*iter)->handle_event();            
        }
        run_pending_functors();
    }
}
void EventLoop::update(Channel* channel){
    _epoll->update(channel);
}
void EventLoop::queue_loop(IRun* run){
    _pending_functors.push_back(run);
    wakeup();
}
void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t len = write(_event_fd, &one, sizeof(one));
    if (len != sizeof(one))
    {
        cout << "EventLoop::wakeup() write " << len << " bytes" << endl;
    }
}
void EventLoop::handle_read(){
    uint64_t one = 1;
    ssize_t len = read(_event_fd, &one, sizeof(one));
    if (len != sizeof(one))
    {
        cout << "EventLoop::handle_read() write " << len << " bytes" << endl;
    }
}
void EventLoop::handle_write(){
}
void EventLoop::run_pending_functors(){
    vector<IRun*> tmp;
    tmp.swap(_pending_functors);
    vector<IRun*>::iterator it;
    for (it = tmp.begin(); it != tmp.end();++it){
        (*it)->run();
    }
}