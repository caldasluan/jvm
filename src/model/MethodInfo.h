#ifndef METHOD_INFO_H
#define METHOD_INFO_H

#include <cstdint>
#include <vector>
#include <memory>

#include "AttributeInfo.h"

class MethodInfo {
    public:
        uint16_t access_flags = 0; // AccessFlagsMethodConst
        uint16_t name_index = 0;
        uint16_t descriptor_index = 0;
        uint16_t attributes_count = 0;
        std::vector<std::shared_ptr<AttributeInfo>> attributes;
};

#endif // METHOD_INFO_H