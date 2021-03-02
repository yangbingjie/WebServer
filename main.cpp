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
#define MAX_BUF_SIZE 1000
int main(){
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

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
    struct sockaddr_in client_addr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    char read_buf[MAX_BUF_SIZE];
    while (true){
        int connect_fd = accept(listen_fd, (sockaddr*)&client_addr, (socklen_t*)&clilen);
        if (connect_fd > 0){
            cout << "Client Connect From " << inet_ntoa(client_addr.sin_addr) << ":" 
            << ntohs(client_addr.sin_port) << " with connect fd " << connect_fd << endl;
        }else{
            cout << "Accept error: " << errno << endl;
        }
        bzero(read_buf, MAX_BUF_SIZE);
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

    return 0;
}