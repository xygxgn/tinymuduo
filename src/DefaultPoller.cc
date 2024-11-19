#include "Poller.hh"

#include <stdlib.h>

Poller* Poller::newDefaultPoller(EventLoop *loop)
{
    if (::getenv("TINYMUDUO_USE_POLL"))
        return nullptr;
    else
        return nullptr;
}
