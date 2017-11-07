//
// Created by root on 11/7/17.
//

#include "../src/network/eventloop.hpp"
#include "../src/rpc/rpc_server.hpp"
#include "../src/b+tree/db.hpp"

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