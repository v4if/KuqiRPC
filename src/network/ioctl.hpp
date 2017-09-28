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
#include "buffer.hpp"
#include "../debug/debug_new.hpp"

namespace Network {
    class IO {
    public:
        IO(int fd);
        ~IO();

        int fd();
        uint32_t tryRead();
        uint32_t tryWrite();
        Buffer& getInput();
        Buffer& getOutput();
    private:
        int fd_;
        Buffer input_;
        Buffer output_;

        uint32_t Read(char* data, uint32_t len);
        uint32_t Write(char* data, uint32_t len);
    };
}

#endif //KUQIKV_IOCTL_HPP
