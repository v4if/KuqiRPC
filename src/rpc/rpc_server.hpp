//
// Created by root on 9/28/17.
//

#ifndef KUQIKV_RPC_SERVER_HPP
#define KUQIKV_RPC_SERVER_HPP


#include <unordered_map>
#include "../network/server.hpp"
#include "../debug/debug_new.hpp"
#include "rpc.hpp"

namespace RPC {
    class RpcServer: public Network::Server{
    public:
        RpcServer(Network::EventLoop*, int);
        ~RpcServer();

        template <class T1, class T2, class T3>
        void registerService(std::string method, T1* obj, void (T1::*(func)) (const T2* args, T3* future)){
            uint32_t h = RPC_Impl::hash(method);
            if (services_.find(h) != services_.end()) return;

            services_[h] = new RPC_Impl(method, obj, func);
        }

    private:
        using Network::Server::onRead;

        std::unordered_map<u_int32_t , RPC_Impl*> services_;


    };
}

#endif //KUQIKV_RPC_SERVER_HPP
