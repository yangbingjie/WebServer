#include "TcpServer.h"
#include "TcpConnection.h"
#include "Acceptor.h"

TcpServer::TcpServer(EventLoop* loop):_loop(loop),_acceptor(NULL), _user(NULL){

}
TcpServer::~TcpServer(){

}

void TcpServer::start(){
    _acceptor = new Acceptor(_loop); // TODO Memory Leak
    _acceptor->set_callback(this);
    _acceptor->start();
}

void TcpServer::newConnection(int connect_fd){
    TcpConnection * handler = new TcpConnection(_loop, connect_fd); // TODO Memory Leak
    _connections[connect_fd] = handler;
    handler->set_user(_user);
    handler->connectEstablish();
}

void TcpServer::set_callback(IUser* user){
    _user = user;
}