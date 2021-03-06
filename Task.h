#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include "IRun.h"
using namespace std;
class Task{
public:
    Task(IRun0* func);
    Task(IRun2* func, const std::string& str, void* args);
    void do_task();
private:
    IRun0* _func0;
    IRun2* _func2;
    std::string _str;
    void* _args;
};

#endif // _TASK_H_