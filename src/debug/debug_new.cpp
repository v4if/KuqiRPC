//
// Created by root on 9/26/17.
//
#include <stddef.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <string>

// 头文件中函数实现只能inline
 void* operator new(size_t size, const char* file, int line){
//    return MC.put_(size, file, line);
}

 void* operator new[](size_t size, const char* file, int line){
//    return MC.put_(size, file, line);
}

 void operator delete(void* ptr) {
//    MC.delete_(ptr);
}

 void operator delete[](void* ptr) {
//    MC.delete_(ptr);
}