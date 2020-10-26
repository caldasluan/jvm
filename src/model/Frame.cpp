#include "Frame.h"
#include "../attributes/attribute_code.h"

Frame::Frame(ClassFile& class_file, MethodInfo& method) {
    this->class_file = &class_file;
    this->pc = 0;
    this->method = &method;
    AttributeCode* code = dynamic_cast<AttributeCode*>(method.attributes[0].get());
    this->code = code;
    this->local_variables.resize(code->max_locals, 0);
}