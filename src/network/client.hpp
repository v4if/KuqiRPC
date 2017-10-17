//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_CLIENT_HPP
#define KUQIKV_CLIENT_HPP


#include "../include/nocopy.hpp"
#include "socket.hpp"
#include "eventloop.hpp"
#include "../debug/debug_new.hpp"

namespace Network {
    class Client: public NoCopy {
    public:
        typedef std::function<void(Channel*)> FuncType;

        Client(EventLoop*);
        ~Client();
        bool connect(const Socket::EndPoint&);
        void onRead(FuncType func_);
        Channel* getChannel();

    private:
        EventLoop* loop_;
        Socket* socket_;
        Channel* chan_;
        FuncType read_;
    };
}

#endif //KUQIKV_CLIENT_HPP
