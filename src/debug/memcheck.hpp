//
// Created by root on 9/27/17.
//

#ifndef KUQIKV_MEMCHECK_HPP
#define KUQIKV_MEMCHECK_HPP

#include <iostream>
#include <cassert>
#include <cstring>
#include <csignal>
#include <functional>

class MemoryCheck{
public:
    // Hash Storage
#define HASH_TABLE_SIZE 1024
#define HASH(x) ((x & 0x3FF) % HASH_TABLE_SIZE)

//    这里没有用std::map进行底层存储，运行时会陷入new的嵌套
    struct bucket {
        bucket* next;
        char* file;
        int line;
        size_t size;
    };

    MemoryCheck():new_cnt_(0), delete_cnt_(0) {}
    ~MemoryCheck() {
        memory_check_();
    }

    void memory_check_() {
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
        printf("new count: %d, delete count: %d\n", new_cnt_, delete_cnt_);
        assert(new_cnt_ == delete_cnt_);
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
        new_cnt_++;
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
                delete_cnt_++;
                return;
            }
            prev = head;
            head = head->next;
        }

//        assert(!"delete raw memory or double delete an address :(");
    }

    typedef std::function<void(void)> FuncType;
    void atExit(FuncType func) {
        exit_ = func;
    }
    void exit() {
        if (exit_) {
            exit_();
        } else {
            memory_check_();
        }
    }

private:
    bucket* pBucket[HASH_TABLE_SIZE];
    FuncType exit_;

    uint32_t new_cnt_;
    uint32_t delete_cnt_;
};

#endif //KUQIKV_MEMCHECK_HPP
