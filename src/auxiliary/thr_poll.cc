//
// Created by root on 10/26/17.
//

#include "thr_poll.h"

static void *do_worker(void* args) {
    ThrPoll *thr_poll = (ThrPoll*)args;
    while (1) {
        ThrPoll::job_t job;
        if (!thr_poll->takeJob(&job))
            break; // die
        (void)job.fn(job.wrapper_args);
    }
    pthread_exit(NULL);
}

ThrPoll::ThrPoll(int sz):nthreads_(sz){
    pthread_attr_t attr_;
    pthread_attr_init(&attr_);
    /* 128K */
    pthread_attr_setstacksize(&attr_, 128<<10);

    for (int i = 0; i < nthreads_; i++) {
        pthread_t t;
        pthread_create(&t, &attr_, do_worker, (void *)this);
        th_.push_back(t);
    }
    pthread_attr_destroy(&attr_);
}

ThrPoll::~ThrPoll() {
    for (int i = 0; i < nthreads_; i++) {
        job_t j;
        j.fn = (void *(*)(void *))NULL; //poison pill to tell worker threads to exit
        jobq_.enq(j);
    }

    for (int i = 0; i < nthreads_; i++) {
        pthread_join(th_[i], NULL);
    }
}

bool ThrPoll::addJob(void *(*fn)(void *), void *args) {
    job_t job;
    job.fn = fn;
    job.wrapper_args = args;

    return jobq_.enq(job);
}

bool ThrPoll::takeJob(job_t *job) {
    jobq_.deq(job);
    return (job->fn != NULL);
}