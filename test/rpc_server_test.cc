//
// Created by root on 9/29/17.
//
#include <iostream>
#include "../src/rpc/rpc_server.hpp"
#include "rpc_obj.hpp"
class Test {
public:
    static void hello(uint8_t i)
    {
//        std::cout << "Hello " << s << '\n';
    }
};
class Object {
public:
    void hello(const std::string& s)
    {
        std::cout << "Hello " << s << '\n';
    }
};
int main() {
    Network::EventLoop looper;
    RPC::RpcServer serv(&looper, 8080);
    serv.Start();

    Rpc_Obj obj;
    serv.reg("Rpc_Obj::Add", &obj, &Rpc_Obj::Add);

    looper.loop();

    return 0;
}