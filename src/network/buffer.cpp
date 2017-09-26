//
// Created by root on 9/25/17.
//

#include <cstring>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "buffer.hpp"

namespace Network {
    Buffer::Buffer():data_(new char[InitSize]), cap_(InitSize), size_(0), begin_(0), end_(0) {}

    Buffer::~Buffer() {
        delete[] data_;
    }

    void* Buffer::begin() {
        return data_ + begin_;
    }

    void* Buffer::end() {
        return data_ + end_;
    }

    uint32_t Buffer::size() {
        return size_;
    }

    uint32_t Buffer::cap() {
        return cap_;
    }

    uint32_t Buffer::read(void *buff, uint32_t nbytes) {
        if (nbytes > size_)
            nbytes = size_;

        memcpy(buff, data_ + begin_, nbytes);
        begin_ += nbytes;
        size_ -= nbytes;

//        缓冲区已经没有数据
        if (size_ == 0) {
            begin_ = 0;
            end_ = 0;
        }
        return nbytes;
    }

    uint32_t Buffer::write(const void *buff, uint32_t nbytes) {
        uint32_t free = cap_ - size_;
        if (nbytes > free) {
            uint32_t expand = cap_;
            while (end_ + nbytes > expand)
                expand <<= 1;
            adjust(expand);
        }

        assert(cap_ > size_ + nbytes);
        memcpy(data_ + begin_, buff, nbytes);
        end_ += nbytes;
        size_ += nbytes;
        return nbytes;
    }

    void Buffer::adjust(uint32_t capacity) {
        char* buff = new char[capacity];

        assert(buff != NULL);

        memcpy(buff, data_ + begin_, size_);
        delete[] data_;
        data_ = buff;
        begin_ = 0;
        end_ = size_;
        cap_ = capacity;
    }
}