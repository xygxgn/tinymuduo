#include "tinymuduo/EventLoopThreadPool.hh"
#include "tinymuduo/EventLoopThread.hh"

#include <stdio.h>

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, const std::string nameArg)
    : baseLoop_(baseLoop),
      name_(nameArg),
      started_(false),
      numThreads_(0),
      next_(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
}

void EventLoopThreadPool::start(const ThreadInitCallback &cb)
{
    started_ = true;

    for (int i = 0; i < numThreads_; ++i)
    {
        char buf[name_.size() + 32];
        ::snprintf(buf, sizeof(buf), "%s%d", name_.c_str(), i);
        // EventLoopThread starts when constructed
        EventLoopThread *t = new EventLoopThread(cb, buf);
        threads_.emplace_back(t);
        loops_.push_back(t->startLoop());
    }

    if (numThreads_ == 0 && cb != nullptr)
    {
        cb(baseLoop_);
    }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    EventLoop* loop = baseLoop_;

    if (!loops_.empty())
    {
        loop = loops_[next_++]; // round-robin subreactors
        
        if (next_ >= static_cast<int>(loops_.size()))
        {
            next_ = 0;
        }
    }

    return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
    if (loops_.empty())
    {
        return std::vector<EventLoop*>(1, baseLoop_);
    }
    else
    {
        return loops_;
    }
}