#ifndef CLASS_FILE_H
#define CLASS_FILE_H

#include <cstdint>
#include <vector>
#include <string>

#include "CpInfo.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
#include "AttributeInfo.h"

class ClassFile {
    public:   
        uint32_t magic;
        uint16_t minor_version;
        uint16_t major_version;
        uint16_t constant_pool_count;
        std::vector<CpInfo> constant_pool;
        uint16_t access_flags; // AccessFlagsClassConst
        uint16_t this_class;
        uint16_t super_class;
        uint16_t interfaces_count;
        std::vector<uint16_t> interfaces;
        uint16_t fields_count;
        std::vector<FieldInfo> fields;
        uint16_t methods_count;
        std::vector<MethodInfo> methods;
        uint16_t attributes_count;
        std::vector<AttributeInfo> attributes;

        ClassFile();

        std::string get_string_constant_pool(uint16_t);
        std::string get_string_constant_pool(uint16_t, uint8_t);
};

#endif // CLASS_FILE_H