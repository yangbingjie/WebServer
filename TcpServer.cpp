#include "TcpServer.h"

TcpServer::TcpServer(){

}
int TcpServer::create_epoll(int listen_fd){
    int epoll_fd = epoll_create(1);
    struct epoll_event ev;
    ev.data.fd = listen_fd;
    ev.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
    return epoll_fd;
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
    int listen_fd = create_socket();
    int epoll_fd = create_epoll(listen_fd);
    int connect_fd;
    char read_buf[MAX_BUF_SIZE];
    struct sockaddr_in client_addr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    struct epoll_event ev, events[MAX_EVENTS];
    while (true){
        int fds = epoll_wait(epoll_fd, events, MAX_EVENTS , -1);
        if (fds == -1){
            cout << "Epoll wait error: " << errno << endl;
        }
        for(int i = 0; i < fds; ++i){
            if(events[i].data.fd == listen_fd){
                connect_fd = accept(listen_fd, (sockaddr*)&client_addr, (socklen_t*)&clilen);
                if (connect_fd > 0){
                    cout << "Client Connect From " << inet_ntoa(client_addr.sin_addr) << ":" 
                    << ntohs(client_addr.sin_port) << " with connect fd " << connect_fd << endl;
                }else{
                    cout << "Accept error: " << errno << endl;
                }
                ev.data.fd = connect_fd;
                ev.events = EPOLLIN;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &ev);
            } else if (events[i].events == EPOLLIN){
                bzero(read_buf, MAX_BUF_SIZE);
                connect_fd = events[i].data.fd;
                int read_len = read(connect_fd, read_buf, MAX_BUF_SIZE);
                if (read_len < 0 && errno == ECONNRESET){
                    cout << "ECONNRESET error" << endl;
                    close(connect_fd);
                }else if (read_len == 0){
                    cout << "Socket close" << endl;
                    close(connect_fd);
                }else{
                    cout << "Read from client: " << read_buf << endl;
                    if (read_len != write(connect_fd, read_buf, read_len)){
                        cout << "Write error" << endl;
                    }
                }
            }
        }
    }

}