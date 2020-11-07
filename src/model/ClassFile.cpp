#include "ClassFile.h"
#include "CpInfo.h"
#include "../constants/CpTagConst.h"
#include <stdio.h>
#include <string>

std::string get_string_utf8(CpInfo cpInfo) {
    std::string s(cpInfo.get_bytes_utf8().data(), cpInfo.get_lenght());
    return s;
}

std::string ClassFile::get_string_constant_pool(uint16_t index, uint8_t type) {
    CpInfo& cpInfo = this->constant_pool[index-1];
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
        case CpTagConst::CONSTANT_Integer:
            return std::to_string(cpInfo.get_int());
        case CpTagConst::CONSTANT_Float:
            return std::to_string(cpInfo.get_float());
        case CpTagConst::CONSTANT_Long:
            return std::to_string(cpInfo.get_long());
        case CpTagConst::CONSTANT_Double:
            return std::to_string(cpInfo.get_double());
        default:
            return "";
    }
}

std::string ClassFile::get_string_constant_complete(uint16_t index)
{
    CpInfo cpInfo = this->constant_pool[index-1];
    switch (cpInfo.tag)
    {
    case CpTagConst::CONSTANT_Utf8:
        return get_string_utf8(cpInfo);
    case CpTagConst::CONSTANT_Integer:
    case CpTagConst::CONSTANT_Float:
    case CpTagConst::CONSTANT_Long:
    case CpTagConst::CONSTANT_Double:
        return get_string_constant_pool(index, 0);
    case CpTagConst::CONSTANT_Class:
        return get_string_constant_pool(cpInfo.get_name_index(), 0);
    case CpTagConst::CONSTANT_String:
        return get_string_constant_pool(cpInfo.get_string_index(), 0);
    case CpTagConst::CONSTANT_InterfaceMethodref:
    case CpTagConst::CONSTANT_Methodref:
    case CpTagConst::CONSTANT_Fieldref:
        return get_string_constant_pool(cpInfo.get_class_index(), 0) + "." + get_string_constant_pool(cpInfo.get_name_and_type_index(), 0) + " " + get_string_constant_pool(cpInfo.get_name_and_type_index(), 1);
    case CpTagConst::CONSTANT_NameAndType:
        return get_string_constant_pool(cpInfo.get_name_index(), 0) + " : " + get_string_constant_pool(cpInfo.get_descriptor_index(), 0);
    case CpTagConst::CONSTANT_MethodHandle:
        return cpInfo.info[0] + " " + get_string_constant_complete((cpInfo.info[1] << 8) | cpInfo.info[2]);
    case CpTagConst::CONSTANT_MethodType:
        return get_string_constant_pool(cpInfo.get_name_index(), 0);
    case CpTagConst::CONSTANT_InvokeDynamic:
        return cpInfo.get_name_index() + " " + get_string_constant_complete(cpInfo.get_name_and_type_index());
    }
    return "What?" + index;
}

std::string ClassFile::get_string_constant_pool(uint16_t index) {
    return this->get_string_constant_pool(index, 0);
}