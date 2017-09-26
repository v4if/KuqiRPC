#include "channel.hpp"

namespace Network {
    Channel::Channel(int fd, uint32_t events, Func read_cb, Func write_cb): 
        fd_(fd), events_(events), read_cb_(read_cb), write_cb_(write_cb) {}

    Channel::~Channel() {}

    int Channel::fd() const {
        return fd_;
    }

    uint32_t Channel::events() const {
        return events_;
    }

    void Channel::read_cb() {
        if (read_cb_)
            read_cb_(this);
    }

    void Channel::write_cb() {
        if (write_cb_)
            write_cb_(this);
    }
}