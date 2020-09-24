#ifndef JVM_ATTRIBUTE_SOURCEFILE_H
#define JVM_ATTRIBUTE_SOURCEFILE_H

#include "../model/AttributeInfo.h"

class AttributeSourceFile : public AttributeInfo
{
public:
  AttributeSourceFile(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t sourcefile_index;

  void fillAttribute(FILE *file, ClassFile* classFile);

  virtual void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_SOURCEFILE_H