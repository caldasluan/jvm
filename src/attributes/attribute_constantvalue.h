#ifndef JVM_ATTRIBUTE_CONSTANTVALUE_H
#define JVM_ATTRIBUTE_CONSTANTVALUE_H

#include "../model/AttributeInfo.h"

class AttributeConstantValue : public AttributeInfo
{
public:
  AttributeConstantValue(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t constant_value;

  void fillAttribute(FILE *file, ClassFile* classFile);

  virtual void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_CONSTANTVALUE_H