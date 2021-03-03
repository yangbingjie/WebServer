#include "TcpServer.h"

TcpServer::TcpServer():_epoll_fd(-1), _listen_fd(-1){

}
TcpServer::~TcpServer(){

}

void TcpServer::start(){
    _epoll_fd = epoll_create(1);

    if (_epoll_fd < 0){
        cout << "Epoll create error: " << errno << endl;
    }
    _acceptor = new Acceptor(_epoll_fd); // TODO Memory Leak
    _acceptor->set_callback(this);
    _acceptor->start();
    
    while (true){
        int fds = epoll_wait(_epoll_fd, _events, MAX_EVENTS , -1);
        if (fds == -1){
            cout << "Epoll wait error: " << errno << endl;
        }
        vector<Channel*>channel_array;
        for(int i = 0; i < fds; ++i){
            Channel * pChannel = static_cast<Channel*>(_events[i].data.ptr);
            pChannel->set_revents(_events[i].events);
            channel_array.push_back(pChannel);
        }
        vector<Channel*>::iterator iter = channel_array.begin();
        while(iter != channel_array.end()){
            (*iter)->handle_events();
            iter++;
        }
    }

}

void newConnection(int connect_fd){
    TcpConnection * handler = new TcpConnection(_epoll_fd, _socket_fd); // TODO Memory Leak
    _connections[connect_fd] = handler;
}