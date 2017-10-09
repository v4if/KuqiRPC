//
// Created by root on 9/26/17.
//
#include "memcheck.hpp"

//全局唯一变量，用于内存泄露检测
MemoryCheck MC;

// 重载
void* operator new(size_t size, const char* file, int line) {
    return MC.put_(size, file, line);
}

void* operator new[](size_t size, const char* file, int line) {
    return operator new(size, file, line);
}

// 在没有包含头文件的情况下重载原有new运算符
void* operator new(size_t size)
{
    return operator new(size, "<Unknown>", 0x00);
}

void* operator new[](size_t size)
{
    return operator new(size, "<Unknown Array>", 0xff);
}

void* operator new(size_t size, const std::nothrow_t&) throw()
{
    return operator new(size);
}

void* operator new[](size_t size, const std::nothrow_t&) throw()
{
    return operator new[](size);
}

void operator delete(void* ptr) {
    MC.delete_(ptr);
}

void operator delete[](void* ptr) {
    operator delete(ptr);
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
