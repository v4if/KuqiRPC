//
// Created by root on 9/28/17.
//
#include <sstream>
#include "rpc_server.hpp"

namespace RPC {
    RpcServer::RpcServer(Network::EventLoop* loop, int port): Network::Server(loop, port) {
        this->onMsg([this](Network::Channel *chan) {
            Marshal marshal(&chan->getIO().getInput(), &chan->getIO().getOutput());
            uint32_t xid;
            marshal >> xid;

            if (map_.count(xid) > 0) {
                Functor *h = map_[xid];
                (*h)(marshal);
                chan->sendOut();
            }
        });
    }

    RpcServer::~RpcServer() {
        for (auto map : map_) {
            delete map.second;
        }
    }
}