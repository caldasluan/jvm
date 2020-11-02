#ifndef JVM_ATTRIBUTE_CODE_H
#define JVM_ATTRIBUTE_CODE_H

#include "../model/AttributeInfo.h"
#include <cstdint>

typedef struct
{
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
} exception;

class AttributeCode : public AttributeInfo
{
public:
  AttributeCode(uint16_t _name_index, uint32_t _length)
      : AttributeInfo(_name_index, _length)
  {
  }
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t* code;
  uint16_t exceptions_length;
  std::vector<exception> exceptions;
  uint16_t attribute_count;
  std::vector<std::shared_ptr<AttributeInfo>> attributes;

  ~AttributeCode();

  inline void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);

  void showCode(int offset, ClassFile& classFile);

  void showExceptions(int offset, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_CODE_H