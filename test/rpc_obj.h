//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_RPC_OBJ_HPP
#define KUQIKV_RPC_OBJ_HPP

class Rpc_Obj {
public:
    struct Args{
        uint32_t num1;
        uint32_t num2;
    };

    void Add(const Args* a, uint32_t * r) {
        *r = a->num1 + a->num2;
    }
};

inline Marshal& operator >> (Marshal &marshal, Rpc_Obj::Args &vv) {
    marshal >> vv.num1;
    marshal >> vv.num2;
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, Rpc_Obj::Args &vv) {
    marshal << vv.num1;
    marshal << vv.num2;
    return marshal;
}

#endif //KUQIKV_RPC_OBJ_HPP
