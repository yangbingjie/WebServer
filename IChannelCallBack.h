#ifndef _ICHANNEL_CALLBACK_H_
#define _ICHANNEL_CALLBACK_H_
class IChannelCallBack{
public:
    virtual void handle_read() = 0;
    virtual void handle_write() = 0;
};
#endif // _ICHANNEL_CALLBACK_H_