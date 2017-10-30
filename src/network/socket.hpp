#ifndef _SOCKET_HPP_        
#define _SOCKET_HPP_

#include <arpa/inet.h>
#include "sys/types.h"

namespace Network {
    enum { BackLog = 32 };
    class Socket    
    {
    public:
        Socket();
        ~Socket();

        int Bind(uint16_t);
        int Listen();
        int Accept();

        bool Connect(const char *addr, uint16_t port);
        int Close();

        int SetNonBlock(int fd);
        uint32_t Read(int fd, char* data, uint32_t len);
        uint32_t Write(int fd, char* data, uint32_t len);

        int fd() const;
    private:
        int fd_; //sockfd 
    };
}

#endif //_SOCKET_HPP_   
