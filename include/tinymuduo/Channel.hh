#ifndef _TINYMUDUO_CHANNEL_H
#define _TINYMUDUO_CHANNEL_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Timestamp.hh"

#include <functional>
#include <memory>

class EventLoop;

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    void handleEvent(Timestamp receieveTime);

    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    void tie(const std::shared_ptr<void> &obj);

    int fd() const { return fd_; }
    int events() const { return events_; }
    void setRevents(int revents) { revents_ = revents; }
    bool isNonEvent() const { return events_ == kNoneEvent; }

    void enableReading() { events_ |= kReadEvent; update(); }
    void disableReading() { events_ &= ~kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }

    bool isNoneEvent() { return events_ == kNoneEvent; }
    bool isWriting() { return events_ & kWriteEvent; }
    bool isReading() { return events_ & kReadEvent; }

    int index() { return index_; }
    void setIndex(int idx) { index_ = idx; }

    EventLoop* ownerLoop() { return loop_; }
    void remove();

private:
    void update();
    void handleEventWithGuard(Timestamp receieveTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_; // eventLoop the channel belongs to
    const int fd_; // packaged socket
    int events_; // registed events (EPOLLHUP | EPOLLIN | EPOLLPRI | EPOLLOUT)
    int revents_; // return events (EPOLLHUP | EPOLLIN | EPOLLPRI | EPOLLOUT)
    int index_; // kNoneEvent | kReadEvent | kWriteEvent

    std::weak_ptr<void> tie_;
    bool tied_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

#endif
