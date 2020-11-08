#ifndef JVM_FRAME_H
#define JVM_FRAME_H

#include <cstdint>
#include <vector>
#include <stack>
#include "ClassInfo.h"
#include "../attributes/attribute_code.h"

class Frame {
    public:
        std::vector<uint32_t> local_variables;
        std::stack<uint32_t> operand_stack;
        ClassInfo* class_info;
        MethodInfo* method;
        AttributeCode* code;
        uint32_t pc;
        uint8_t ret_words;
        bool exception = false;

        Frame(ClassInfo*, MethodInfo&);
};

#endif // JVM_FRAME_H