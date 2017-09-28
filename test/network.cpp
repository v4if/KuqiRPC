#include <iostream>
#include "../src/network/eventloop.hpp"
#include "../src/network/server.hpp"

int main()
{
    Network::EventLoop looper;
    Network::Server serv(&looper, 8000);
    serv.Start();

    MC.atExit([&]() {
        looper.exit();
    });

    serv.onRead([](Network::Channel* chan){
        Network::Buffer& input = chan->getIO().getInput();
        char buff[1024];
        int bytes = sprintf(buff, "%d %d %s", input.cap(), input.size(), input.data());
        Print(buff);

        buff[bytes] = '\0';
        chan->sendOut(buff);
    });

    looper.loop();

    return 0;
}