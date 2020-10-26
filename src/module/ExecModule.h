#ifndef EXEC_MODULE_H
#define EXEC_MODULE_H

#include "../model/ClassFile.h"

class ExecModule {
    public:
        static void exec(ClassFile& classFile);
};

#endif // EXEC_MODULE_H