#ifndef _ICHANNEL_CALLBACK_H_
#define _ICHANNEL_CALLBACK_H_
class IChannelCallBack{
public:
    virtual void handle_event(int socket_fd) = 0;
};
#endif // _ICHANNEL_CALLBACK_H_