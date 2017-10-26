//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_MUTEX_HPP
#define KUQIKV_MUTEX_HPP

#include <mutex>

class ScopedLock{
public:
    ScopedLock(pthread_mutex_t* m):m_(m) {
        pthread_mutex_lock(m_);
    }

    ~ScopedLock() {
        pthread_mutex_unlock(m_);
    }

private:
    pthread_mutex_t* m_;
};

#endif //KUQIKV_MUTEX_HPP
