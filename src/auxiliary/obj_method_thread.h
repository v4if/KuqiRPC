//
// Created by root on 10/26/17.
//

#ifndef KUQIKV_OBJ_METHOD_THREAD_H
#define KUQIKV_OBJ_METHOD_THREAD_H

#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

template <typename C, typename A>
class ObjFuncWrapper {
public:
    ObjFuncWrapper (C *obj, void (C::*method)(A), A args):o_(obj), m_(method), a_(args) {}

    static void* fn(void *wrapper) {
        ObjFuncWrapper *w = (ObjFuncWrapper*)wrapper;
        C *o = w->o_;
        void (C::*m)(A) = w->m_;
        A a = w->a_;
        (o->*m)(a);

        delete w;
        return 0;
    }

private:
    C *o_;
    void (C::*m_)(A);
    A a_;
};

template <typename C, typename A>
pthread_t obj_method_thread(C *obj, void (C::*method)(A), A args) {
    ObjFuncWrapper<C, A> *func_wrapper = new ObjFuncWrapper<C, A>(obj, method, args);

    pthread_t th;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // set stack size to 100K, so we don't run out of memory
    pthread_attr_setstacksize(&attr, 100*1024);

    int err = pthread_create(&th, &attr, &ObjFuncWrapper<C, A>::fn, func_wrapper);
    pthread_attr_destroy(&attr);
    if (err != 0) {
        fprintf(stderr, "pthread_create ret %d %s\n", err, strerror(err));
        exit(1);
    }

    return th;
}

#endif //KUQIKV_OBJ_METHOD_THREAD_H
