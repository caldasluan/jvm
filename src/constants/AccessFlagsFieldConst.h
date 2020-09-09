#ifndef ACCESS_FLAGS_FIELD_CONST_H
#define ACCESS_FLAGS_FIELD_CONST_H

#include <cstdint>

class AccessFlagsFieldConst {
    public:
        static const uint16_t ACC_PUBLIC = 0x0001;
        static const uint16_t ACC_PRIVATE = 0x0002;
        static const uint16_t ACC_PROTECTED = 0x0004;
        static const uint16_t ACC_STATIC = 0x0008;
        static const uint16_t ACC_FINAL = 0x0010;
        static const uint16_t ACC_VOLATILE = 0x0040;
        static const uint16_t ACC_TRANSIENT = 0x0080;
};

#endif // ACCESS_FLAGS_FIELD_CONST_H