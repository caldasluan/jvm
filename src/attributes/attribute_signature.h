#ifndef JVM_ATTRIBUTE_SIGNATURE
#define JVM_ATTRIBUTE_SIGNATURE

#include "../model/AttributeInfo.h"

class AttributeSignature : public AttributeInfo
{
public:
  AttributeSignature(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t signature_index;

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_SIGNATURE
