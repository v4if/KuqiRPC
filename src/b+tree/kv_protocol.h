//
// Created by root on 11/7/17.
//

#ifndef KUQIKV_KV_PROTOCOL_H
#define KUQIKV_KV_PROTOCOL_H

#include <string>
#include "../rpc/marshal.h"

class KV_Protocol {
public:
    typedef std::string Key;
    typedef std::string Value;

    struct PutArgs {
        Key key;
        Value value;
    };

    struct GetArgs {
        Key key;
    };

    struct PutReply {
        uint8_t ok;
    };

    struct GetReply {
        Value value;
        uint8_t ok;
    };
};

inline Marshal& operator << (Marshal &marshal, KV_Protocol::PutArgs &vv) {
    marshal << vv.key;
    marshal << vv.value;
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, KV_Protocol::PutArgs &vv) {
    marshal >> vv.key;
    marshal >> vv.value;
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, KV_Protocol::GetArgs &vv) {
    marshal << vv.key;
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, KV_Protocol::GetArgs &vv) {
    marshal >> vv.key;
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, KV_Protocol::PutReply &vv) {
    marshal << vv.ok;
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, KV_Protocol::PutReply &vv) {
    marshal >> vv.ok;
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, KV_Protocol::GetReply &vv) {
    marshal << vv.value;
    marshal << vv.ok;
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, KV_Protocol::GetReply &vv) {
    marshal >> vv.value;
    marshal >> vv.ok;
    return marshal;
}

#endif //KUQIKV_KV_PROTOCOL_H
