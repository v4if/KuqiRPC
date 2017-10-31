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
        typedef std::function<void(Channel*)> Functor;

        Channel(int fd, uint32_t events, Functor read_cb);
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
        IoCtl& getIO();

    private:
        uint32_t events_;
        Functor read_cb_;
        Functor write_cb_;
        IoCtl io_;
        bool canRead_; //控制回调
        bool canWrite_;
        bool connected_; //控制发送到对端
    };
}

#endif //_CHANNEL_HPP_
