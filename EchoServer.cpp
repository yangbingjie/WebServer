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
void EchoServer::onMessage(TcpConnection* connection, string* data){
    while(data->size() > MESSAGE_LENGTH){
        string message = data->substr(0, MESSAGE_LENGTH);
        *data = data->substr(MESSAGE_LENGTH, data->size());
        connection->send(message + "\n");
    }
}