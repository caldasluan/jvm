#ifndef ACCESS_FLAGS_CLASS_CONST_H
#define ACCESS_FLAGS_CLASS_CONST_H

#include <cstdint>

class AccessFlagsClassConst {
    public:
        static const uint16_t ACC_PUBLIC = 0x0001;
        static const uint16_t ACC_FINAL = 0x0010;
        static const uint16_t ACC_SUPER = 0x0020;
        static const uint16_t ACC_INTERFACE = 0x0200;
        static const uint16_t ACC_ABSTRACT = 0x0400;
};

#endif // ACCESS_FLAGS_CLASS_CONST_H