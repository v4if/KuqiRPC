#include <iostream>
#include "channel.hpp"

namespace Network {
    Channel::Channel(int fd, uint32_t events, Func read_cb):
        io_(fd), events_(events), read_cb_(read_cb), canRW_(false) {}

    Channel::~Channel() {}

    int Channel::fd() {
        return io_.fd();
    }
    uint32_t Channel::events() const {
        return events_;
    }

    void Channel::read_cb() {
        if (canRW_)
            io_.tryRead();

        if (read_cb_)
            read_cb_(this);
    }

    void Channel::write_cb() {
        if (canRW_)
            io_.tryWrite();
    }

    void Channel::enableRW() {
        canRW_ = true;
    }

    void Channel::sendOut(const char *data) {
        io_.getOutput().write(data, strlen(data));
        io_.tryWrite();
    }

    IO& Channel::getIO() {
        return io_;
    }
}