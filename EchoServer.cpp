#include "EchoServer.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#define MESSAGE_LENGTH 10

EchoServer::EchoServer(EventLoop* loop)
:_loop(loop), _server(loop), _timer(-1), _index(0){
    _server.set_callback(this);
}
EchoServer::~EchoServer(){}
void EchoServer::start(){
    _server.start();
}
void EchoServer::onConnect(TcpConnection* connection){
    cout << "onConnect" << endl;
}
void EchoServer::onMessage(TcpConnection* connection, Buffer* buffer){
    while(buffer->size() > MESSAGE_LENGTH){
        string message = buffer->retrieveAndReturn(MESSAGE_LENGTH);
        connection->send(message+ "\n");        
    }
    _timer = _loop->run_every(0.5, this);
}
void EchoServer::onWriteComplate(TcpConnection* connection){
    cout << "onWriteComplate" << endl;
}
void EchoServer::run(void* args){
    cout << _index;
    if(_index++ > 3){
        cout << ", Timeout!" << endl;
        _loop->cancel_timer(_timer);
        _index = 0;
    }
}