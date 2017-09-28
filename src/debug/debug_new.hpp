//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_DEBUG_NEW_HPP_H
#define KUQIKV_DEBUG_NEW_HPP_H

#include <stddef.h>
#include <stdio.h>
#include <new>
#include "memcheck.hpp"

extern void* operator new(size_t size, const char* file, int line);

extern void* operator new[](size_t size, const char* file, int line);

extern void operator delete(void* ptr);

extern void operator delete[](void* ptr);

extern MemoryCheck MC;

#define new DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)

#define Print(message) \
    printf("%s:%d %s", __FILE__, __LINE__, message);
#define PrintLn(message) \
    printf("%s:%d %s", __FILE__, __LINE__, message);

#endif //KUQIKV_DEBUG_NEW_HPP_H
