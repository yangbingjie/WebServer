#ifndef _TIMER_QUEUE_H_
#define _TIMER_QUEUE_H_
#include <vector>
#include <set>
#include <fstream>
#include <unistd.h>
#include "Declare.h"
#include "IRun.h"
#include "IChannelCallBack.h"
#include "Timestamp.h"
using namespace std;
class Timer{
public:
    Timer(IRun* run, Timestamp timestamp, double interval):_run(run), _timestamp(timestamp), _interval(interval){}
    Timestamp get_timestamp(){return _timestamp;}
    void run(){
        _run->run(this);
    }
    bool is_interval(){return _interval > 0.0;}
    void move_to_next(){_timestamp = Timestamp::nowAfter(_interval);}
private:
    Timestamp _timestamp;
    IRun* _run;
    double _interval;
};


class TimerQueue : public IChannelCallBack{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();
    long add_timer(IRun* run, Timestamp when, double interval);
    void do_add_timer(void* arg);
    void cancel_timer(long timer_id);
    void do_cancel_timer(void* arg);
    virtual void handle_read();
    virtual void handle_write(){}
    static struct timespec time_from_now(Timestamp when);

    class AddTimerWrapper : public IRun{
    public:
        AddTimerWrapper(TimerQueue* queue):_time_queue(queue){}
        virtual void run(void* args){
            _time_queue->do_add_timer(args);
        }
    private:
        TimerQueue* _time_queue;
    };

    class CancelTimerWrapper : public IRun{
        public:
        CancelTimerWrapper(TimerQueue* queue):_time_queue(queue){}
        virtual void run(void* args){
            _time_queue->do_cancel_timer(args);
        }
    private:
        TimerQueue* _time_queue;
    };
private:
    typedef pair<Timestamp, Timer*> TimePair;
    typedef set<TimePair> TimeList;

    bool insert(Timer* timer);
    void reset_timerfd(int timerfd, Timestamp timestamp);
    void read_timerfd(int timefd, Timestamp now);
    int create_timerfd();
    vector<TimePair> get_expired(Timestamp now);
    void reset(vector<TimePair>& expired, Timestamp timestamp);

    AddTimerWrapper* _add_timer_wrapper;
    CancelTimerWrapper* _cancel_timer_wrapper;
    int _timefd;
    EventLoop* _loop;
    TimeList _time_list;
    Channel* _timefd_channel;
};
#endif // _TIMER_QUEUE_H