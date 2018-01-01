//
// Created by root on 10/9/17.
//
#include "db.hpp"
namespace KuqiKV {
    void DB::Get(const KV_Protocol::GetArgs *args, KV_Protocol::GetReply *future) {
        if (map_.count(args->key) == 0) {
            future->ok = 0;
            return;
        }

        future->value = map_[args->key];
        future->ok = 1;
    }

    void DB::Put(const KV_Protocol::PutArgs *args, KV_Protocol::PutReply *future) {
        if (map_.count(args->key) > 0) {
            future->ok = 0;
            return;
        }

        map_[args->key] = args->value;
        future->ok = 1;
    }
}