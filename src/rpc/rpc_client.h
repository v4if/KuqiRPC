//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_RPC_CLIENT_HPP
#define KUQIKV_RPC_CLIENT_HPP

#include <map>
#include <atomic>
#include "../network/client.hpp"
#include "marshal.h"
#include "future.h"

namespace RPC {
    class RpcClient: public Network::Client {
    public:
        typedef std::function<void(Marshal&)> FutureFunctor;

        static std::atomic_uint32_t R_Id;  // request序列号

        RpcClient(Network::EventLoop* loop);

        template <class A, class R>
        void Call(std::string method, const A* args, Future<R> *fu);

    private:
        std::map<uint32_t, FutureFunctor> futures_;
    };


    inline static uint32_t hash(std::string str) {
        uint32_t ret = 0;
        for (char ch : str) {
            ret += static_cast<u_int32_t >(ch);
        }
        return ret;
    }

    template <class A, class R>
    void RpcClient::Call(std::string method, const A *args, Future<R> *fu) {
        uint32_t h = hash(method);

        A a = (*args);
        uint32_t r_id = R_Id++;
        Marshal marshal(&getChannel()->getIO().getInput(), &getChannel()->getIO().getOutput());
        marshal << h;
        marshal << r_id;
        marshal << a;

        futures_.insert({r_id, std::bind(&Future<R>::Notify, fu, std::placeholders::_1)});

        getChannel()->sendOut();
    }
}

#endif //KUQIKV_RPC_CLIENT_HPP
