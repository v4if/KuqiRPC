//
// Created by root on 9/24/17.
//

#include <iostream>
#include <string>
int main() {
    std::string a;
    a[6] = '2';
    std::cout << a.capacity() << std::endl;
    std::cout << "hello world" << std::endl;
}