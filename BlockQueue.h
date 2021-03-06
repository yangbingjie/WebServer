#ifndef _BLOCK_QUEUE_H_
#define _BLOCK_QUEUE_H_
#include <iostream>
#include <queue>
#include "Mutex.h"
#include "Cond.h"
using namespace std;

template<typename T>
class BlockQueue{
public:
    BlockQueue():_cond(_mutex){}
    void enqueue(const T& t){
        _mutex.lock();
        _queue.push_back(t);
        _cond.notify();
        _mutex.unlock();
    }
    T dequeue(){
        _mutex.lock();
        while(_queue.empty()){
            _cond.wait();
        }
        T t(_queue.front());
        _queue.pop_front();
        _mutex.unlock();
        return t;
    }
private:
    deque<T> _queue;
    Mutex _mutex;
    Cond _cond;
};


#endif // _BLOCK_QUEUE_H_