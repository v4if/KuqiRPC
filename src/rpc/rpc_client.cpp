//
// Created by root on 10/16/17.
//

#include "rpc_client.hpp"
#include "rpc.hpp"

namespace RPC {
    RpcClient::RpcClient(Network::EventLoop *loop): Network::Client(loop) {}
}