#include <iostream>
#include "channel.hpp"

namespace Network {
    Channel::Channel(int fd, uint32_t events, Func read_cb):
        io_(fd), events_(events), read_cb_(read_cb), canRead_(false), canWrite_(false), connected_(false) {}

    Channel::~Channel() {}

    int Channel::fd() {
        return io_.fd();
    }
    uint32_t Channel::events() const {
        return events_;
    }

    void Channel::read_cb() {
        if (!canRead_) {
            canRead_ = true;
//            Server端accept
            if (read_cb_)
                read_cb_(this);
        } else {
            io_.tryRead();
            if (read_cb_)
                read_cb_(this);
        }
    }

    void Channel::write_cb() {
        /*
         * Posix 定义了两条与 select 和 非阻塞 connect 相关的规定：
            1）连接成功建立时，socket 描述字变为可写。（连接建立时，写缓冲区空闲，所以可写）
            2）连接建立失败时，socket 描述字既可读又可写。 （由于有未决的错误，从而可读又可写）
         * */
        if (!canWrite_) {
            canWrite_ = true;
        } else {
            io_.tryWrite();
        }
    }

    void Channel::sendOut(const void *data, uint32_t len) {
        if (connected_) {
            CharBuffer& output = io_.getOutput();
            output.write(data, len);
            io_.tryWrite();
        }
    }

    void Channel::sendOut() {
        if (connected_) {
            io_.tryWrite();
        }
    }

    IO& Channel::getIO() {
        return io_;
    }

    void Channel::enableConn() {
        connected_ = true;
    }

    void Channel::enableRead() {
        canRead_ = true;
    }

    void Channel::disableRead() {
        canRead_ = false;
    }

    void Channel::disableConn() {
        connected_ = false;
    }

    void Channel::disableWrite() {
        canWrite_ = false;
    }
}