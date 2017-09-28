#include <cassert>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include "poller.hpp"

namespace Network {
    Poller::Poller() {
        assert((fd_ = epoll_create1(EPOLL_CLOEXEC)) >= 0);
    }

    Poller::~Poller() {
        close(fd_);
    }

    void Poller::registerChannel(Channel* chan) {
        struct epoll_event event;
        event.events = chan->events();
        event.data.ptr = chan;
        assert(!epoll_ctl(fd_, EPOLL_CTL_ADD, chan->fd(), &event));
    }

    void Poller::unregisterChannel(Channel* chan) {
        struct epoll_event event;
        memset(&event, 0, sizeof(event));
        event.events = chan->events();
        event.data.ptr = chan;
        assert(!epoll_ctl(fd_, EPOLL_CTL_DEL, chan->fd(), &event));
    }

    void Poller::backendPoll(int ms) {
        int ready = epoll_wait(fd_, events_, MaxEvents, ms);
        assert(!(ready == -1 && errno != EINTR));

        for (; --ready >= 0; ) {
            Channel *channel = (Channel *)events_[ready].data.ptr;
            uint32_t event = events_[ready].events;
            if (event & EPOLLIN) {
                channel->read_cb();
            } else if (event & EPOLLOUT) {
                channel->write_cb();
            } else {
                assert(0);
            }
            
            // assert(!epoll_ctl(fd_, EPOLL_CTL_MOD, channel->fd(), &events_[ready]));
        }
    }
}