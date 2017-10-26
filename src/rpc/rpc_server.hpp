//
// Created by root on 9/28/17.
//

#ifndef KUQIKV_RPC_SERVER_HPP
#define KUQIKV_RPC_SERVER_HPP


#include <unordered_map>
#include "../network/server.hpp"
#include "rpc.hpp"
#include "../debug/debug_new.hpp"

namespace RPC {
    class RpcServer: public Network::Server{
    public:
        RpcServer(Network::EventLoop*, int);
        ~RpcServer();

        template <typename T1, typename A, typename R>
        void reg(std::string method, T1 *obj, void (T1::*(func))(const A *a, R *r));

    private:
        using Network::Server::onRead;

        std::unordered_map<u_int32_t , RPC_Impl*> services_;
    };
}

template <typename T1, typename A, typename R>
void RPC::RpcServer::reg(std::string method, T1 *obj, void (T1::*(func))(const A *a, R *r)){
    uint32_t proc = RPC_Impl::hash(method);
    if (services_.find(proc) != services_.end()) return;

    services_[proc] = new RPC_Impl(method, obj, func);
}

#endif //KUQIKV_RPC_SERVER_HPP
