#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <unistd.h>
#include <sys/syscall.h>
#include <vector>
#include "Declare.h"
#include "BlockQueue.h"
#include "IRun.h"
#include "Thread.h"
using namespace std;


namespace CurrentThread
{
    extern __thread int t_cachedTid;
    inline void cacheTid()
    {
        t_cachedTid = static_cast<int>(::syscall(SYS_gettid));
    }
    inline int tid()
    {
        if(t_cachedTid == 0)
        {
            cacheTid();
        }
        return t_cachedTid;
    }
}

class ThreadPool : public IRun0{
public:
    ThreadPool();
    void start(int num);
    void add_task(Task& task);
    virtual void run0();
private:
    void run_by_thread();
    BlockQueue<Task> _queue;
    vector<Thread*> _threads;
};

#endif // _THREAD_POOL_H_