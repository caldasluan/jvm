#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <cstdint>
#include <vector>

#include "AttributeInfo.h"

class FieldInfo {
    public:
        uint16_t access_flags; // AccessFlagsFieldConst
        uint16_t name_index;
        uint16_t descriptor_index;
        uint16_t attributes_count;
        std::vector<AttributeInfo> attributes;
};

#endif // FIELD_INFO_H