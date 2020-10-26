#include "Frame.h"

Frame::Frame(ClassFile& class_file, MethodInfo method, int max_local) {
    this->class_file = &class_file;
    this->method = method;
    this->pc = 0;
    this->local_variables.resize(max_local, 0);
}