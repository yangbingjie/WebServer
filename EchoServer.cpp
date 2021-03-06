#include "EchoServer.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Task.h"
#define MESSAGE_LENGTH 10

EchoServer::EchoServer(EventLoop* loop)
:_loop(loop), _server(loop), _timer(-1), _index(0){
    _server.set_callback(this);
}
EchoServer::~EchoServer(){}
void EchoServer::start(){
    _server.start();
    _thread_pool.start(5);
}
void EchoServer::onConnect(TcpConnection* connection){
    cout << "onConnect" << endl;
}
void EchoServer::onMessage(TcpConnection* connection, Buffer* buffer){
    while(buffer->size() > MESSAGE_LENGTH){
        string message = buffer->retrieveAndReturn(MESSAGE_LENGTH);
        Task task(this, message, connection);
        _thread_pool.add_task(task);
    }
    _timer = _loop->run_every(0.5, this);
}
void EchoServer::run2(const string& message, void* tcp){
    cout << "tid = " << fib(30) << CurrentThread::tid() << endl;
    static_cast<TcpConnection*>(tcp)->send(message + "\n");
}
int EchoServer::fib(int n){
    return (n == 1 || n == 2) ? 1 : (fib(n-1) + fib(n-2));
}
void EchoServer::onWriteComplate(TcpConnection* connection){
    cout << "onWriteComplate" << endl;
}
void EchoServer::run0(){
    cout << _index;
    if(_index++ > 3){
        cout << ", Timeout!" << endl;
        _loop->cancel_timer(_timer);
        _index = 0;
    }
}