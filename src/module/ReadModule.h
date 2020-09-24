#ifndef READ_MODULE_H
#define READ_MODULE_H

#include <cstdint>
#include <string>

#include "../model/ClassFile.h"

class ReadModule {
    public:
        static ClassFile& read_file(const char*);
};

uint8_t u1Read(FILE* file);

uint16_t u2Read(FILE* file);

uint32_t u4Read(FILE* file);

void fill_attributes_info(FILE* file, uint16_t size, std::vector<std::unique_ptr<AttributeInfo>>& attributes, ClassFile* classFile);

#endif // READ_MODULE_H