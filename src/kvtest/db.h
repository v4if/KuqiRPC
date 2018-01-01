//
// Created by root on 10/9/17.
//

#ifndef KUQIKV_DB_HPP
#define KUQIKV_DB_HPP


#include <iostream>
#include <unordered_map>
#include "kv_protocol.h"

namespace KuqiKV {
    class DB {
    public:
        void Get(const KV_Protocol::GetArgs *args, KV_Protocol::GetReply *future);

        void Put(const KV_Protocol::PutArgs *args, KV_Protocol::PutReply *future);

    private:
        std::unordered_map<KV_Protocol::Key, KV_Protocol::Value> map_;
    };
}

#endif //KUQIKV_DB_HPP
