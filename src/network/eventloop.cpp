#include <unistd.h>
#include <stdio.h>
#include "eventloop.hpp"

namespace Network {
    EventLoop::EventLoop():poller_(new Poller()), running_(true){}
    
    EventLoop::~EventLoop() {
        delete poller_;
    }

    Poller* EventLoop::getPoller() {
        return poller_;
    }

    void EventLoop::loop() {
        while (running_) {
            poller_->BackendPoll(-1);
        }
    }

    void EventLoop::exit() {
        running_ = false;
    }
}