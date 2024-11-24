#ifndef _TINYMUDUO_EPOLLPOLLER_H
#define _TINYMUDUO_EPOLLPOLLER_H

#include "tinymuduo/Poller.hh"

#include <vector>
#include <sys/epoll.h>

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop *loop);
    virtual ~EPollPoller() override;
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;

    virtual void updateChannel(Channel *channel) override;
    virtual void removeChannel(Channel *channel) override;
    
private:
    using EventList = std::vector<epoll_event>;
    static const int kInitEventListSize = 16;
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    void update(int operation, Channel *channel);

    int epollfd_;
    EventList events_;
};

#endif
