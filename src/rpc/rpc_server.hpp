//
// Created by root on 9/28/17.
//

#ifndef KUQIKV_RPC_SERVER_HPP
#define KUQIKV_RPC_SERVER_HPP


#include <unordered_map>
#include <map>
#include <cxxabi.h>
#include <assert.h>
#include <memory>
#include "../network/server.hpp"
#include "marshal.h"

namespace RPC {
    class RpcServer: public Network::Server{
    public:
        typedef std::function<void (Marshal&)> CallbackFunctor;

        class Functor {
        public:
            Functor():fn_(0) {}

            template <typename C, typename A, typename R>
            void MakeFn(C *obj, void (C::*(mtd))(const A *a, R *r)) {
                fn_ = [obj, mtd](Marshal& marshal){
                    uint32_t r_id;
                    marshal >> r_id;

                    A a; R r;
                    marshal >> a;
                    (obj->*mtd)(&a, &r);
                    marshal << r_id;
                    marshal << r;
                };
            }

            void operator() (Marshal& marshal){
                fn_(marshal);
            }
        private:
            CallbackFunctor fn_;
        };

        RpcServer(Network::EventLoop*, int);
        ~RpcServer();

        template <typename C, typename A, typename R>
        void reg(std::string method, C *obj, void (C::*(func))(const A *a, R *r));

    private:
        using Network::Server::onMsg;
        std::map<uint32_t, Functor*> map_;
    };

    inline static uint32_t hash(std::string str) {
        uint32_t ret = 0;
        for (char ch : str) {
            ret += static_cast<u_int32_t >(ch);
        }
        return ret;
    }

    template <typename C, typename A, typename R>
    void RPC::RpcServer::reg(std::string method, C *obj, void (C::*(mtd))(const A *a, R *r)){
        uint32_t xid = hash(method);

        assert(map_.count(xid) == 0);

        Functor *handler = new Functor;
        handler->MakeFn(obj, mtd);
        map_.insert(std::make_pair(xid, handler));
    }
}

#endif //KUQIKV_RPC_SERVER_HPP
