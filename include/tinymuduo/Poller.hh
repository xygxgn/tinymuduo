#ifndef _TINYMUDUO_POLLER_H
#define _TINYMUDUO_POLLER_H

#include "tinymuduo/noncopyable.hh"
#include "tinymuduo/Timestamp.hh"

#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *loop);
    virtual ~Poller() = default;
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    bool hasChannel(Channel *channel) const;
    static Poller* newDefaultPoller(EventLoop *loop);
protected:
    // key:value <==> sockfd:channel
    using ChannelMap = std::unordered_map<int, Channel*>;

    ChannelMap channels_;
private:
    EventLoop *ownerLoop_; // eventLoop the poller belongs to
};

#endif
