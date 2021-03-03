#include "Acceptor.h"
Acceptor::Acceptor(int epoll_fd):_epoll_fd(epoll_fd), _listen_fd(-1), _channel(NULL), _callbacks(NULL){

}
Acceptor::~Acceptor(){}

void Acceptor::start(){
    _listen_fd = create_socket();
    _channel = new Channel(_epoll_fd, _listen_fd); // TODO Memory Leak
    _channel->enable_read();
    _channel->set_callback(this);
}

int Acceptor::create_socket(){
    _listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(_listen_fd, F_SETFL, O_NONBLOCK);
    int on = 1;
    setsockopt(_listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    struct sockaddr_in sever_addr;
    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = htons(PORT);
    sever_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if (-1 == bind(_listen_fd, (sockaddr*)&sever_addr, sizeof(sever_addr))){
        cout << "Bind error: " << errno << endl;
    }

    if (-1 == listen(_listen_fd, MAX_LISTEN)){
        cout << "Listen error: " << errno << endl;
    }
    return _listen_fd;
}

void Acceptor::handle_event(int socket_fd){
    struct sockaddr_in client_addr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    int connect_fd = accept(_listen_fd, (sockaddr*)&client_addr, (socklen_t*)&clilen);
    if (connect_fd > 0){
        cout << "Client Connect From " << inet_ntoa(client_addr.sin_addr) << ":" 
        << ntohs(client_addr.sin_port) << " with connect fd " << connect_fd << endl;
    }else{
        cout << "Accept error: " << errno << endl;
    }
    fcntl(connect_fd, F_SETFL, O_NONBLOCK);
    _callbacks->newConnection(connect_fd);
}

void Acceptor::set_callback(IAcceptorCallBack* callback){
    _callbacks = callback;
}