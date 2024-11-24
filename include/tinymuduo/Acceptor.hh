#ifndef _TINYMUDUO_ACCEPTOR_H
#define _TINYMUDUO_ACCEPTOR_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Socket.hh"
#include "tinymuduo/Channel.hh"

#include <functional>

class EventLoop;
class InetAddress;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int, const InetAddress&)>;
    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback &cb) { newConnectionCallback_ = std::move(cb);}

    bool listenning() const { return listenning_; }
    void listen();
private:
    void handleRead();

    EventLoop *loop_; // main reactor
    Socket acceptSocket_; // Socket of listen fd
    Channel acceptChannel_; // Channel of listen fd
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;
};

#endif
