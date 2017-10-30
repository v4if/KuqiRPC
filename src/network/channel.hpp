#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include <functional>
#include "sys/types.h"
#include "charbf.hpp"
#include "ioctl.hpp"

namespace Network {
    class Channel
    {
    public:
        using Func = std::function<void(Channel*)>;
        Channel(int fd, uint32_t events, Func read_cb);
        ~Channel();

        int fd();
        uint32_t events() const;

        void read_cb();
        void write_cb();
        void sendOut(const void* data, uint32_t len);
        void sendOut();
        void enableRead();
        void enableConn();
        void disableRead();
        void disableConn();
        void disableWrite();
        IO& getIO();

    private:
        uint32_t events_;
        Func read_cb_;
        Func write_cb_;
        IO io_;
        bool canRead_; //控制回调
        bool canWrite_;
        bool connected_; //控制发送到对端
    };
}

#endif //_CHANNEL_HPP_
