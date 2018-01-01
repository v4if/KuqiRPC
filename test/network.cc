#include <iostream>
#include <algorithm>
#include "../src/network/eventloop.h"
#include "../src/network/server.h"

int main()
{
    Network::EventLoop looper;
    Network::Server serv(&looper, 8080);
    serv.Start();

    serv.onMsg([](Network::Channel *chan) {
        Network::CharBuffer &input = chan->getIO().getInput();
        std::cout << input.data() << std::endl;

        chan->sendOut(input.begin(), input.size());
    });

    looper.loop();

    return 0;
}