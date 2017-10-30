//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_BUFFER_H
#define KUQIKV_BUFFER_H


#include <cstdint>
#include "../auxiliary/nocopy.hpp"

namespace Network {
    class CharBuffer : public NoCopy {
    public:
        enum { InitSize = 4 };

        CharBuffer();
        ~CharBuffer();

        uint32_t cap();
        uint32_t size();
        char* begin();
        char* end();
        char* data();
        void advanceTail(uint32_t len); //调整尾指针
        void advanceHead(uint32_t len); //调整头指针
        void unGet(uint32_t len); //回退指针

        uint32_t read(void* buff, uint32_t nbytes); //从缓冲区读数据
        uint32_t write(const void* buff, uint32_t nbytes);

        void rewind(); //把指针从现在读取的位置，重新回到开头
        uint32_t canWrite(); //能写入的数据大小

        void resize(uint32_t capacity); // 调整缓冲大小
    private:
        char* data_;
        uint32_t cap_;
        uint32_t size_;
        uint32_t begin_;
        uint32_t end_;
    };
}

#endif //KUQIKV_BUFFER_H
