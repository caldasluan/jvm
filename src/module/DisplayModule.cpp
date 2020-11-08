#include "DisplayModule.h"
#include "../constants/AccessFlagsClassConst.h"
#include "../constants/AccessFlagsMethodConst.h"
#include "../constants/AccessFlagsFieldConst.h"
#include "../constants/CpTagConst.h"
#include <stdio.h>
#include <cstdint>
#include <string>
#include <cstring>

std::string access_flags(uint16_t flags) {
    std::string s;
    if (flags & AccessFlagsClassConst::ACC_PUBLIC) s.append("public ");
    if (flags & AccessFlagsClassConst::ACC_FINAL) s.append("final ");
    if (flags & AccessFlagsClassConst::ACC_SUPER) s.append("super ");
    if (flags & AccessFlagsClassConst::ACC_INTERFACE) s.append("interface ");
    if (flags & AccessFlagsClassConst::ACC_ABSTRACT) s.append("abstract ");
    if (flags & AccessFlagsClassConst::ACC_SYNTHETIC) s.append("synthetic ");
    if (flags & AccessFlagsClassConst::ACC_ANNOTATION) s.append("annotation ");
    if (flags & AccessFlagsClassConst::ACC_ENUM) s.append("anum ");
    return s;
}

std::string access_flags_methods(uint16_t flags) {
    std::string s;
    if (flags & AccessFlagsMethodConst::ACC_PUBLIC) s.append("public ");
    if (flags & AccessFlagsMethodConst::ACC_PRIVATE) s.append("private ");
    if (flags & AccessFlagsMethodConst::ACC_PROTECTED) s.append("protected ");
    if (flags & AccessFlagsMethodConst::ACC_STATIC) s.append("static ");
    if (flags & AccessFlagsMethodConst::ACC_FINAL) s.append("final ");
    if (flags & AccessFlagsMethodConst::ACC_SYNCHRONIZED) s.append("synchronized ");
    if (flags & AccessFlagsMethodConst::ACC_BRIDGE) s.append("bridge ");
    if (flags & AccessFlagsMethodConst::ACC_VARARGS) s.append("varargs ");
    if (flags & AccessFlagsMethodConst::ACC_NATIVE) s.append("native ");
    if (flags & AccessFlagsMethodConst::ACC_ABSTRACT) s.append("abstract ");
    if (flags & AccessFlagsMethodConst::ACC_STRICT) s.append("strict ");
    if (flags & AccessFlagsMethodConst::ACC_SYNTHETIC) s.append("synthetic ");
    return s;
}

std::string access_flags_field(uint16_t flags) {
    std::string s;
    if (flags & AccessFlagsFieldConst::ACC_PUBLIC) s.append("public ");
    if (flags & AccessFlagsFieldConst::ACC_PRIVATE) s.append("private ");
    if (flags & AccessFlagsFieldConst::ACC_PROTECTED) s.append("protected ");
    if (flags & AccessFlagsFieldConst::ACC_STATIC) s.append("static ");
    if (flags & AccessFlagsFieldConst::ACC_FINAL) s.append("final ");
    if (flags & AccessFlagsFieldConst::ACC_VOLATILE) s.append("volatile ");
    if (flags & AccessFlagsFieldConst::ACC_TRANSIENT) s.append("transient ");
    return s;
}

void show_interfaces(ClassFile& classFile) {
    int count = 0;
    printf("\nInterfaces:\n");
    for (uint16_t index : classFile.interfaces) {
        printf("\t#%4d = \t#%d\t< %s >\n", count, index, classFile.get_string_constant_pool(index).c_str());
        count++;
    }
}

void show_constant_pool(ClassFile& classFile) {
    int i = 1;
    printf("\nConstant pool:\n\n");
    for (std::vector<CpInfo>::iterator it = classFile.constant_pool.begin() ; it != classFile.constant_pool.end(); ++it) {
        switch (it->tag) {
            case CpTagConst::CONSTANT_Class:
                //printf("\t#%4d = Class     \t\t\t #%d \t\t         // %s\n", i, it->get_name_index(), classFile.get_string_constant_pool(i).c_str());
                printf("[%d] CONSTANT_Class_info\n", i);
                printf("\t- Class name: \t\t\tcp_info #%d \t\t<%s>\n\n", it->get_name_index(), classFile.get_string_constant_pool(i).c_str());
                break;
            case CpTagConst::CONSTANT_Fieldref:
                //printf("\t#%4d = Fieldref  \t\t\t #%d.#%d \t\t // %s.%s:%s\n", i, it->get_class_index(), it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 0).c_str(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                printf("[%d] CONSTANT_Fieldref_info\n", i);
                printf("\t- Class name: \t\t\tcp_info #%d  \t\t<%s>\n", it->get_class_index(), classFile.get_string_constant_pool(i, 0).c_str());
                printf("\t- Name and type: \t\tcp_info #%d  \t\t<%s:%s>\n\n", it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                break;
            case CpTagConst::CONSTANT_Methodref:
                //printf("\t#%4d = Methodref \t\t\t #%d.#%d \t\t // %s.%s:%s\n", i, it->get_class_index(), it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 0).c_str(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                printf("[%d] CONSTANT_Methodref_info\n", i);
                printf("\t- Class name: \t\t\tcp_info #%d  \t\t<%s>\n", it->get_class_index(), classFile.get_string_constant_pool(i, 0).c_str());
                printf("\t- Name and type: \t\tcp_info #%d  \t\t<%s:%s>\n\n", it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                break;
            case CpTagConst::CONSTANT_InterfaceMethodref:
                //printf("\t#%4d = InterfaceMethodref \t\t #%d.#%d \t\t // %s.%s:%s\n", i, it->get_class_index(), it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 0).c_str(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                printf("[%d] CONSTANT_InterfaceMethodref_info\n", i);
                printf("\t- Class name: \t\t\tcp_info #%d  \t\t<%s>\n", it->get_class_index(), classFile.get_string_constant_pool(i, 0).c_str());
                printf("\t- Name and type: \t\tcp_info #%d  \t\t<%s:%s>\n\n", it->get_name_and_type_index(), classFile.get_string_constant_pool(i, 1).c_str(), classFile.get_string_constant_pool(i, 2).c_str());
                break;
            case CpTagConst::CONSTANT_String:
                //printf("\t#%4d = String    \t\t\t #%d \t\t         // %s\n", i, it->get_string_index(), classFile.get_string_constant_pool(i).c_str());
                printf("[%d] CONSTANT_String_info\n", i);
                printf("\t- String: \t\t\tcp_info #%d  \t\t<%s>\n\n", it->get_string_index(), classFile.get_string_constant_pool(i).c_str());
                break;
            case CpTagConst::CONSTANT_Integer:
                //printf("\t#%4d = Integer    \t\t\t %d\n", i, it->get_int());
                printf("[%d] CONSTANT_Integer_info\n", i);
                printf("\t- Integer: \t\t\t%d\n\n", it->get_int());
                break;
             case CpTagConst::CONSTANT_Float:
                //printf("\t#%4d = Float    \t\t\t %f\n", i, it->get_float());
                printf("[%d] CONSTANT_Float_info\n", i);
                printf("\t- Float: \t\t\t%f\n\n", it->get_float());
                break;
            case CpTagConst::CONSTANT_Long:
                //printf("\t#%4d = Long    \t\t\t %lld\n", i, it->get_long());
                printf("[%d] CONSTANT_Long_info\n", i);
                printf("\t- Long: \t\t\t%lld\n\n", it->get_long());
                break;
            case CpTagConst::CONSTANT_Double:
                //printf("\t#%4d = Double    \t\t\t %lf\n", i, it->get_double());
                printf("[%d] CONSTANT_Double_info\n", i);
                printf("\t- Double: \t\t\t%lf\n\n", it->get_double());
                break;
            case CpTagConst::CONSTANT_NameAndType:
                //printf("\t#%4d = NameAndType \t\t\t #%d:#%d \t\t\t // %s:%s\n", i, it->get_name_index(), it->get_descriptor_index(), classFile.get_string_constant_pool(i, 0).c_str(), classFile.get_string_constant_pool(i, 1).c_str());
                printf("[%d] CONSTANT_NameAndType_info\n", i);
                printf("\t- Name: \t\t\tcp_info #%d  \t\t<%s>\n", it->get_name_index(), classFile.get_string_constant_pool(i, 0).c_str());
                printf("\t- Descriptor: \t\t\tcp_info #%d  \t\t<%s>\n\n", it->get_descriptor_index(), classFile.get_string_constant_pool(i, 1).c_str());
                break;
            case CpTagConst::CONSTANT_Utf8:
                //printf("\t#%4d = Utf8    \t\t\t %s\n", i, classFile.get_string_constant_pool(i).c_str());
                printf("[%d] CONSTANT_Utf8_info\n", i);
                printf("\t- String: \t\t\t%s\n\n", classFile.get_string_constant_pool(i).c_str());
                break;
            case CpTagConst::CONSTANT_LargeNumeric:
                //printf("\t#%4d = (large numeric continued)\n", i);
                printf("[%d] (large numeric continued)\n\n", i);
                break;
            default:
                break;
        }
        i++;
    }
}

void show_methods(ClassFile& classFile) {
    printf("\nMethods:\n\n");
    for (MethodInfo methodInfo : classFile.methods) {
        printf("\tName:\t\t\tcp_info#%d\t\t<%s>\n", methodInfo.name_index, classFile.get_string_constant_pool(methodInfo.name_index).c_str());
        printf("\tDescriptor:\t\tcp_info#%d\t\t<%s>\n", methodInfo.descriptor_index, classFile.get_string_constant_pool(methodInfo.descriptor_index).c_str());
        printf("\tAccess Flags:\t\t0x%04x\t\t\t[ %s]\n", methodInfo.access_flags, access_flags_methods(methodInfo.access_flags).c_str());
        show_attributes(1, methodInfo.attributes, classFile);
        printf("\n");
    }
}

void show_fields(ClassFile& classFile) {
    printf("\nFields:\n\n");
    for (FieldInfo fieldInfo : classFile.fields) {
        printf("\tName:\t\t\tcp_info#%d\t\t<%s>\n", fieldInfo.name_index, classFile.get_string_constant_pool(fieldInfo.name_index).c_str());
        printf("\tDescriptor:\t\tcp_info#%d\t\t<%s>\n", fieldInfo.descriptor_index, classFile.get_string_constant_pool(fieldInfo.descriptor_index).c_str());
        printf("\tAccess Flags:\t\t0x%04x\t\t\t[ %s]\n", fieldInfo.access_flags, access_flags_field(fieldInfo.access_flags).c_str());
        show_attributes(1, fieldInfo.attributes, classFile);
        printf("\n");
    }
}

void DisplayModule::show(ClassFile& classFile) {
    printf("Magic Number: 0x%08x\n", classFile.magic);
    printf("Minor Version: %d\n", classFile.minor_version);
    printf("Major Version: %d [1.%d]\n", classFile.major_version, classFile.major_version - 44);
    printf("Constant Pool Count: %d\n", classFile.constant_pool_count);
    printf("Access Flags: 0x%04x [ %s]\n", classFile.access_flags, access_flags(classFile.access_flags).c_str());
    printf("This Class: cp_info #%d <%s>\n", classFile.this_class, classFile.get_string_constant_pool(classFile.this_class).c_str());
    printf("Super Class: cp_info #%d <%s>\n", classFile.super_class, classFile.get_string_constant_pool(classFile.super_class).c_str());
    printf("Interfaces Count: %d\n", classFile.interfaces_count);
    printf("Fields Count: %d\n", classFile.fields_count);
    printf("Methods Count: %d\n", classFile.methods_count);
    printf("Attributes Count: %d\n", classFile.attributes_count);
    show_constant_pool(classFile);
    show_interfaces(classFile);
    show_fields(classFile);
    show_methods(classFile);
    show_attributes(0, classFile.attributes, classFile);
}