#include "DisplayModule.h"
#include "../model/ClassFile.h"
#include "../constants/AccessFlagsClassConst.h"
#include <stdio.h>
#include <cstdint>
#include <string>

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
}