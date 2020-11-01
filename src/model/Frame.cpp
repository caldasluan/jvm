#include "Frame.h"
#include "../attributes/attribute_code.h"

Frame::Frame(ClassInfo* class_info, MethodInfo& method) {
    this->class_info = class_info;
    this->pc = 0;
    this->method = &method;
    AttributeCode* code = dynamic_cast<AttributeCode*>(method.attributes[0].get());
    this->code = code;
    this->local_variables.resize(code->max_locals, 0);
    this->ret_words = 0;
}