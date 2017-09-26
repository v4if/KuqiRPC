#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include <memory>  //unique_ptr
#include <functional>
#include "sys/types.h"
#include "buffer.hpp"

namespace Network {
    class Channel
    {
    public:
        using Func = std::function<void(Channel*)>;
        Channel(int, uint32_t, Func, Func);
        ~Channel();
        
        uint32_t events() const;
        int fd() const;
        void read_cb();
        void write_cb();
    private:
        int fd_;
        uint32_t events_;
        Func read_cb_;
        Func write_cb_;
        Buffer input_;
        Buffer output_;
    };
}

#endif //_CHANNEL_HPP_
