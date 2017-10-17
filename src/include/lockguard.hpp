//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_MUTEX_HPP
#define KUQIKV_MUTEX_HPP

#include <mutex>

class LockGuard{
public:
    LockGuard() {
        m_.lock();
    }

    ~LockGuard() {
        m_.unlock();
    }

private:
    std::mutex m_;
};

#endif //KUQIKV_MUTEX_HPP
