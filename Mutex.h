#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <pthread.h>
class Mutex{
public:
    Mutex(){
        pthread_mutex_init(&_mutex_id, NULL);
    }
    ~Mutex(){
        pthread_mutex_destroy(&_mutex_id);
    }
    void lock(){
        pthread_mutex_lock(&_mutex_id);
    }
    void unlock(){
        pthread_mutex_unlock(&_mutex_id);
    }
    pthread_mutex_t* get_pthread_mutex_id(){return &_mutex_id;}
private:
    pthread_mutex_t _mutex_id;
};


#endif // _MUTEX_H_