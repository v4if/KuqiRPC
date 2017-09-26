#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "socket.hpp"
#include <stdio.h>

namespace Network {
    Socket::Socket():fd_(-1) {
        fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        assert(fd_ != -1);
        SetNonBlock(fd_);
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

    int Socket::Close() {
        int no = 0;
        if (fd_ != -1) {
            no = close(fd_);
            fd_ = -1;
        }
        return no;
    }

    uint32_t Socket::Read(int fd, char* data, uint32_t len) {
        uint32_t cnt = 0;
        ssize_t r;
        for (; cnt < len && (r = read(fd, data + cnt, len - cnt));) {
            if (r == -1) {
                if (errno == EINTR)
                    continue;
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                else
                    printf("read error, %s :(\n", strerror(errno));
                break;
            }
            cnt += r;
        }

        return cnt;
    }

    uint32_t Socket::Write(int fd, char* data, uint32_t len) {
        uint32_t cnt = 0;
        ssize_t r;
        for (;cnt < len && (r = write(fd, data + cnt, len - cnt));) {
            if (r == -1) {
                if (errno == EINTR)
                    continue;
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                else
                    printf("write error, %s :(\n", strerror(errno));
                break;
            }
            cnt += r;
        }

        return cnt;
    }
}