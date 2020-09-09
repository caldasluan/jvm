#ifndef READ_MODULE_H
#define READ_MODULE_H

#include <cstdint>
#include <string>

#include "../model/ClassFile.h"

class ReadModule {
    public:
        static ClassFile& read_file(const char*);
};

#endif // READ_MODULE_H