#ifndef _TINYMUDUO_TCPSERVER_H
#define _TINYMUDUO_TCPSERVER_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Callbacks.hh"
#include "tinymuduo/InetAddress.hh"
#include "tinymuduo/TcpConnection.hh"
// #include "tinymuduo/EventLoop.hh"
// #include "tinymuduo/Acceptor.hh"
// #include "tinymuduo/EventLoopThreadPool.hh"

#include <functional>
#include <string>
#include <memory>
#include <unordered_map>
#include <atomic>

class EventLoop;
class Acceptor;
class EventLoopThreadPool;

class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    enum Option
    {
        kNoReusePort,
        kReusePort
    };

    TcpServer(EventLoop *loop, const InetAddress listenAddr, const std::string &nameArg, Option option = kNoReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback &cb) { threadInitCallback_ = cb; }
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) {writeCompleteCallback_ = cb; }

    void setThreadNum(int numThreads);
    void start();
private:
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

    void newConnection(int sockfd, const InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

    EventLoop *loop_;
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;

    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;

    ThreadInitCallback threadInitCallback_;
    std::atomic<int> started_;

    int nextConnId_;
    ConnectionMap connections_;
};

#endif
