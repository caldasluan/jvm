#ifndef METHOD_INFO_H
#define METHOD_INFO_H

#include <cstdint>
#include <vector>

#include "AttributeInfo.h"

class MethodInfo {
    public:
        uint16_t access_flags; // AccessFlagsMethodConst
        uint16_t name_index;
        uint16_t descriptor_index;
        uint16_t attributes_count;
        std::vector<AttributeInfo> attributes;
};

#endif // METHOD_INFO_H