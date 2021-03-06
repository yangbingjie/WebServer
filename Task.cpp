#include "Task.h"
Task::Task(IRun0* func):_func0(func), _func2(NULL), _args(NULL){

}
Task::Task(IRun2* func, const std::string& str, void* args)
:_func0(NULL),_func2(func), _str(str), _args(args){}
void Task::do_task(){
    if(_func0) {
        _func0->run0();
    } else {
        _func2->run2(_str, _args);
    }
}