#include "attribute_linenumbertable.h"

void AttributeLineNumberTable::fillAttribute(FILE *file, ClassFile* classFile)
{
  line_number_table_length = u2Read(file);
  line_number_table = std::vector<line_number>(line_number_table_length);

  for (int i = 0; i < line_number_table_length; i++)
  {
    line_number_table[i].start_pc = u2Read(file);
    line_number_table[i].line_number = u2Read(file);
  }
}

void AttributeLineNumberTable::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d line number table length\n%*sStart pc | Line number\n",
         offset * OFFSET_AMMOUNT, "", line_number_table_length,
         offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "");
  for (int i = 0; i < line_number_table_length; i++)
  {
    printf("%*s%-4d %8d | %11d\n",
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT - 5, "",
           i,
           line_number_table[i].start_pc,
           line_number_table[i].line_number);
  }
}