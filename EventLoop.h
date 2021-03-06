#ifndef _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

#include <vector>
#include <iterator>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "sys/eventfd.h"
#include "Declare.h"
#include "IRun.h"
#include "Timestamp.h"
#include "IChannelCallBack.h"
#include "Mutex.h"
#include "ThreadPool.h"
#include "Task.h"

using namespace std;

class EventLoop : public IChannelCallBack{
public:
    EventLoop();
    ~EventLoop();
    int create_eventfd();
    void loop();
    void update(Channel* channel);
    void queue_loop(Task task);
    void wakeup();
    void handle_read();
    void handle_write();
    void run_pending_functors();
    void run_in_loop(Task f);
    bool is_in_loop_thread();

    long run_at(Timestamp when, IRun0* run);
    long run_after(double delay, IRun0* run);
    long run_every(double interval, IRun0* run);
    void cancel_timer(long timer_id);
private:
    bool _killed;
    Epoll* _epoll;
    int _eventfd;
    vector<Task> _pending_functors;
    Channel* _eventfd_channel;
    TimerQueue* _timer_queue;
    int _timer;
    const pid_t _thread_id;
    bool _calling_pending_func;
    Mutex _mutex;
};

#endif // _EVENT_LOOP_H_