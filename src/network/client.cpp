//
// Created by root on 10/16/17.
//

#include <assert.h>
#include "client.hpp"

namespace Network {
    Client::Client(EventLoop* loop): loop_(loop), socket_(new Socket) {}

    Client::~Client() {
        close(chan_->fd());
        delete(socket_);
        delete(chan_);
    }

    void Client::onMsg(FuncType func) {
        read_ = func;
    }

    bool Client::connect(const EndPoint& endPoint) {
        assert(socket_->Connect(endPoint.address_, endPoint.port_));

        socket_->SetNonBlock(socket_->fd());
        chan_ = new Channel(socket_->fd(), EPOLLIN|EPOLLOUT|EPOLLET, [&](Channel* chan){
            CharBuffer& read_buff = chan->getIO().getInput();
            if (read_buff.size() == 0) {
                // 对端关闭
                close(chan->fd());
            } else {
                if (read_) read_(chan);
            }
        });
        chan_->enableConn();
        chan_->enableRead();
        loop_->getPoller()->registerChannel(chan_);
    }

    Channel* Client::getChannel() {
        return chan_;
    }
}