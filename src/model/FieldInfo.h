#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <cstdint>
#include <vector>
#include <memory>

class FieldInfo;

#include "AttributeInfo.h"

class FieldInfo {
    public:
        uint16_t access_flags; // AccessFlagsFieldConst
        uint16_t name_index;
        uint16_t descriptor_index;
        uint16_t attributes_count;
        std::vector<std::shared_ptr<AttributeInfo>> attributes;

    static uint8_t field_size_bytes(std::string descr);
};

#endif // FIELD_INFO_H