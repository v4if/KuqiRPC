//
// Created by root on 10/16/17.
//

#ifndef KUQIKV_RPC_OBJ_HPP
#define KUQIKV_RPC_OBJ_HPP

class Rpc_Obj {
public:
    struct Args{
        int num1;
        int num2;
    };

    void Add(const uint8_t* a, uint8_t* r) {
        *r = *a;
    }
};

#endif //KUQIKV_RPC_OBJ_HPP
