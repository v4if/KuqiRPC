## KuqiRPC

轻量级 RPC Framework

![cartoon](https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/cartoon.jpg)

## Framework Architecture
![UML](https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/UMLSequenceDiagram-loop.png)

![UML](https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/DataMembers-serv.png)

![UML](https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/DataMembers-client.png)

## Tutorial

`Server KV test`
```c++
#include "../src/network/eventloop.h"
#include "../src/rpc/rpc_server.h"
#include "../src/kvtest/db.h"

int main() {
    Network::EventLoop looper;
    RPC::RpcServer serv(&looper, 8080);
    serv.Start();

    KuqiKV::DB db;
    serv.reg("DB::Put", &db, &KuqiKV::DB::Put);
    serv.reg("DB::Get", &db, &KuqiKV::DB::Get);

    looper.loop();

    return 0;
}
```

`Client KV test`
```c++
#include <thread>
#include <iostream>
#include "../src/rpc/future.h"
#include "../src/network/client.h"
#include "../src/rpc/rpc_client.h"
#include "../src/kvtest/kv_protocol.h"

int main() {
    Network::EventLoop looper;
    RPC::RpcClient client(&looper);

    Network::Client::EndPoint endPoint{"127.0.0.1", 8080};
    client.connect(endPoint);

//    另外开启一个线程运行loop
    std::thread t1([&](){
        looper.loop();
    });

    KV_Protocol::PutArgs putArgs{"test_key", "rpc msg"};
    Future<KV_Protocol::PutReply> putFu;
    client.Call("DB::Put", &putArgs, &putFu);

    putFu.Wait();
    std::cout << (int)putFu.Get().ok << std::endl;


    KV_Protocol::PutArgs getArgs{"test_key"};
    Future<KV_Protocol::GetReply> GetFu;
    client.Call("DB::Get", &getArgs, &GetFu);
    GetFu.Wait();
    std::cout << (int)GetFu.Get().ok << " " << GetFu.Get().value << std::endl;

    t1.join();

    return 0;
}
```

## 反射简单框架
```C++
// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include <iostream>
#include <functional>
#include <string>
#include <cstdlib>
#include <map>

class RunTest {
public:
    struct Args{
        int num1;
        int num2;
    };
    typedef int Reply;
    void add(Args* args, Reply* reply) {
        *reply = args->num1 + args->num2;
    }
};

class Caller {
public:
    typedef std::function<void (void*)> Functor;
    
    template<typename A, typename R>
    struct Wrapper {
        A* args;
        R* reply;
        
        Wrapper(A* a, R* r): args(a), reply(r) {}
    };
    
    template<typename C, typename A, typename R>
    bool reg(std::string method, C* obj, void (C::*(call))(A* args, R* reply));
    
    template<typename A, typename R>
    void call(std::string method, A* args, R* reply);
private:
    std::map<std::string, Functor> reflect;
};

template<typename C, typename A, typename R>
bool Caller::reg(std::string method, C* obj, void (C::*(call))(A* args, R* reply)) {
    
    auto iter = reflect.find(method);
    if (iter != reflect.end()) return false;
    
    reflect[method] = [=](void* v) {
        Wrapper<A, R>* w = (Wrapper<A, R>*)v;
        A* args = w->args;
        R* reply = w->reply;
        
        std::cout << args->num1 << " " << args->num2 << std::endl;
        (obj->*call)(args, reply);
    };
    return true;
}

template<typename A, typename R>
void Caller::call(std::string method, A* args, R* reply) {
    auto iter = reflect.find(method);
    if (iter == reflect.end()) return;
    
    Wrapper<A, R> w{args, reply};
    iter->second(&w);
}

int main()
{
    RunTest rt;
    Caller caller;
    caller.reg("RunTest::add", &rt, &RunTest::add);
    
    RunTest::Args args{1,2};
    RunTest::Reply future;
    caller.call("RunTest::add", &args, &future);
    std::cout << future << std::endl;
    std::cout << "Hello, Wandbox!" << std::endl;
}

// GCC reference:
// https://gcc.gnu.org/

/**
Start
1 2
3
Hello, Wandbox!
0
Finish
 */
```

