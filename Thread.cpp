#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <iostream>
#include "Thread.h"
namespace CurrentThread
{
  __thread int t_cachedTid = 0;
}

void* global_run(void* args){
    ((Task*)args)->do_task();
    return NULL;
}
Thread::Thread(Task& task):_task(task){

}
void Thread::start(){
    pthread_t t;
    pthread_create(&t, NULL, global_run, &_task);
}
pid_t Thread::get_tid(){
    return static_cast<pid_t>(syscall(SYS_gettid));
}