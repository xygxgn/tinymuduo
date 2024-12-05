#include "tinymuduo/Poller.hh"
#include "tinymuduo/Channel.hh"

Poller::Poller(EventLoop *loop)
    : ownerLoop_(loop)
{
}

bool Poller::hasChannel(Channel *channel) const
{
    ChannelMap::const_iterator iter = channels_.find(channel->fd());
    return iter != channels_.end() && iter->second == channel;
}