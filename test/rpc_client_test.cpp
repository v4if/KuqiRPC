//
// Created by root on 10/16/17.
//

#include <thread>
#include <iostream>
#include "../src/network/client.hpp"
#include "../src/rpc/rpc_client.hpp"
#include "rpc_obj.hpp"

int main() {
    Network::EventLoop looper;
    RPC::RpcClient client(&looper);

    Network::Client::EndPoint endPoint{"127.0.0.1", 8080};
    client.connect(endPoint);

//    另外开启一个线程运行loop
    std::thread t1([&](){
        looper.loop();
    });

    Rpc_Obj::Args args{1,8};
    int reply = 0;
    uint8_t i = 2;
    Future<uint8_t> fu;
    client.Call("Rpc_Obj::Add", &i, &fu);

    fu.Wait();

    std::cout << (int)fu.Get() << std::endl;

    t1.join();

    return 0;
}