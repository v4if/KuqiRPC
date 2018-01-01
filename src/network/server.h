#ifndef _SERVER_HPP_        
#define _SERVER_HPP_    

#include <vector>
#include <functional>
#include "eventloop.h"
#include "socket.h"
#include "channel.h"

namespace Network {
    class Server : public NoCopy
    {
    public:
        typedef std::function<void(Channel*)> FuncType;

        Server(EventLoop*, int);
        ~Server();

        void Start();
        void Close();
        void onMsg(FuncType);

    private:
        int listen_port_;
        EventLoop* loop_;
        Socket* socket_;
        Channel* listen_;
        std::vector<Channel*> conn_;
        FuncType on_read_;

        void HandleAccept();
    };
}

#endif //_SERVER_HPP_   
