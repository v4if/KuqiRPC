//
// Created by root on 9/26/17.
//
#include <mutex>
#include "ioctl.h"

namespace Network {
    IoCtl::IoCtl(int fd):fd_(fd) {}
    IoCtl::~IoCtl() {}

    int IoCtl::fd() {
        return fd_;
    }

    uint32_t IoCtl::Read(char* data, uint32_t len) {
        uint32_t cnt = 0;
        ssize_t r;
        for (; cnt < len && (r = read(fd_, data + cnt, len - cnt));) {
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

    uint32_t IoCtl::Write(char* data, uint32_t len) {
        uint32_t cnt = 0;
        ssize_t r;
        for (;cnt < len && (r = write(fd_, data + cnt, len - cnt));) {
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

    uint32_t IoCtl::tryRead() {
//        回退指针
        input_.rewind();

        uint32_t nbytes = 0;
        uint32_t len = input_.canWrite();
        uint32_t bytes = Read(input_.end(), len);
        input_.advanceTail(bytes);

        nbytes += bytes;
        while (bytes == len) {
            input_.resize(input_.cap() << 1);
            len = input_.canWrite();
            bytes = Read(input_.end(), len);
            input_.advanceTail(bytes);
            nbytes += bytes;
        }
        return nbytes;
    }

    uint32_t IoCtl::tryWrite() {
        uint32_t len = output_.size();
        uint32_t bytes = 0;
        while (bytes < len) {
            uint32_t n = Write(output_.begin(), output_.size());
            output_.advanceHead(n);
            bytes += n;
        }

        output_.rewind();

        return bytes;
    }

    CharBuffer& IoCtl::getInput() {
        return input_;
    }

    CharBuffer& IoCtl::getOutput() {
        return output_;
    }
}