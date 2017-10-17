#ifndef _EVENTLOOP_HPP_
#define _EVENTLOOP_HPP_

#include "poller.hpp"
#include "channel.hpp"
#include "../debug/debug_new.hpp"

namespace Network {
    class EventLoop : public NoCopy
    {
    public:
        EventLoop();
        ~EventLoop();

        Poller* getPoller();
    
        void loop();
        void exit();
    private:    
        Poller* poller_;
        bool running_;
    };
}

#endif //_EVENTLOOP_HPP_
