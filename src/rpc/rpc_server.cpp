//
// Created by root on 9/28/17.
//

#include <sstream>
#include "rpc_server.hpp"

namespace RPC {
    RpcServer::RpcServer(Network::EventLoop* loop, int port): Network::Server(loop, port) {
        this->onRead([this](Network::Channel* chan){
            Network::Buffer& input = chan->getIO().getInput();
            Print(input.data());

            if (!input.size()) return;

            std::stringstream ss;
            ss.str(input.data());
            std::string method;
            getline(ss, method, ' ');

            auto call = services.find(method);
            if (call != services.end()) {
                auto func = call->second;
                std::string args;
                getline(ss, args, '\n');
                int future = func(args);

                char buff[1024];
                int bytes = sprintf(buff, "%s %d\n", "Get Value", future);
                buff[bytes] = '\0';
                chan->sendOut(buff);
            }
        });
    }

    RpcServer::~RpcServer() {}

    void RpcServer::registerService(std::string method, std::function<int(std::string)> func) {
        if (services.find(method) != services.end()) return;

        services[method] = func;
    }

    void RpcServer::unRegisterService(std::string method) {
        if (services.find(method) != services.end())
            services.erase(method);
    }
}