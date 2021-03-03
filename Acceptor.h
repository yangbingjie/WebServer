#ifndef _ACCEPTOR_H_
#define _ACCEPTOR_H_

class Acceptor :public EventHandler{
public:
    Acceptor(int epoll_fd);
    ~Acceptor();
    virtual void handle_event(int socket_fd);
    void start();
    int create_socket();
private:
    int _listen_fd;
    Channel* _channel;
    IChannelCallBack* _callbacks;
};
#endif // _ACCEPTOR_H_