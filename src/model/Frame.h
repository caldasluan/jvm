#ifndef JVM_FRAME_H
#define JVM_FRAME_H

#include <cstdint>
#include <vector>
#include <stack>
#include "ClassFile.h"

class Frame {
    public:
        std::vector<uint32_t> local_variables;
        std::stack<uint32_t> operand_stack;
        ClassFile* class_file;
        MethodInfo method;
        uint32_t pc;

        Frame(ClassFile&, MethodInfo, int);
};

#endif // JVM_FRAME_H