#include "TcpConnection.h"
#include "Channel.h"
#include "IUser.h"
#include "EventLoop.h"

TcpConnection::TcpConnection(EventLoop* loop, int socket_fd):_loop(loop),_socket_fd(socket_fd), 
_user(NULL){
    _connect_channel = new Channel(_loop, _socket_fd); // TODO Memory Leak
    _connect_channel->enable_read();
    _connect_channel->set_callback(this);
}
TcpConnection::~TcpConnection(){

}
void TcpConnection::handle_read(){
    int socket_fd = _connect_channel->get_fd();
    if (socket_fd < 0) {
        cout << "EPOLLIN error sockfd" << socket_fd << "< 0"<< endl;
        return;
    }
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
        _in_buffer.append(string(read_buf, read_len));
        _user->onMessage(this, &_in_buffer);
    }
}

void TcpConnection::handle_write(){
    int socket_fd = _connect_channel->get_fd();
    if (_connect_channel->is_writing())
    {
        int len = write(socket_fd, _out_buffer.c_str(), _out_buffer.size());
        if (len > 0){
            cout << "Write " << len << " bytes" << endl;
            _out_buffer.retrieve(len);
            if(_out_buffer.empty()){
                _connect_channel->disable_write();
                _loop->queue_loop(this, NULL);
            }
        }
    }
}

void TcpConnection::send(const string& data){
    int len = 0;
    if (_out_buffer.empty())
    {
        len = write(_socket_fd, data.c_str(), data.size());
        if(len < 0){
            cout << "Write error: " << errno << endl;
        }
        if (len == static_cast<int>(data.size()))
        {
            _loop->queue_loop(this, NULL); // Invoke onWriteComplate
        }
        
    }
    if (len < static_cast<int>(data.size()))
    {
        _out_buffer.append(data.substr(len, data.size()));
        if (_connect_channel->is_writing())
        {
            _connect_channel->enable_write();
        }
        
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
void TcpConnection::run(void* args){
    _user->onWriteComplate(this);
}