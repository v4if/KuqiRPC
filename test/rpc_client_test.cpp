//
// Created by root on 10/16/17.
//

#include <thread>
#include "../src/debug/debug_new.hpp"
#include "../src/network/client.hpp"
#include "../src/rpc/rpc_client.hpp"
#include "rpc_obj.hpp"

int main() {
    Network::EventLoop looper;
    RPC::RpcClient client(&looper);

    MC.atExit([&]() {
        looper.exit();
    });

    client.onRead([](Network::Channel* chan){
        Network::Buffer& input = chan->getIO().getInput();

        uint32_t future;
        assert (input.size() >= sizeof(future));
        input.read(&future, sizeof(future));
        std::cout << future << std::endl;
    });

    Network::Socket::EndPoint endPoint{"127.0.0.1", 8080};
    client.connect(endPoint);

//    另外开启一个线程运行loop
    std::thread t1([&](){
        looper.loop();
    });

    Rpc_Obj::Args args{1,8};
    int reply = 0;
    client.Call("Rpc_Obj::Add", &args, &reply);

    t1.join();

    return 0;
}