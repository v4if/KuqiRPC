//
// Created by root on 9/26/17.
//

#ifndef KUQIKV_IOCTL_HPP
#define KUQIKV_IOCTL_HPP

#include <cstdint>
#include <stdio.h>
#include <zconf.h>
#include <cerrno>
#include <cstring>
#include "charbf.h"

namespace Network {
    class IoCtl {
    public:
        IoCtl(int fd);
        ~IoCtl();

        int fd();
        uint32_t tryRead();
        uint32_t tryWrite();
        CharBuffer& getInput();
        CharBuffer& getOutput();
    private:
        int fd_;
        CharBuffer input_;
        CharBuffer output_;

        uint32_t Read(char* data, uint32_t len);
        uint32_t Write(char* data, uint32_t len);
    };
}

#endif //KUQIKV_IOCTL_HPP
