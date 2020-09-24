#ifndef JVM_ATTRIBUTE_SOURCEDEBUGEXTENSION_H
#define JVM_ATTRIBUTE_SOURCEDEBUGEXTENSION_H

#include "../model/AttributeInfo.h"

class AttributeSourceDebugExtension : public AttributeInfo
{
public:
  AttributeSourceDebugExtension(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  char *debug_extension;
  
  ~AttributeSourceDebugExtension()
  {
    delete[] debug_extension;
  }

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_SOURCEDEBUGEXTENSION_H
