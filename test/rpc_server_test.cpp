//
// Created by root on 9/29/17.
//
#include "../src/rpc/rpc_server.hpp"
#include "rpc_obj.hpp"

int main() {
    Network::EventLoop looper;
    RPC::RpcServer serv(&looper, 8080);
    serv.Start();

    MC.atExit([&]() {
        looper.exit();
    });

    Rpc_Obj obj;
    serv.registerService("Rpc_Obj::Add", &obj, &Rpc_Obj::Add);

    looper.loop();

    return 0;
}