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
#include "IChannelCallBack.h"

using namespace std;

class EventLoop : public IChannelCallBack{
    public:
        EventLoop();
        ~EventLoop();
        int create_eventfd();
        void loop();
        void update(Channel* channel);
        void queue_loop(IRun* run);
        void wakeup();
        void handle_read();
        void handle_write();
        void run_pending_functors();
    private:
        bool _killed;
        Epoll* _epoll;
        int _eventfd;
        vector<IRun*> _pending_functors;
        Channel* _eventfd_channel;
};

#endif // _EVENT_LOOP_H_