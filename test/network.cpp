#include <iostream>
#include <cassert>
#include "../src/network/eventloop.hpp"
#include "../src/network/server.hpp"
#include "../src/network/buffer.hpp"
#include <string>

std::string bufferToString(Network::Buffer b) {
    std::string out;
    out = "cap: " + std::to_string(b.cap()) + ", size: " + std::to_string(b.size()) + "\n";
    return out;
}
int main()
{
//  Network::EventLoop looper;
//  Network::Server serv(&looper, 8080);
//  serv.Start();
//
//    looper.loop();
    char temp[] = "h";
    Network::Buffer buff;
    std::string out = bufferToString(buff);
    std::cout << out;
    buff.write(temp, sizeof(temp));
    buff.read(temp, sizeof(temp) - 1);
    std::cout << bufferToString(buff);
    std::cout << temp << std::endl;

    buff.read(temp, sizeof(temp) - 1);
    std::cout << bufferToString(buff);
    std::cout << temp << std::endl;

    std::cout << buff.begin() << " " << buff.end() << std::endl;
}