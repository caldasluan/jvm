#include "ClassFile.h"
#include "CpInfo.h"
#include "../constants/CpTagConst.h"
#include <stdio.h>

ClassFile::ClassFile() {}

std::string get_string_utf8(CpInfo cpInfo) {
    std::string s(cpInfo.get_bytes_utf8().data(), cpInfo.get_lenght());
    return s;
}

std::string ClassFile::get_string_constant_pool(uint16_t index, uint8_t type) {
    CpInfo cpInfo = this->constant_pool[index-1];
    switch (cpInfo.tag) {
        case CpTagConst::CONSTANT_Class:
            return this->get_string_constant_pool(cpInfo.get_name_index(), 0);
        case CpTagConst::CONSTANT_String:
            return this->get_string_constant_pool(cpInfo.get_string_index(), 0);
        case CpTagConst::CONSTANT_NameAndType:
            if (type == 0) return this->get_string_constant_pool(cpInfo.get_name_index(), 0);
            return this->get_string_constant_pool(cpInfo.get_descriptor_index(), 0);
        case CpTagConst::CONSTANT_InterfaceMethodref:
        case CpTagConst::CONSTANT_Methodref:
        case CpTagConst::CONSTANT_Fieldref:
            if (type == 1 || type == 2) return this->get_string_constant_pool(cpInfo.get_name_and_type_index(), type - 1);
            return this->get_string_constant_pool(cpInfo.get_class_index(), 0);
        case CpTagConst::CONSTANT_Utf8:
            return get_string_utf8(cpInfo);
        default:
            return "";
    }
}

std::string ClassFile::get_string_constant_pool(uint16_t index) {
    return this->get_string_constant_pool(index, 0);
}