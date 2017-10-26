//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_DEBUG_NEW_HPP_H
#define KUQIKV_DEBUG_NEW_HPP_H

#include <stddef.h>
#include <stdio.h>
#include <new>
#include "memcheck.hpp"

void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);

#define new DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)

#define malloc(s) ((void*)(new char[s]))
#define free(p) delete[] (char*)(p)

extern MemoryCheck MC;

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif //KUQIKV_DEBUG_NEW_HPP_H
