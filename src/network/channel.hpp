#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include <memory>  //unique_ptr
#include <functional>
#include "sys/types.h"
#include "buffer.hpp"
#include "ioctl.hpp"
#include "../debug/debug_new.hpp"

namespace Network {
    class Channel
    {
    public:
        using Func = std::function<void(Channel*)>;
        Channel(int, uint32_t, Func);
        ~Channel();

        int fd();
        uint32_t events() const;

        void read_cb();
        void write_cb();
        void sendOut(const char*);
        void enableRW();
        IO& getIO();

    private:
        uint32_t events_;
        Func read_cb_;
        Func write_cb_;
        IO io_;
        bool canRW_; //对端是否建立连接
    };
}

#endif //_CHANNEL_HPP_
