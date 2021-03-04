#include "EchoServer.h"
#include "TcpConnection.h"
#define MESSAGE_LENGTH 10

EchoServer::EchoServer(EventLoop* loop):_loop(loop), _server(loop){
    _server.set_callback(this);
}
EchoServer::~EchoServer(){}
void EchoServer::start(){
    _server.start();
}
void EchoServer::onConnect(TcpConnection* connection){
    cout << "onConnect" << endl;
}
void EchoServer::onMessage(TcpConnection* connection, Buffer* data){
    while(data->size() > MESSAGE_LENGTH){
        data->substr(MESSAGE_LENGTH);
        connection->send(data->value() + "\n");
    }
}
void EchoServer::onWriteComplate(TcpConnection* connection){
    cout << "onWriteComplate" << endl;
}