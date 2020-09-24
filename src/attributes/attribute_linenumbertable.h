#ifndef JVM_ATTRIBUTE_LINENUMBERTABLE_H
#define JVM_ATTRIBUTE_LINENUMBERTABLE_H

#include "../model/AttributeInfo.h"

typedef struct
{
  uint16_t start_pc;
  uint16_t line_number;
} line_number;

class AttributeLineNumberTable : public AttributeInfo
{
public:
  AttributeLineNumberTable(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t line_number_table_length;
  std::vector<line_number> line_number_table;

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_LINENUMBERTABLE_H