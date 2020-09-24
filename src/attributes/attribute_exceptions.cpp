#include "attribute_exceptions.h"

void AttributeExceptions::fillAttribute(FILE *file, ClassFile* classFile)
{
  number_of_exceptions = u2Read(file);
  exception_index_table = std::vector<uint16_t>(number_of_exceptions);

  for (int i = 0; i < number_of_exceptions; i++)
  {
    exception_index_table[i] = u2Read(file);
    file += 2;
  }
}

// TODO: test this
void AttributeExceptions::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d exception%s\n",
         offset * OFFSET_AMMOUNT, "",
         (int)exception_index_table.size(),
         (int)exception_index_table.size() == 1 ? "" : "s");

  for (int i = 0; i < exception_index_table.size(); i++)
  {
    printf("%*s%-4d Exception: %d < %s >\n",
           offset * OFFSET_AMMOUNT, "", i,
           exception_index_table[i],
           classFile.get_string_constant_pool(exception_index_table[i]).c_str());
  }
}