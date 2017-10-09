//
// Created by root on 9/28/17.
//

#ifndef KUQIKV_RPC_SERVER_HPP
#define KUQIKV_RPC_SERVER_HPP

#include "../network/server.hpp"
#include "../debug/debug_new.hpp"

namespace RPC {
    class RpcServer: public Network::Server{
    public:
        RpcServer(Network::EventLoop*, int);
        ~RpcServer();

        void registerService(std::string method, std::function<int(std::string)>);
        void unRegisterService(std::string method);

    private:
        using Network::Server::onRead;

        std::unordered_map<std::string, std::function<int(std::string)>> services;
    };
}

#endif //KUQIKV_RPC_SERVER_HPP
