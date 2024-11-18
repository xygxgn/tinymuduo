#ifndef _TINYMUDUO_INETADDRESS_H
#define _TINYMUDUO_INETADDRESS_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

class InetAddress
{
public:
    InetAddress();
    explicit InetAddress(const sockaddr_in &addr);
    explicit InetAddress(uint16_t port, std::string ip = "127.0.0.1");
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getSockAddrIn() const;
    const sockaddr* getSockAddr() const;

private:
    sockaddr_in addr_;
};

#endif
