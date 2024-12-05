#ifndef _TINYMUDUO_EVENTLOOP_H
#define _TINYMUDUO_EVENTLOOP_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Timestamp.hh"
#include "tinymuduo/CurrentThread.hh"

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

class Channel;
class Poller;

// Reactor, at most one per thread
class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }
    
    void runInLoop(Functor cb); 
    void queueInLoop(Functor cb);

    void wakeup();

    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

private:
    using ChannelList = std::vector<Channel*>;

    void handleRead();
    void doPendingFunctors();

    std::atomic<bool> looping_;
    std::atomic<bool> quit_;

    const pid_t threadId_;

    Timestamp pollReturnTime_;
    std::unique_ptr<Poller> poll_;

    int wakeupFd_; // used for mainloop to wake up a subloop to process channel
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_;

    std::atomic<bool> callingPendingFunctors_;
    std::vector<Functor> pendingFunctors_;
    std::mutex mutex_;
};

#endif
