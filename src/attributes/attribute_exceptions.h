#ifndef JVM_ATTRIBUTE_EXCEPTIONS
#define JVM_ATTRIBUTE_EXCEPTIONS

#include "../model/AttributeInfo.h"

class AttributeExceptions : public AttributeInfo
{
public:
  AttributeExceptions(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t number_of_exceptions;
  std::vector<uint16_t> exception_index_table;

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_EXCEPTIONS
