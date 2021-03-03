#ifndef _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

#include <vector>
#include <iterator>
#include "Declare.h"

using namespace std;

class EventLoop{
    public:
        EventLoop();
        ~EventLoop();
        void loop();
        void update(Channel* channel);
    private:
        bool _killed;
        Epoll* _epoll;
};

#endif // _EVENT_LOOP_H_