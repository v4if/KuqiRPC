//
// Created by root on 9/28/17.
//
#include <sstream>
#include "rpc_server.hpp"

namespace RPC {
    RpcServer::RpcServer(Network::EventLoop* loop, int port): Network::Server(loop, port) {
        this->onRead([this](Network::Channel* chan){
            Network::Buffer& input = chan->getIO().getInput();

            uint32_t hash;
            if (input.size() < sizeof(hash)) {
                std::cout << "rpc args wrong! (: " << input.data() << std::endl;
                return;
            }

//            没有调整缓冲头指针
            input.read(&hash, sizeof(hash));
            std::unordered_map<u_int32_t , RPC_Impl*>::iterator service = services_.find(hash);
            if (service != services_.end()) {
                RPC_Impl* rpc = service->second;
                rpc->getReady(&chan->getIO());
                (*rpc)();
            } else {
                input.unGet(sizeof(hash));
                std::cout << "rpc args wrong! (: " << input.data() << std::endl;
                return;
            }

            chan->sendOut();
        });
    }

    RpcServer::~RpcServer() {
        for (auto service : services_) {
            delete service.second;
        }
    }
}