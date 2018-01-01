//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_CLIENT_HPP
#define KUQIKV_CLIENT_HPP


#include "socket.h"
#include "eventloop.h"

namespace Network {
    class Client: public NoCopy {
    public:
        struct EndPoint{
            const char* address_;
            uint16_t port_;
        };
        
        typedef std::function<void(Channel*)> FuncType;

        Client(EventLoop*);
        ~Client();
        bool connect(const EndPoint&);
        void onMsg(FuncType func_);
        Channel* getChannel();

    private:
        EventLoop* loop_;
        Socket* socket_;
        Channel* chan_;
        FuncType read_;
    };
}

#endif //KUQIKV_CLIENT_HPP
