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

using namespace std;

class EventLoop : public IChannelCallBack{
public:
    EventLoop();
    ~EventLoop();
    int create_eventfd();
    void loop();
    void update(Channel* channel);
    void queue_loop(IRun* run, void* args);
    void wakeup();
    void handle_read();
    void handle_write();
    void run_pending_functors();

    long run_at(Timestamp when, IRun* run);
    long run_after(double delay, IRun* run);
    long run_every(double interval, IRun* run);
    void cancel_timer(long timer_id);

    class Runner{
    public:
        Runner(IRun* run, void* args):_run(run), _args(args){}
        void do_run(){
            _run->run(_args);
        }
    private:
        IRun* _run;
        void* _args;
    };
private:
    bool _killed;
    Epoll* _epoll;
    int _eventfd;
    vector<Runner> _pending_functors;
    Channel* _eventfd_channel;
    TimerQueue* _timer_queue;
    int _timer;
};

#endif // _EVENT_LOOP_H_