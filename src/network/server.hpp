#ifndef _SERVER_HPP_        
#define _SERVER_HPP_    

#include <set>
#include "eventloop.hpp"
#include "socket.hpp"
#include "channel.hpp"

namespace Network {
    class Server : public KuqiKV::NoCopy
    {
    public:
        Server(EventLoop*, int);
        ~Server();

        void Start();
        void Close();

    private:
        int listen_port_;
        EventLoop* loop_;
        Socket* socket_;
        Channel* listen_;
        std::set<Channel*> conn_;

        void HandleAccept();
        void HandleRead(Channel *chan);
        void HandleWrite(Channel *chan);
    };
    
}

#endif //_SERVER_HPP_   
