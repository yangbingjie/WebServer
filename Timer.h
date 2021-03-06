#ifndef _TIMER_H_
#define _TIMER_H_
#include "IRun.h"
class Timer{
public:
    Timer(IRun0* run, Timestamp timestamp, double interval):_run(run), _timestamp(timestamp), _interval(interval){}
    Timestamp get_timestamp(){return _timestamp;}
    bool is_interval(){return _interval > 0.0;}
    void move_to_next(){_timestamp = Timestamp::nowAfter(_interval);}
    void timeout()
    {
        _run->run0();
    }

private:
    Timestamp _timestamp;
    IRun0* _run;
    double _interval;
};

#endif // _TIMER_H_