//
// Created by root on 10/29/17.
//

#ifndef KUQIKV_FUTURE_H
#define KUQIKV_FUTURE_H

#include <zconf.h>
#include <pthread.h>
#include "../auxiliary/scope_lock.h"
#include "marshal.h"

template <class T>
class Future {
public:
    enum Status{pending = 0x0, ready};

    Future():value_(), status_(pending) {
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&cond_, NULL);
    }

    ~Future() {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&cond_);
    }

    T Get() {
        ScopedLock ml(&mutex_);
        if (status_ == ready) {
            return value_;
        }
    }

    void Wait() {
        ScopedLock ml(&mutex_);
        while (status_ != ready) {
            pthread_cond_wait(&cond_, &mutex_);
        }
    }

    void Notify(Marshal &marshal) {
        ScopedLock ml(&mutex_);
        if (status_ == pending) {
            marshal >> value_;
            status_ = ready;
            pthread_cond_signal(&cond_);
        }
    }
private:
    T value_;
    Status status_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};

#endif //KUQIKV_FUTURE_H
