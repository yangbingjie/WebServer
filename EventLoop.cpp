#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include "TimerQueue.h"
EventLoop::EventLoop():_killed(false),
 _epoll(new Epoll()), // TODO Memory Leak
 _timer_queue(new TimerQueue(this)) // TODO Memory Leak
 {
    _eventfd = create_eventfd();
    _eventfd_channel = new Channel(this, _eventfd); // TODO Memory Leak
    _eventfd_channel->enable_read();
    _eventfd_channel->set_callback(this);
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
void EventLoop::queue_loop(IRun* run, void* arg){
    Runner r(run, arg);
    _pending_functors.push_back(r);
    wakeup();
}
void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t len = write(_eventfd, &one, sizeof(one));
    if (len != sizeof(one))
    {
        cout << "EventLoop::wakeup() write " << len << " bytes" << endl;
    }
}
void EventLoop::handle_read(){
    uint64_t one = 1;
    ssize_t len = read(_eventfd, &one, sizeof(one));
    if (len != sizeof(one))
    {
        cout << "EventLoop::handle_read() write " << len << " bytes" << endl;
    }
}
void EventLoop::handle_write(){
}
void EventLoop::run_pending_functors(){
    vector<Runner> tmp;
    tmp.swap(_pending_functors);
    vector<Runner>::iterator it;
    for (it = tmp.begin(); it != tmp.end();++it){
        it->do_run();
    }
}
long EventLoop::run_at(Timestamp when, IRun* run){
    return _timer_queue->add_timer(run, when, 0.0);
}
long EventLoop::run_after(double delay, IRun* run){
    return _timer_queue->add_timer(run, Timestamp::nowAfter(delay), 0.0);
}
long EventLoop::run_every(double interval, IRun* run){
    return _timer_queue->add_timer(run, Timestamp::nowAfter(interval), interval);
}
void EventLoop::cancel_timer(long timer_id){
    _timer_queue->cancel_timer(timer_id);
}
