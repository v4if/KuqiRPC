//
// Created by root on 10/25/17.
//

#ifndef KUQIKV_MARSHALL_H
#define KUQIKV_MARSHALL_H

#include "../network/charbf.hpp"

class Marshal {
public:
    Marshal(Network::CharBuffer *read_buff, Network::CharBuffer *write_buff):read_buff_(read_buff), write_buff_(write_buff) {}
    void Read(const void *b, uint32_t sz);
    void Write(void *b, uint32_t sz);
private:
    Network::CharBuffer* read_buff_;
    Network::CharBuffer* write_buff_;
};

inline void Marshal::Read(const void *b, uint32_t sz) {
    write_buff_->write(b, sz);
}

inline void Marshal::Write(void *b, uint32_t sz) {
    read_buff_->read(b, sz);
}

inline Marshal& operator << (Marshal &marshal, uint8_t &vv) {
    marshal.Read(&vv, sizeof(uint8_t));
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, uint8_t &vv) {
    marshal.Write(&vv, sizeof(uint8_t));
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, uint32_t &vv) {
    marshal.Read(&vv, sizeof(uint32_t));
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, uint32_t &vv) {
    marshal.Write(&vv, sizeof(uint32_t));
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, std::string &vv) {
    uint32_t len = (uint32_t)vv.size();
    marshal.Read(&len, sizeof(uint32_t));
    marshal.Read(vv.c_str(), len);
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, std::string &vv) {
    uint32_t len;
    marshal.Write(&len, sizeof(uint32_t));

    char *temp = (char*)malloc(len + 1);
    marshal.Write(temp, len);
    temp[len] = '\0';
    vv.append(temp);
    delete(temp);
    return marshal;
}

#endif //KUQIKV_MARSHALL_H
