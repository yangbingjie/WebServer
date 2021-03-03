#include "TcpServer.h"

TcpServer::TcpServer():_epoll_fd(-1), _listen_fd(-1){

}
TcpServer::~TcpServer(){

}
int TcpServer::create_socket(){
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(listen_fd, F_SETFL, O_NONBLOCK);
    int on = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    struct sockaddr_in sever_addr;
    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = htons(PORT);
    sever_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if (-1 == bind(listen_fd, (sockaddr*)&sever_addr, sizeof(sever_addr))){
        cout << "Bind error: " << errno << endl;
    }

    if (-1 == listen(listen_fd, MAX_LISTEN)){
        cout << "Listen error: " << errno << endl;
    }
    return listen_fd;
}
void TcpServer::start(){
    _listen_fd = create_socket();
    _epoll_fd = epoll_create(1);

    Channel* channel = new Channel(_epoll_fd, _listen_fd); // TODO Memory Leak
    channel->enable_read();
    channel->set_callback(this);
    
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

void TcpServer::handle_events(int socket_fd){    
    if(socket_fd == _listen_fd){
        struct sockaddr_in client_addr;
        socklen_t clilen = sizeof(struct sockaddr_in);
        int connect_fd = accept(_listen_fd, (sockaddr*)&client_addr, (socklen_t*)&clilen);
        if (connect_fd > 0){
            cout << "Client Connect From " << inet_ntoa(client_addr.sin_addr) << ":" 
            << ntohs(client_addr.sin_port) << " with connect fd " << connect_fd << endl;
        }else{
            cout << "Accept error: " << errno << endl;
        }
        Channel* pChannel = new Channel(_epoll_fd, connect_fd); // TODO Memory Leak
        pChannel->enable_read();
        pChannel->set_callback(this);
    } else {
        char read_buf[MAX_BUF_SIZE];
        bzero(read_buf, MAX_BUF_SIZE);
        int read_len = read(socket_fd, read_buf, MAX_BUF_SIZE);
        if (read_len < 0 && errno == ECONNRESET){
            cout << "ECONNRESET error" << endl;
            close(socket_fd);
        }else if (read_len == 0){
            cout << "Socket close" << endl;
            close(socket_fd);
        }else{
            cout << "Read from client: " << read_buf << endl;
            if (read_len != write(socket_fd, read_buf, read_len)){
                cout << "Write error" << endl;
            }
        }
    }
}