//
// Created by root on 9/25/17.
//
#include <iostream>
#include "../src/include/debug_new.hpp"

#define HELPER(x) #x
#define PRINT_MACRO(x) #x " = " HELPER(x)
//编译阶段打印宏内容
#pragma message(PRINT_MACRO(new int[5]))

struct Test{
    int data;
};
int main() {
    char* buff = new char[6];
    delete[] buff;

    Test* t = new Test;
    return 0;
}