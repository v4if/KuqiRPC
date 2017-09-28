//
// Created by root on 9/25/17.
//
#include <iostream>
#include "../src/debug/debug_new.hpp"
#include "../src/network/buffer.hpp"

#define HELPER(x) #x
#define PRINT_MACRO(x) #x " = " HELPER(x)
//编译阶段打印宏内容
#pragma message(PRINT_MACRO(new int[5]))

class Test{
public:
    Test(): data_(0x6){}
    int data() { return data_; }
private:
    int data_;
};

int main() {
    char* buff = new char[6];
    delete[] buff;

    Test* t = new Test;
    std::cout << t->data() << std::endl;

    Network::Buffer bf;

//    getchar();

    return 0;
}