//
// Created by root on 9/26/17.
//
#include <iostream>

int main () {
    int* v = (int*)malloc(sizeof(int));
    std::cout << v << " " << v + 1 << std::endl;

    char* ch = (char*)malloc(sizeof(int));
    std::cout << (void*)ch << " " << (void*)(ch + 1) << std::endl;

    return 0;
}