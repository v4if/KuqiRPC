#include <iostream>
#include <algorithm>
#include "../src/network/eventloop.hpp"
#include "../src/network/server.hpp"
#include "../src/debug/debug_new.hpp"

int main()
{
    Network::EventLoop looper;
    Network::Server serv(&looper, 8080);
    serv.Start();

    MC.atExit([&]() {
        looper.exit();
    });

    serv.onMsg([](Network::Channel *chan) {
        Network::CharBuffer &input = chan->getIO().getInput();
        std::cout << input.data() << std::endl;

        chan->sendOut(input.begin(), input.size());
    });

    looper.loop();

    return 0;
}