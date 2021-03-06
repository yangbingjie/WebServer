#ifndef _THREAD_H_
#define _THREAD_H_
#include "Task.h"
using namespace std;
class Thread{
public:
    Thread(Task& task);
    void start();
    pid_t get_tid();
private:
    Task _task;
};

#endif // _THREAD_H_