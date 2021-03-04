#ifndef _IUSER_H_
#define _IUSER_H_
#include <string>
#include "Declare.h"

using namespace std;

class IUser{
public:
    virtual void onConnect(TcpConnection* connection) = 0;
    virtual void onMessage(TcpConnection* connection, Buffer* data) = 0;
    virtual void onWriteComplate(TcpConnection* connection) = 0;
};

#endif // _IUSER_H_