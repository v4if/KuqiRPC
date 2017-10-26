//
// Created by root on 10/26/17.
//

#ifndef KUQIKV_FIFO_H
#define KUQIKV_FIFO_H

#include <list>
#include <pthread.h>
#include "scope_lock.h"

template <typename T>
class fifo {
public:
    fifo();
    ~fifo();

    bool enq(T e);
    void deq(T* e);
    unsigned long size();

private:
    std::list<T> q_;
    pthread_mutex_t m_;
    pthread_cond_t wait_enq_c_;
};

template <typename T>
fifo<T>::fifo() {
    pthread_mutex_init(&m_, NULL);
    pthread_cond_init(&wait_enq_c_, NULL);
}

template <typename T>
fifo<T>::~fifo() {
    pthread_mutex_destroy(&m_);
    pthread_cond_destroy(&wait_enq_c_);
}

template <typename T>
bool fifo<T>::enq(T e) {
    ScopedLock ml(&m_);
    q_.push_back(e);
    return true;
}

template <typename T>
void fifo<T>::deq(T *e) {
    ScopedLock ml(&m_);
    while (q_.empty()) {
        pthread_cond_wait(&wait_enq_c_, &m_);
    }
    *e = q_.front();
    q_.pop_back();
}

template <typename T>
unsigned long fifo<T>::size() {
    ScopedLock ml(&m_);
    return q_.size();
}

#endif //KUQIKV_FIFO_H
