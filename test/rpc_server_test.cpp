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

//    MC.atExit([&]() {
//        looper.exit();
//    });

    Rpc_Obj obj;
    serv.reg("Rpc_Obj::Add", &obj, &Rpc_Obj::Add);

    looper.loop();


//    typedef std::function<void(const std::string&)> ExampleFunction;
//    Object instance;
//    std::string str("World");
//    ExampleFunction f = std::bind(&Object::hello, &instance,
//                                  std::placeholders::_1);
//    f(str);
//
//    struct caller_wrapper {
//
//        static void fn(const std::string& s, void*) {
//
//            return;
//        }
//    };
//
//
//    std::function<void(const std::string& s)> fn = std::bind(&caller_wrapper::fn,   std::placeholders::_1, (void*)0);
//    fn(str);

    return 0;
}