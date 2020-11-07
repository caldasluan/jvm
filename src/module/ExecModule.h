#ifndef EXEC_MODULE_H
#define EXEC_MODULE_H

#include <stack>
#include <map>
#include "../model/ClassFile.h"
#include "../model/ClassInfo.h"
#include "../model/Runtime.h"

class ExecModule {
public:
    static void exec_jvm(Runtime &runtime);
    static ClassInfo *prepare_class(Runtime &runtime, std::string fileName);
    static ClassInfo *read_load_class(Runtime &runtime, const char* fileName);
    static void clinit_loaded_classes(Runtime &runtime, ClassInfo *classInfo);
    static void initialize_jvm(const char *fileName, int argc, char *argv[]);

};

#endif // EXEC_MODULE_H