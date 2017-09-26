//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_BUFFER_H
#define KUQIKV_BUFFER_H


#include <cstdint>
#include "../include/nocopy.hpp"
#include "../include/debug_new.hpp"

namespace Network {
    class Buffer : public KuqiKV::NoCopy {
    public:
        enum { InitSize = 4 };

        Buffer();
        ~Buffer();

        uint32_t cap();
        uint32_t size();
        void* begin();
        void* end();

        uint32_t read(void* buff, uint32_t nbytes); // 从缓冲区读数据
        uint32_t write(const void* buff, uint32_t nbytes);

        void adjust(uint32_t capacity); // 调整缓冲大小
    private:
        char* data_;
        uint32_t cap_;
        uint32_t size_;
        uint32_t begin_;
        uint32_t end_;
    };
}

#endif //KUQIKV_BUFFER_H
