//
// Created by root on 9/29/17.
//
#include "../src/rpc/rpc_server.hpp"

int main() {
    Network::EventLoop looper;
    RPC::RpcServer serv(&looper, 8000);
    serv.Start();

    MC.atExit([&]() {
        looper.exit();
    });

    serv.registerService("Get", [](std::string key) -> int {
        PrintLn(key.c_str());
        return 0x6;
    });

    looper.loop();

    return 0;
}