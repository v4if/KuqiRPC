#include <cassert>
#include <unistd.h>
#include <algorithm>
#include "server.hpp"

namespace Network {
    Server::Server(EventLoop* loop, int port):listen_port_(port), loop_(loop), socket_(new Socket){}

    Server::~Server() {
        socket_->Close();
        delete socket_;
        if (listen_)
            delete listen_;

        for (auto it = conn_.begin(); it != conn_.end();) {
            close((*it)->fd());
            conn_.erase(it);
            delete (*it);
        }
    }

    void Server::Start() {
        assert(socket_->Bind(listen_port_) == 0 && socket_->Listen() == 0);
        listen_ = new Channel(socket_->fd(), EPOLLIN|EPOLLET, [this](Channel*){
            HandleAccept();
        });
        loop_->getPoller()->registerChannel(listen_);
    }

    void Server::Close() {
        socket_->Close();
        delete socket_;
        if (listen_)
            delete listen_;

        for (auto it = conn_.begin(); it != conn_.end();) {
            close((*it)->fd());
            conn_.erase(it);
            delete (*it);
        }
    }

    void Server::HandleAccept() {
        int fd = socket_->Accept();
        socket_->SetNonBlock(fd);
        Channel* conn = new Channel(fd, EPOLLIN|EPOLLOUT|EPOLLET, [&](Channel* chan) {
            Buffer& input = chan->getIO().getInput();
            if (input.size() == 0) {
                // 对端关闭
                close(chan->fd());

                auto it = std::find(conn_.begin(), conn_.end(), chan);
                if (it != conn_.end()) {
                    conn_.erase(it);
                }

                delete chan;
            } else {
                on_read_(chan);
            }
        });

        loop_->getPoller()->registerChannel(conn);
        conn->enableRW();
        conn_.push_back(std::move(conn));
    }


    void Server::onRead(FuncType func) {
        on_read_ = func;
    }
}