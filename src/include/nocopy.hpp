//
// Created by root on 9/25/17.
//

#ifndef KUQIKV_NOCOPY_H
#define KUQIKV_NOCOPY_H

namespace KuqiKV {
    class NoCopy{
    public:
        NoCopy(){}
        virtual ~NoCopy(){}

        NoCopy(const NoCopy&) = delete;
        NoCopy& operator=(const NoCopy&) = delete;
    };
}

#endif //KUQIKV_NOCOPY_H
