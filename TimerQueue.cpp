#include <sys/timerfd.h>
#include <string.h>
#include <inttypes.h>
#include <iostream>
#include "TimerQueue.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Timestamp.h"
#define UINTPOINT_MAX 0xffffffff

TimerQueue::TimerQueue(EventLoop* loop)
:_loop(loop), _timefd(create_timerfd()),
 _add_timer_wrapper(new AddTimerWrapper(this)), // TODO Memory Leak
 _cancel_timer_wrapper(new CancelTimerWrapper(this)),
 _timefd_channel(new Channel(_loop, _timefd)) // TODO Memory Leak
{
    _timefd_channel->set_callback(this);
    _timefd_channel->enable_read();
}
TimerQueue::~TimerQueue(){
    close(_timefd);
}
long TimerQueue::add_timer(IRun* run, Timestamp when, double interval){
    Timer* timer = new Timer(run, when, interval); // TODO Memory Leak
    _loop->queue_loop(_add_timer_wrapper, timer);
    return (long)timer; // return the address of timer object
}
void TimerQueue::do_add_timer(void* args){
    Timer* timer = static_cast<Timer*>(args);
    if (insert(timer))
    {
        reset_timerfd(_timefd, timer->get_timestamp());
    }
}
void TimerQueue::cancel_timer(long timer_id){
    _loop->queue_loop(_cancel_timer_wrapper, (void*)timer_id);
}
void TimerQueue::do_cancel_timer(void* args){
    Timer* timer = static_cast<Timer*>(args);
    for(auto iter = _time_list.begin(); iter != _time_list.end(); ++iter){
        if(iter->second == timer){
            _time_list.erase(iter);
            return;
        }
    }
    // cout << "Can not find timer " << timer->get_timestamp().to_string() << endl;
}
bool TimerQueue::insert(Timer* timer){
    bool is_first_timer = false;
    Timestamp when = timer->get_timestamp();
    if (_time_list.empty() || when < _time_list.begin()->first)
    {
        is_first_timer = true;
    }
    auto iter = _time_list.insert(TimePair(when, timer));
    if (!iter.second)
    {
        cout << "time_list insert error" << endl;
    }
    return is_first_timer;
}
int TimerQueue::create_timerfd(){
    int timefd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (timefd < 0) {
        cout << "timefd creation error" << endl;
    }
    return timefd;
}
void TimerQueue::reset_timerfd(int timerfd, Timestamp timestamp){
    struct itimerspec new_val;
    struct itimerspec old_val;
    bzero(&old_val, sizeof(old_val));
    bzero(&new_val, sizeof(new_val));
    new_val.it_value = TimerQueue::time_from_now(timestamp);
    int ret = timerfd_settime(timerfd, 0, &new_val, &old_val);
    if (ret){
        cout << "timerfd_settime error" << endl;
    }
}
struct timespec TimerQueue::time_from_now(Timestamp when)
{
    int64_t microseconds = when.get_timestamp()
        - Timestamp::now().get_timestamp();
    if (microseconds < 100)
    {
        microseconds = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(
            microseconds / Timestamp::_MICROSECOND_PRE_SECOND);
    ts.tv_nsec = static_cast<long>(
            (microseconds % Timestamp::_MICROSECOND_PRE_SECOND) * 1000);
    return ts;
}

void TimerQueue::read_timerfd(int timefd, Timestamp now){
    uint64_t tmp;
    ssize_t len = read(timefd, &tmp, sizeof(tmp));
    if (len != sizeof(tmp)){
        cout << "read_timerfd() error" << endl;
    }
}
vector<TimerQueue::TimePair> TimerQueue::get_expired(Timestamp now){
    vector<TimePair> expired;
    TimePair time_pair(now, reinterpret_cast<Timer*>(UINTPOINT_MAX));
    auto end = _time_list.lower_bound(time_pair);
    copy(_time_list.begin(), end, back_inserter(expired));
    _time_list.erase(_time_list.begin(), end);
    return expired;
}
void TimerQueue::reset(vector<TimerQueue::TimePair>& expired, Timestamp timestamp){
    for(auto iter = expired.begin(); iter != expired.end(); ++iter){
        if(iter->second->is_interval()){
            iter->second->move_to_next();
            insert(iter->second);
        }
    }
    Timestamp next_expire;
    if(!_time_list.empty()){
        next_expire = _time_list.begin()->second->get_timestamp();
    }
    if(next_expire.valid()){
        reset_timerfd(_timefd, next_expire);
    }
}
void TimerQueue::handle_read(){
    Timestamp now(Timestamp::now());
    read_timerfd(_timefd, now);
    vector<TimePair> expired = get_expired(now);
    for (auto iter = expired.begin(); iter != expired.end();++iter){
        iter->second->run();
    }
    reset(expired, now);
}
