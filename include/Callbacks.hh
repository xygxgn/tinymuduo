#ifndef _TINYMUDUO_CALLBACKS_H
#define _TINYMUDUO_CALLBACKS_H

#include "Timestamp.hh"

#include <memory>
#include <functional>

class Buffer;
class TcpConnection;
// class Timestamp;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;
using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*, Timestamp)>;

class Callbacks
{
public:
    Callbacks();
    ~Callbacks();
private:
};



#endif