#ifndef _TINYMUDUO_INETADDRESS_H
#define _TINYMUDUO_INETADDRESS_H

#include "tinymuduo/copyable.hh"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

class InetAddress : public copyable
{
public:
    explicit InetAddress(const sockaddr_in &addr);
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getSockAddrIn() const;
    const sockaddr* getSockAddr() const;
    void setSockAddrIn(const sockaddr_in &addr) { addr_ = addr; }

private:
    sockaddr_in addr_;
};

#endif
