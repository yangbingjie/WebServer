#include "ThreadPool.h"

ThreadPool::ThreadPool(){}
void ThreadPool::start(int num){
    _threads.reserve(num);
    for(int i = 0; i < num; ++i){
        Task task(this);
        Thread* p = new Thread(task); // TODO Memory Leak
        _threads.push_back(p);
        p->start();
    }
}
void ThreadPool::add_task(Task& task){
    _queue.enqueue(task);
}
void ThreadPool::run0(){
    run_by_thread();
}
void ThreadPool::run_by_thread(){
    while(true){
        _queue.dequeue().do_task();
    }
}