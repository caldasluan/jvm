#include <iostream>
#include "module/ReadModule.h"

int main(int argc, char *argv[])
{
    char file[] = "input/MainAct.class";

    ClassFile& classFile = ReadModule::read_file(file);

    std::cout << classFile.magic << std::endl;
    std::cout << classFile.minor_version << std::endl;
    std::cout << classFile.major_version << std::endl;
    std::cout << classFile.constant_pool_count << std::endl;
    std::cout << classFile.access_flags << std::endl;
    std::cout << classFile.this_class << std::endl;
    std::cout << classFile.super_class << std::endl;
    std::cout << classFile.interfaces_count << std::endl;
    std::cout << classFile.fields_count << std::endl;
    std::cout << classFile.methods_count << std::endl;
    std::cout << classFile.attributes_count << std::endl;
}
