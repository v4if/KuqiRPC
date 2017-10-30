//
// Created by root on 10/25/17.
//

#ifndef KUQIKV_MARSHALL_H
#define KUQIKV_MARSHALL_H

class Marshal {
public:
    Marshal(){}
    Marshal(Network::CharBuffer *in, Network::CharBuffer *out):input_(in), output_(out) {}
    void Read(const void *b, uint32_t sz);
    void Write(void *b, uint32_t sz);
private:
    Network::CharBuffer* input_;
    Network::CharBuffer* output_;
};

inline void Marshal::Read(const void *b, uint32_t sz) {
    output_->write(b, sz);
}

inline void Marshal::Write(void *b, uint32_t sz) {
    input_->read(b, sz);
}

inline Marshal& operator >> (Marshal &marshal, uint8_t &vv) {
    marshal.Write(&vv, sizeof(uint8_t));
    return marshal;
}

inline Marshal& operator >> (Marshal &marshal, uint32_t &vv) {
    marshal.Write(&vv, sizeof(uint32_t));
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, uint8_t &vv) {
    marshal.Read(&vv, sizeof(uint8_t));
    return marshal;
}

inline Marshal& operator << (Marshal &marshal, uint32_t &vv) {
    marshal.Read(&vv, sizeof(uint32_t));
    return marshal;
}

#endif //KUQIKV_MARSHALL_H
