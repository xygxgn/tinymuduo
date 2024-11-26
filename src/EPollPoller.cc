#include "tinymuduo/EPollPoller.hh"
#include "tinymuduo/Logger.hh"
#include "tinymuduo/Channel.hh"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

// state of channel->index_
const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

EPollPoller::EPollPoller(EventLoop *loop) 
    : Poller(loop), 
      epollfd_(epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize)
{
    if (epollfd_ == -1)
    {
        LOG_FATAL("epoll_create error: %d\n", errno);
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}


Timestamp EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    LOG_INFO("function=%s => fd total count:%lu\n", __func__, channels_.size());

    int numEvent = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);
    int saveErrno = errno;
    Timestamp nowTime(Timestamp::now());
    if (numEvent > 0)
    {
        LOG_DEBUG("%d events happened! \n", numEvent);
        fillActiveChannels(numEvent, activeChannels);
        if (static_cast<size_t>(numEvent) == events_.size())
        {
            events_.resize(events_.size() * 2);
        }
    }
    else if (numEvent == 0)
    {
        LOG_DEBUG("%s timeout!\n", __func__);
    }
    else
    {
        if (saveErrno != EINTR)
        {
            errno = saveErrno;
            LOG_ERROR("EPollPoller::poll error!");
        }
    }
    return nowTime;
}

void EPollPoller::updateChannel(Channel *channel)
{
    const int index = channel->index();
    LOG_INFO("function=%s ==>fd=%d, events=%d, index=%d", __func__, 
        channel->fd(), channel->events(), channel->index());

    if (index == kNew || index == kDeleted)
    {
        // a new one, add with EPOLL_CTL_ADD
        if (index == kNew)
        {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        channel->setIndex(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        // update existing one with EPOLL_CTL_MOD/DEL
        int fd = channel->fd();
        if (channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->setIndex(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPollPoller::removeChannel(Channel *channel)
{
    int fd = channel->fd();
    channels_.erase(fd);

    LOG_INFO("function=%s => fd=%d", __func__, channel->fd());

    int index = channel->index();
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->setIndex(kNew);

}

void EPollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    for (int i = 0; i < numEvents; ++i)
    {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->setRevents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

void EPollPoller::update(int operation, Channel *channel)
{
    epoll_event event;
    ::memset(&event, 0, sizeof(event));
    int fd = channel->fd();
    event.data.ptr = channel;
    event.events = channel->events();
    
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll_ctl del error: %d\n", errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/mod error: %d\n", errno);
        }
    }
}
