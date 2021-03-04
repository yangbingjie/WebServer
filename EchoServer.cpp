#include "EchoServer.h"
#include "TcpConnection.h"

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
void EchoServer::onMessage(TcpConnection* connection, const string& data){
    cout << "onMessage" << endl;
    connection->send(data);
}