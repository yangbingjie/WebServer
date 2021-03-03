#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

#define PORT 6978
#define MAX_LISTEN 10
#define MAX_BUF_SIZE 100
#define MAX_EVENTS 100
class TcpServer{
public:
    TcpServer();
    void start();
    int create_epoll(int listen_fd);
    int create_socket();
};
#endif