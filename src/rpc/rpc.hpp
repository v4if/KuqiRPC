//
// Created by root on 10/15/17.
//

#ifndef KUQIKV_RPC_HPP
#define KUQIKV_RPC_HPP

#include <functional>
#include "../debug/debug_new.hpp"

namespace RPC {
    class RPC_Impl {
    public:
        template<typename T1, typename T2, typename T3>
        RPC_Impl(const std::string method, T1* obj, void (T1::*(func)) (const T2*, T3*));

        void getReady(Network::IO* io_ptr) {
            io_ptr_ = io_ptr;
        }

        inline void operator()(){
            func_();
        }

        inline static uint32_t hash(std::string str) {
            uint32_t ret = 0;
            for (char ch : str) {
                ret += static_cast<u_int32_t >(ch);
            }
            return ret;
        }
    private:
        std::function<void()> func_;
        Network::IO* io_ptr_;
    };

    template <class T1, class T2, class T3>
    RPC_Impl::RPC_Impl(const std::string method, T1 *obj, void (T1::*(func))(const T2 *, T3 *)) {
        func_ = [this, obj, func]() {
            Network::Buffer& input = io_ptr_->getInput();
            T2 args;
            input.read(&args, sizeof(args));

            T3 future;
            (obj->*func)(&args, &future);
            Network::Buffer& out = io_ptr_->getOutput();
            out.write(&future, sizeof(future));
        };
    }
}

#endif //KUQIKV_RPC_HPP
