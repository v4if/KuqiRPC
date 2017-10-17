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

    void Add(const Args* args, int* reply) {
        *reply = args->num1 + args->num2;
    }
};

#endif //KUQIKV_RPC_OBJ_HPP
