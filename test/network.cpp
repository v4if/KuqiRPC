#include <iostream>
#include <cassert>
#include "../src/network/eventloop.hpp"
#include "../src/network/server.hpp"

int main()
{
    Network::EventLoop looper;
    Network::Server serv(&looper, 8080);
    serv.Start();

    looper.loop();

    return 0;
}