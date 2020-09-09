#ifndef ATTRIBUTE_INFO_H
#define ATTRIBUTE_INFO_H

#include <cstdint>
#include <vector>

class AttributeInfo {
    public:
        uint16_t attribute_name_index;
        uint32_t attribute_length;
        std::vector<uint8_t> info;
};

#endif // ATTRIBUTE_INFO_H