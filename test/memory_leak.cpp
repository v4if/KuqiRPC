//
// Created by root on 9/25/17.
//
#include <iostream>
#include <vector>
#include "../src/debug/debug_new.hpp"


#define HELPER(x) #x
#define PRINT_MACRO(x) #x " = " HELPER(x)
//编译阶段打印宏内容
#pragma message(PRINT_MACRO(new int[5]))

class Test{
public:
    Test(): data_(new int[2]){}
    int* data_;
};

int main() {
    char* buff = new char[6];
    delete[] buff;

    Test* b = new Test;
    delete(b);
    char* a= (char*)malloc(4);

    char* c = new char[11];

    std::string out;
    std::cout << out.capacity() << std::endl;
    out = "123456789abcdef\n";

//    getchar();

    return 0;
}