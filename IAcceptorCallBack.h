#ifndef _IACCEPTOR_CALLBACK_H_
#define _IACCEPTOR_CALLBACK_H_

class IAcceptorCallBack{
    virtual void newConnection(int connect_fd) = 0;
};

#endif // _IACCEPTOR_CALLBACK_H_