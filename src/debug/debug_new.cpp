//
// Created by root on 9/26/17.
//
#include "memcheck.hpp"

//全局唯一变量，用于内存泄露检测
MemoryCheck MC;

void* operator new(size_t size, const char* file, int line) {
    return MC.put_(size, file, line);
}

void* operator new[](size_t size, const char* file, int line) {
    return MC.put_(size, file, line);
}

void operator delete(void* ptr) {
    MC.delete_(ptr);
}

void operator delete[](void* ptr) {
    MC.delete_(ptr);
}

void atExit(int signum) {
    MC.exit();
}
static int beforeMain = [&]() -> int {
    try
    {
//        Ctrl + C
        signal(SIGINT, atExit);
//        Kill -9
        signal(SIGTERM, atExit);
    }
    catch(...)
    {
        assert(":(");
    }
}();
