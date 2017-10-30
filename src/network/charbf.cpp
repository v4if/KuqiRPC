//
// Created by root on 9/25/17.
//

#include <cstring>
#include <stdlib.h>
#include <cassert>
#include "charbf.hpp"

namespace Network {
    CharBuffer::CharBuffer():data_(new char[InitSize + 1]), cap_(InitSize), size_(0), begin_(0), end_(0) {}

    CharBuffer::~CharBuffer() {
        delete[] data_;
    }

    char* CharBuffer::begin() {
        return data_ + begin_;
    }

    char* CharBuffer::end() {
        return data_ + end_;
    }

    char* CharBuffer::data() {
        data_[end_] = '\0';
        return data_ + begin_;
    }

    uint32_t CharBuffer::size() {
        return size_;
    }

    uint32_t CharBuffer::cap() {
        return cap_;
    }

    uint32_t CharBuffer::read(void *buff, uint32_t nbytes) {
        assert(nbytes <= size_);

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

    uint32_t CharBuffer::write(const void *buff, uint32_t nbytes) {
        uint32_t free = cap_ - size_;
        if (nbytes > free) {
            uint32_t expand = cap_;
            while (end_ + nbytes > expand)
                expand <<= 1;
            resize(expand);
        }

        assert(cap_ >= size_ + nbytes);
        memcpy(data_ + end_, buff, nbytes);
        end_ += nbytes;
        size_ += nbytes;
        return nbytes;
    }

    void CharBuffer::resize(uint32_t capacity) {
        char* buff = new char[capacity + 1];

        assert(buff != NULL);

        memcpy(buff, data_ + begin_, size_);
        delete[] data_;
        data_ = buff;
        begin_ = 0;
        end_ = size_;
        cap_ = capacity;
    }

    void CharBuffer::rewind() {
        begin_ = 0;
        end_ = 0;
        size_ = 0;
    }

    uint32_t CharBuffer::canWrite() {
        return cap_ - size_;
    }

    void CharBuffer::advanceTail(uint32_t len) {
        assert(end_ + len <= cap_);

        end_ += len;
        size_ += len;
    }

    void CharBuffer::advanceHead(uint32_t len) {
        assert(len <= size_);

        begin_ += len;
        size_ -= len;

        memmove(data_, data_ + begin_, size_);
        begin_ = 0;
        end_ = size_;
    }

    void CharBuffer::unGet(uint32_t len) {
        assert(len <= begin_);
        begin_ = begin_ - len;
        size_ = size_ - len;
    }
}