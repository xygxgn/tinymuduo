#include "tinymuduo/Poller.hh"
#include "tinymuduo/EPollPoller.hh"

#include <stdlib.h>

Poller* Poller::newDefaultPoller(EventLoop *loop)
{
    if (::getenv("TINYMUDUO_USE_POLL"))
        return nullptr;
    else
        return new EPollPoller(loop);
}
