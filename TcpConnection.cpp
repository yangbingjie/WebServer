#include "TcpConnection.h"
#include "Channel.h"
#include "IUser.h"

TcpConnection::TcpConnection(EventLoop* loop, int socket_fd):_loop(loop),_socket_fd(socket_fd){
    _channel = new Channel(_loop, _socket_fd); // TODO Memory Leak
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
        string buffer(read_buf, MAX_BUF_SIZE);
        _user->onMessage(this, buffer);
    }
}

void TcpConnection::send(const string& data){
    int len = write(_socket_fd, data.c_str(), data.size());
    if (len != data.size()){
        cout << "Write error" << endl;
    }
}

void TcpConnection::set_user(IUser* user){
    _user = user;
}

void TcpConnection::connectEstablish(){
    if(_user){
        _user->onConnect(this);
    }
}