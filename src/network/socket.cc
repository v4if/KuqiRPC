#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "socket.h"
#include <stdio.h>
#include <netinet/tcp.h>

namespace Network {
    Socket::Socket():fd_(-1) {
        fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        assert(fd_ != -1);

        int yes = 1;
        setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
        setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes));
    }
    
    Socket::~Socket() {
        if (fd_ != -1) {
            close(fd_);
            fd_ = -1;
        }
    }

    int Socket::fd() const {
        return fd_;
    }

    int Socket::SetNonBlock(int fd) {
        int value = fcntl(fd, F_GETFL, 0);
        assert(value != -1);
        return !fcntl(fd, F_SETFL, value | O_NONBLOCK);
    }

    int Socket::Bind(uint16_t port) {
        struct sockaddr_in serv;
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_port = htons(port);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);
        assert(bind(fd_, (const struct sockaddr *)&serv, sizeof(serv)) == 0);
        return 0;
    }

    int Socket::Listen() {
        assert(listen(fd_, BackLog) == 0);
        return 0;
    }

    int Socket::Accept() {
        struct sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t len = sizeof(client);
        int fd = accept(fd_, (struct sockaddr *)&client, &len);

        assert(fd != -1);
        return fd;
    }

    bool Socket::Connect(const char *addr, uint16_t port)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family      = AF_INET;
        server.sin_port        = htons(port);
        server.sin_addr.s_addr = inet_addr(addr);

        return !connect(fd_, (const struct sockaddr *)&server, sizeof(server));
    }

    int Socket::Close() {
        int no = 0;
        if (fd_ != -1) {
            no = close(fd_);
            fd_ = -1;
        }
        return no;
    }
}