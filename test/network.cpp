#include <iostream>
#include <algorithm>
#include "../src/network/eventloop.hpp"
#include "../src/network/server.hpp"

int main()
{
    Network::EventLoop looper;
    Network::Server serv(&looper, 8080);
    serv.Start();

    MC.atExit([&]() {
        looper.exit();
    });

    serv.onRead([](Network::Channel* chan){
        Network::Buffer& input = chan->getIO().getInput();
        std::cout << input.data() << std::endl;

        chan->sendOut(input.begin(), input.size());
    });

    looper.loop();

    return 0;
}