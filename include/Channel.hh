#ifndef _TINYMUDUO_CHANNEL_H
#define _TINYMUDUO_CHANNEL_H

#include "noncopyable.hh"
#include "Timestamp.hh"

#include <functional>
#include <memory>

class EventLoop;

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel();
    Channel(EventLoop *loop, int fd);
    void handleEvent(Timestamp receieveTime);

private:
    static const int kNodeEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int *fd_;
    int events_;
    int revents_;
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

#endif
