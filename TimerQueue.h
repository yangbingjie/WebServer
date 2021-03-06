#ifndef _TIMER_QUEUE_H_
#define _TIMER_QUEUE_H_
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <unistd.h>
#include "Declare.h"
#include "IRun.h"
#include "IChannelCallBack.h"
#include "Timestamp.h"
#include "Timer.h"
using namespace std;


class TimerQueue : public IChannelCallBack, public IRun2{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();
    virtual void run2(const string& str, void* timer);
    long add_timer(IRun0* run, Timestamp when, double interval);
    void do_add_timer(Timer* arg);
    void cancel_timer(long timer_id);
    void do_cancel_timer(Timer* arg);
    virtual void handle_read();
    virtual void handle_write(){}
    static struct timespec time_from_now(Timestamp when);
private:
    typedef pair<Timestamp, Timer*> TimePair;
    typedef set<TimePair> TimeList;

    bool insert(Timer* timer);
    void reset_timerfd(int timerfd, Timestamp timestamp);
    void read_timerfd(int timefd, Timestamp now);
    int create_timerfd();
    vector<TimePair> get_expired(Timestamp now);
    void reset(vector<TimePair>& expired, Timestamp timestamp);

    int _timefd;
    EventLoop* _loop;
    TimeList _time_list;
    Channel* _timefd_channel;
};
#endif // _TIMER_QUEUE_H