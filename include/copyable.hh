#ifndef _TINYMUDUO_COPYABLE_H
#define _TINYMUDUO_COPYABLE_H

class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif
