//
// Created by root on 10/9/17.
//

#ifndef KUQIKV_DB_HPP
#define KUQIKV_DB_HPP


#include <iostream>
#include <unordered_map>
#include "../debug/debug_new.hpp"

namespace KuqiKV {
    class DB {
    public:
        void Get(const int* args, int* future);

        void Put(const int* args, int* future);

    private:
        std::unordered_map<std::string, std::string> bucket;
    };
}

#endif //KUQIKV_DB_HPP
