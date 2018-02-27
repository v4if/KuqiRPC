## KuqiRPC

轻量级 RPC Framework

![cartoon](https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/cartoon.jpg)

## Framework Architecture
* 透明化远程服务调用：代理模式
* 消息编码和解码：序列化
* 通信：单线程 + epoll多路复用

消息里会有携带RequestID，来实现异步返回Future

![arch](http://oowjr8zsi.bkt.clouddn.com/arch.png)
<div align="center"><b>整体架构图</b></div>

<br>
<img align="center" alt="arch" src="https://raw.githubusercontent.com/v4if/KuqiKV/master/doc/img/UMLSequenceDiagram-loop.png">
<div align="center"><b>网络通信时序图</b></div>

## Data Structure
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


    KV_Protocol::GetArgs getArgs{"test_key"};
    Future<KV_Protocol::GetReply> GetFu;
    client.Call("DB::Get", &getArgs, &GetFu);
    GetFu.Wait();
    std::cout << (int)GetFu.Get().ok << " " << GetFu.Get().value << std::endl;

    t1.join();

    return 0;
}
```

## Others
[reflect demo](https://github.com/v4if/blog/issues/34)

[double free](https://github.com/v4if/blog/issues/35)

epool ET|LT模式

循环include -> 前置声明

类内static成员初始化

头文件中函数实现只能inline

不要在头文件定义static

模板的声明和实现必须写在一起

