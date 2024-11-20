#ifndef _TINYMUDUO_TCPSERVER_H
#define _TINYMUDUO_TCPSERVER_H

#include "noncopyable.hh"

#include <functional>
#include <string>
#include <memory>

class EventLoop;
class Acceptor;
class EventLoopThreadPool;

class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    TcpServer();
    ~TcpServer();
private:
    EventLoop *loop_;
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;
};

#endif
