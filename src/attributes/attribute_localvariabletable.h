#ifndef JVM_ATTRIBUTE_LOCALVARIABLETABLE_H
#define JVM_ATTRIBUTE_LOCALVARIABLETABLE_H

#include "../model/AttributeInfo.h"

typedef struct
{
  uint16_t start_pc;
  uint16_t length;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t index;
} local_variable;

class AttributeLocalVariableTable : public AttributeInfo
{
public:
  AttributeLocalVariableTable(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t local_variable_table_length;
  std::vector<local_variable> local_variable_table;

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_LOCALVARIABLETABLE_H