#include "tinymuduo/InetAddress.hh"

#include <strings.h>


InetAddress::InetAddress(const sockaddr_in &addr) 
    : addr_(addr) 
{
}

InetAddress::InetAddress(uint16_t port, std::string ip)
{
    ::bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr.s_addr);
}

std::string InetAddress::toIp() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr.s_addr, buf, sizeof(buf));
    return std::string(buf);
}

uint16_t InetAddress::toPort() const
{
    return ntohs(addr_.sin_port);
}

std::string InetAddress::toIpPort() const
{
    return toIp() + std::to_string(toPort());
}

const sockaddr_in* InetAddress::getSockAddrIn() const
{
    return &addr_;
}

const sockaddr* InetAddress::getSockAddr() const
{
    return (sockaddr*)(&addr_);
}
