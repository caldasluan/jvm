#ifndef CP_INFO_H
#define CP_INFO_H

#include <cstdint>
#include <vector>

class CpInfo {
    public:
        uint8_t tag; // CpTagConst
        std::vector<uint8_t> info;

        uint16_t get_name_index();
        uint16_t get_descriptor_index();
        uint16_t get_class_index();
        uint16_t get_name_and_type_index();
        uint16_t get_string_index();
        uint32_t get_bytes();
        uint32_t get_high_bytes();
        uint32_t get_low_bytes();
        uint16_t get_lenght();
        std::vector<char> get_bytes_utf8();
};

#endif // CP_INFO_H