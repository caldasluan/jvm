#ifndef CP_TAG_CONST_H
#define CP_TAG_CONST_H

#include <cstdint>

class CpTagConst {
    public:
        static const uint8_t CONSTANT_Class = 7;
        static const uint8_t CONSTANT_Fieldref = 9;
        static const uint8_t CONSTANT_Methodref = 10;
        static const uint8_t CONSTANT_InterfaceMethodref = 11;
        static const uint8_t CONSTANT_String = 8;
        static const uint8_t CONSTANT_Integer = 3;
        static const uint8_t CONSTANT_Float = 4;
        static const uint8_t CONSTANT_Long = 5;
        static const uint8_t CONSTANT_Double = 6;
        static const uint8_t CONSTANT_NameAndType = 12;
        static const uint8_t CONSTANT_Utf8 = 1;
        static const uint8_t CONSTANT_MethodHandle = 15;
        static const uint8_t CONSTANT_MethodType = 16;
        static const uint8_t CONSTANT_InvokeDynamic = 18;
};

#endif // CP_TAG_CONST_H