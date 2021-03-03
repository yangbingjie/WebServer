#include "TcpConnection.h"

TcpConnection::TcpConnection(int epoll_fd, int socket_fd):EventHandler(epoll_fd),_socket_fd(socket_fd){
    _channel = new Channel(_epoll_fd, _socket_fd);
    _channel->enable_read();
    _channel->set_callback(this);
}
TcpConnection::~TcpConnection(){

}
void TcpConnection::handle_event(int socket_fd){
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