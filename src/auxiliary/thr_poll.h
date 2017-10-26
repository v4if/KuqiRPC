//
// Created by root on 10/25/17.
//

#ifndef KUQIKV_THREAD_POLL_H
#define KUQIKV_THREAD_POLL_H

#include <functional>
#include <vector>
#include "fifo.h"
#include "obj_method_thread.h"

class ThrPoll {
public:
    struct job_t {
        void *(*fn)(void*);
        void *wrapper_args;
    };

    ThrPoll(int sz);
    ~ThrPoll();

    bool addJob(void *(*fn)(void *), void *args);
    bool takeJob(job_t *job);

    template <typename C, typename A>
    bool addObjJob(C *obj, void(C::*)(A), A args);

private:
    fifo<job_t> jobq_;
    std::vector<pthread_t> th_;
    int nthreads_;
};

template <typename C, typename A>
bool ThrPoll::addObjJob(C *obj, void(C::*method)(A), A args) {
    ObjFuncWrapper<C, A> *func_wrapper = new ObjFuncWrapper<C, A>(obj, method, args);
    addJob(&ObjFuncWrapper<C, A>::fn, func_wrapper);
};

#endif //KUQIKV_THREAD_POLL_H
