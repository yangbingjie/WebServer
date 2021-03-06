#ifndef _COND_H_
#define _COND_H_
#include <pthread.h>
#include "Mutex.h"
class Cond{
public:
    Cond(Mutex & mutex):_mutex(mutex){
        pthread_cond_init(&_cond_id, NULL);
    }
    ~Cond(){
        pthread_cond_destroy(&_cond_id);
    }
    void wait(){
        pthread_cond_wait(&_cond_id, _mutex.get_pthread_mutex_id());
    }
    void notify(){
        pthread_cond_signal(&_cond_id);
    }
    void boardcast(){
        pthread_cond_broadcast(&_cond_id);
    }
private:
    Mutex & _mutex;
    pthread_cond_t _cond_id;
};

#endif // _COND_H_