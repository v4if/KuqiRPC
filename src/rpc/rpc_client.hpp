//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_RPC_CLIENT_HPP
#define KUQIKV_RPC_CLIENT_HPP

#include "../network/client.hpp"
#include "rpc.hpp"

namespace RPC {
    class RpcClient: public Network::Client {
    public:
        RpcClient(Network::EventLoop* loop);

        template <class T1, class T2>
        void Call(std::string method, const T1* args, T2* reply);
    };

    template <class T1, class T2>
    void RpcClient::Call(std::string method, const T1 *args, T2 *reply) {
        uint32_t h = RPC::RPC_Impl::hash(method);
        Network::Buffer& out = getChannel()->getIO().getOutput();
        out.write(&h, sizeof(h));
        out.write(args, sizeof(T1));
        getChannel()->sendOut();
    }
}

#endif //KUQIKV_RPC_CLIENT_HPP
