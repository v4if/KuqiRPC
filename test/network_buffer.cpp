#include <iostream>
#include "../src/network/buffer.hpp"

class Test {
public:
    Network::Buffer buff;
};
int main()
{
    std::string out;

    char temp[] = "Hello World";
    Network::Buffer buff;
    std::cout << buff.cap() << buff.size() << std::endl;
    out = "cap: " + std::to_string(buff.cap()) + ", size: " + std::to_string(buff.size()) + "\n";
    std::to_string(buff.size());
    out = "cap: " + std::to_string(buff.cap()) + ", size: " + std::to_string(buff.size()) + "\n";
    std::cout << out;

    buff.write(temp, sizeof(temp));
    std::cout << buff.begin() << " " << buff.end() << std::endl;
    out = "cap: " + std::to_string(buff.cap()) + ", size: " + std::to_string(buff.size()) + "\n";
    std::cout << out;

    uint32_t nbytes = buff.read(temp, sizeof(temp));
    std::cout << "read bytes: " << nbytes << " " << temp << std::endl;
    std::cout << buff.begin() << " " << buff.end() << std::endl;
    out = "cap: " + std::to_string(buff.cap()) + ", size: " + std::to_string(buff.size()) + "\n";
    std::cout << out;

//    再次写入缓冲区
    buff.write(temp, sizeof(temp));
    std::cout << buff.begin() << " " << buff.end() << std::endl;
    out = "cap: " + std::to_string(buff.cap()) + ", size: " + std::to_string(buff.size()) + "\n";
    std::cout << out;

    Test t;
    out = "cap: " + std::to_string(t.buff.cap()) + ", size: " + std::to_string(t.buff.size()) + "\n";
    std::cout << out;
}