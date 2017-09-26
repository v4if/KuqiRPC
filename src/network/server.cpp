#include <cassert>
#include <unistd.h>
#include <cstring>
#include "server.hpp"
#include <stdio.h>

namespace Network {
    Server::Server(EventLoop* loop, int port):listen_port_(port), loop_(loop), socket_(new Socket()){}

    Server::~Server() {
        socket_->Close();
        delete socket_;
        delete listen_;

//        for (Channel* chan : conn_) {
//            close(chan->fd());
//            delete chan;
//        }
    }

    void Server::Start() {
        assert(socket_->Bind(listen_port_) == 0 && socket_->Listen() == 0);
        listen_ = new Channel(socket_->fd(), EPOLLIN|EPOLLET, [this](Channel*){
            HandleAccept();
        }, static_cast<Channel::Func>(0));
        loop_->getPoller()->RegisterChannel(listen_);
    }

    void Server::Close() {
        socket_->Close();
        delete socket_;
        delete listen_;

//        for (Channel* chan : conn_) {
//            close(chan->fd());
//            delete chan;
//        }
    }

    void Server::HandleAccept() {
        int fd = socket_->Accept();
        socket_->SetNonBlock(fd);
        Channel* conn = new Channel(fd, EPOLLIN|EPOLLOUT|EPOLLET, [this](Channel* chan){
            HandleRead(chan);
        }, [this](Channel* chan) {
            HandleWrite(chan);
        });
        conn->enableRW();
        loop_->getPoller()->RegisterChannel(conn);
//        conn_.insert(conn);
    }

    void Server::HandleRead(Channel *chan) {
//        char buff[2046];
//        memset(buff, 0, sizeof(buff));
//        uint32_t bytes = socket_->Read(chan->fd(), buff, 2);
//
//        if (bytes == 0) {
//            close(chan->fd());
//            conn_.erase(chan);
//            delete chan;
//        } else {
//            buff[bytes] = '\0';
//            printf("%p :] bytes: %d :)%s", chan, bytes, buff);
//            char send[]="Hello world\n";
//            socket_->Write(chan->fd(), send, sizeof(send));
//        }
        print(chan->getIO().getInput().begin());
    }

    void Server::HandleWrite(Channel *chan) {

    }
}