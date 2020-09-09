#ifndef ACCESS_FLAGS_METHOD_CONST_H
#define ACCESS_FLAGS_METHOD_CONST_H

#include <cstdint>

class AccessFlagsMethoddConst {
    public:
        static const uint16_t ACC_PUBLIC = 0x0001;
        static const uint16_t ACC_PRIVATE = 0x0002;
        static const uint16_t ACC_PROTECTED = 0x0004;
        static const uint16_t ACC_STATIC = 0x0008;
        static const uint16_t ACC_FINAL = 0x0010;
        static const uint16_t ACC_SYNCHRONIZED = 0x0020;
        static const uint16_t ACC_NATIVE = 0x0100;
        static const uint16_t ACC_ABSTRACT = 0x0400;
        static const uint16_t ACC_STRICT = 0x0800;
};

#endif // ACCESS_FLAGS_METHOD_CONST_H