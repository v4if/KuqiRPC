//
// Created by root on 11/7/17.
//

#include <thread>
#include <iostream>
#include "../src/rpc/future.h"
#include "../src/network/client.hpp"
#include "../src/rpc/rpc_client.hpp"
#include "../src/b+tree/kv_protocol.h"

int main() {
    Network::EventLoop looper;
    RPC::RpcClient client(&looper);

    Network::Client::EndPoint endPoint{"127.0.0.1", 8080};
    client.connect(endPoint);

//    另外开启一个线程运行loop
    std::thread t1([&](){
        looper.loop();
    });

    KV_Protocol::PutArgs putArgs{"test_rpc", "rpc msg"};
    Future<KV_Protocol::PutReply> putFu;
    client.Call("DB::Put", &putArgs, &putFu);

    putFu.Wait();
    std::cout << (int)putFu.Get().ok << std::endl;


    KV_Protocol::PutArgs getArgs{"test_rpc"};
    Future<KV_Protocol::GetReply> GetFu;
    client.Call("DB::Get", &getArgs, &GetFu);
    GetFu.Wait();
    std::cout << (int)GetFu.Get().ok << " " << GetFu.Get().value << std::endl;

    t1.join();

    return 0;
}