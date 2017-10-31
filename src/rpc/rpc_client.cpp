//
// Created by root on 10/16/17.
//

#include "rpc_client.hpp"

namespace RPC {
    std::atomic_uint32_t RpcClient::R_Id(0);
    RpcClient::RpcClient(Network::EventLoop *loop): Network::Client(loop) {
        onMsg([this](Network::Channel *chan) {
            Network::IoCtl &io = chan->getIO();
            Marshal marshal(&io.getInput(), &io.getOutput());

            uint32_t r_id;
            marshal >> r_id;

            auto it = futures_.find(r_id);
            if (it != futures_.end()) {
                FutureFunctor fn = it->second;
                fn(marshal);

                futures_.erase(it);
            }
        });
    }
}