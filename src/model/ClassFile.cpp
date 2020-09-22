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
            if (type == 1) return this->get_string_constant_pool(cpInfo.get_name_index(), 0);
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

void ClassFile::show_constant_pool() {
    int i = 1;
    printf("Constant pool:\n");
    for (std::vector<CpInfo>::iterator it = this->constant_pool.begin() ; it != this->constant_pool.end(); ++it) {
        switch (it->tag) {
            case CpTagConst::CONSTANT_Class:
                printf("\t#%2d = Class     \t\t #%d \t\t         // %s\n", i, it->get_name_index(), this->get_string_constant_pool(it->get_name_index(), 0).c_str());
                break;
            case CpTagConst::CONSTANT_Fieldref:
                printf("\t#%2d = Fieldref  \t\t #%d.#%d \t\t // %s.%s:%s\n", i, it->get_class_index(), it->get_descriptor_index(), this->get_string_constant_pool(it->get_class_index(), 1).c_str(), this->get_string_constant_pool(it->get_name_and_type_index(), 1).c_str(), this->get_string_constant_pool(it->get_descriptor_index(), 2).c_str());
                break;
            case CpTagConst::CONSTANT_Methodref:
                printf("\t#%2d = Methodref \t\t #%d.#%d \t\t // %s.%s:%s\n", i, it->get_class_index(), it->get_descriptor_index(), this->get_string_constant_pool(it->get_class_index(), 1).c_str(), this->get_string_constant_pool(it->get_name_and_type_index(), 1).c_str(), this->get_string_constant_pool(it->get_descriptor_index(), 2).c_str());
                break;
            case CpTagConst::CONSTANT_InterfaceMethodref:
                printf("\t#%2d = InterfaceMethodref \t\t #%d.#%d \t\t // %s.%s\n", i, it->get_class_index(), it->get_descriptor_index(), this->get_string_constant_pool(it->get_class_index(), 1).c_str(), this->get_string_constant_pool(it->get_name_and_type_index(), 2).c_str());
                break;
            case CpTagConst::CONSTANT_String:
                printf("\t#%2d = String    \t\t #%d \t\t         // %s\n", i, it->get_string_index(), get_string_constant_pool(it->get_string_index(), 0).c_str());
                break;
            /*case CpTagConst::CONSTANT_Integer:
                printf("\t#%2d = Integer    \t\t %d\n", i, it->get_bytes());
                break;
            case CpTagConst::CONSTANT_Float:
                printf("\t#%2d = Float    \t\t %.2f\n", i, it->get_bytes());
                break;*/
            case CpTagConst::CONSTANT_Long:
                break;
            case CpTagConst::CONSTANT_Double:
                break;
            case CpTagConst::CONSTANT_NameAndType:
                printf("\t#%2d = NameAndType \t\t #%d:#%d \t\t // %s:%s\n", i, it->get_name_index(), it->get_descriptor_index(), this->get_string_constant_pool(it->get_name_index(), 1).c_str(), this->get_string_constant_pool(it->get_descriptor_index(), 1).c_str());
                break;
            case CpTagConst::CONSTANT_Utf8:
                printf("\t#%2d = Utf8    \t\t\t %s\n", i, get_string_utf8(*it).c_str());
            default:
                break;
        }
        i++;
    }
}