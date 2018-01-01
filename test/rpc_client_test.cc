//
// Created by root on 10/16/17.
//

#include <thread>
#include <iostream>
#include "../src/network/client.h"
#include "../src/rpc/rpc_client.h"
#include "rpc_obj.h"

int main() {
    Network::EventLoop looper;
    RPC::RpcClient client(&looper);

    Network::Client::EndPoint endPoint{"127.0.0.1", 8080};
    client.connect(endPoint);

//    另外开启一个线程运行loop
    std::thread t1([&](){
        looper.loop();
    });

    Rpc_Obj::Args args{ 1, 8 };
    Future<uint32_t> fu;
    client.Call("Rpc_Obj::Add", &args, &fu);

    fu.Wait();

    std::cout << fu.Get() << std::endl;

    t1.join();

    return 0;
}