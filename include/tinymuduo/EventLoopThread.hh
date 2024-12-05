#ifndef _TINYMUDUO_EVENTLOOPTHREAD_H
#define _TINYMUDUO_EVENTLOOPTHREAD_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Thread.hh"

#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>

class EventLoop;

class EventLoopThread : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(), const std::string &name  = std::string());
    ~EventLoopThread();

    EventLoop* startLoop();
private:
    void threadFunc();

    EventLoop *loop_;
    bool exiting_;
    Thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallback callback_;
};

#endif
