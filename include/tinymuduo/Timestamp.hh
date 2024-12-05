#ifndef _TINYMUDUO_TIMESTAMP_H
#define _TINYMUDUO_TIMESTAMP_H

#include "tinymuduo/copyable.hh"

#include <string>

class Timestamp : public copyable
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    static Timestamp now();
    std::string toString() const;
private:
    int64_t microSecondsSinceEpoch_;
};

#endif
