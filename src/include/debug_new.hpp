//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_DEBUG_NEW_HPP_H
#define KUQIKV_DEBUG_NEW_HPP_H

#include <stddef.h>
#include <stdio.h>
#include <cassert>
#include <cstring>

/*
 * 内存泄露检测
 * */

class MemoryCheck{
public:
    // Hash Storage
    #define HASH_TABLE_SIZE 1024
    #define HASH(x) ((x & 0x3FF) % HASH_TABLE_SIZE)

    typedef enum { False, True } RetType;

//    这里没有用std::map进行底层存储，运行时会陷入new的嵌套
    struct bucket {
        bucket* next;
        char* file;
        int line;
        size_t size;
    };

    MemoryCheck() {}
    ~MemoryCheck() {
        bucket* prev = NULL;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            bucket* ptr = pBucket[i];
            while (ptr) {
                printf("Leaked object at %p (size %u, %s:%d)\n",
                       (void*)((char*)ptr + sizeof(bucket)),
                       (unsigned int)ptr->size,
                       ptr->file,
                       ptr->line);

                prev = ptr;
                ptr = ptr->next;
                free(prev->file);
                free(prev);
            }
        }
    }

    void* put_(size_t size, const char* file, int line) {
        size_t block_size = size + sizeof(bucket);
        bucket* ptr = (bucket*)malloc(block_size);
        assert(ptr != NULL);

        void* pointer = (char*)ptr + sizeof(bucket);
        size_t hash = (uint64_t)pointer;
        size_t index = HASH(hash);
        ptr->next = pBucket[index];
        ptr->file = (char*)malloc(strlen(file));
        memcpy(ptr->file, file, strlen(file));
        ptr->line = line;
        ptr->size = size;

        pBucket[index] = ptr;
        return pointer;
    }

    void delete_(void* ptr) {
        size_t hash = (uint64_t)ptr;
        size_t index = HASH(hash);
        bucket* head = pBucket[index];
        bucket* prev = NULL;
        while (head) {
            void* pointer = (void*)((char*)head + sizeof(bucket));
            if (pointer == ptr) {
                if (prev == NULL) {
                    pBucket[index] = head->next;
                } else {
                    prev->next = head->next;
                }
                free(head->file);
                free(head);
                return;
            }
            prev = head;
            head = head->next;
        }

        assert("delete raw memory :(\n");
    }

private:
    bucket* pBucket[HASH_TABLE_SIZE];
};

static MemoryCheck MC;

// 头文件中函数实现只能inline
inline void* operator new(size_t size, const char* file, int line){
    return MC.put_(size, file, line);
}

inline void* operator new[](size_t size, const char* file, int line){
    return MC.put_(size, file, line);
}

inline void operator delete(void* ptr){
    MC.delete_(ptr);
}

inline void operator delete[](void* ptr){
    MC.delete_(ptr);
}

#define new DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)

#endif //KUQIKV_DEBUG_NEW_HPP_H
