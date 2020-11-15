#ifndef JVM_RUNTIME_H
#define JVM_RUNTIME_H

#include <stack>
#include <vector>
#include <map>

#include "Frame.h"
#include "ClassInfo.h"


typedef struct {
    uint8_t *bytes;
    char *type;
    uint32_t size;
    uint32_t length;
} array_t;

typedef struct {
    uint8_t *bytes;
    char *type;
} instance_t;

class Runtime
{
public:
    std::stack<Frame*> stack_frames;
    std::vector<uint8_t *> instances;
    std::map<std::string, ClassInfo *> classMap;

    std::string exceptionName;
    std::string exceptionMethod;
    uint32_t exceptionPc;

    bool verbose, step, watch;
    uint32_t watchPc;

    static Runtime& getInstance() {
        static Runtime instance;
        return instance;
    }
    
    Runtime(Runtime const&) = delete;
    void operator=(Runtime const&) = delete;
private:
    Runtime() : verbose(false), step(false), watch(false), exceptionPc(-1)
    {
        instances.push_back(0); // NULL reference.
    };
};

#endif // JVM_RUNTIME_H