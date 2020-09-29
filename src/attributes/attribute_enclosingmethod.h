#ifndef JVM_ATTRIBUTE_ENCLOSINGMETHOD_H
#define JVM_ATTRIBUTE_ENCLOSINGMETHOD_H

#include "../model/AttributeInfo.h"

class AttributeEnclosingMethod : public AttributeInfo
{
public:
  AttributeEnclosingMethod(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t class_index;
  uint16_t method_index;

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_ENCLOSINGMETHOD_H