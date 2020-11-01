#ifndef JVM_RUNTIME_H
#define JVM_RUNTIME_H

#include <stack>
#include <vector>
#include <map>

#include "Frame.h"
#include "ClassInfo.h"


class Runtime
{
public:
    std::stack<Frame> stack_frames;
    std::vector<uint8_t *> instances;
    std::map<std::string, ClassInfo *> classMap;
};

#endif // JVM_RUNTIME_H