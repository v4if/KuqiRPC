//
// Created by root on 10/9/17.
//

#ifndef KUQIKV_DB_HPP
#define KUQIKV_DB_HPP

namespace KuqiKV {
    class DB {
        enum {Bucket_Size = 1024};
    public:
        std::string Get(std::string key);
        void Put(std::string key, std::string value);

    private:

    };
}

#endif //KUQIKV_DB_HPP
