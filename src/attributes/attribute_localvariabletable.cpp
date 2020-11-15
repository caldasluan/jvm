#include "attribute_localvariabletable.h"

void AttributeLocalVariableTable::fillAttribute(FILE *file, ClassFile* classFile)
{
  local_variable_table_length = u2Read(file);
  local_variable_table = std::vector<local_variable>(local_variable_table_length);

  for (int i = 0; i < local_variable_table_length; i++)
  {
    local_variable_table[i].start_pc = u2Read(file);
    local_variable_table[i].length = u2Read(file);
    local_variable_table[i].name_index = u2Read(file);
    local_variable_table[i].descriptor_index = u2Read(file);
    local_variable_table[i].index = u2Read(file);
  }
}

void AttributeLocalVariableTable::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d local variable%s\n",
         offset * OFFSET_AMMOUNT, "",
         local_variable_table_length, local_variable_table_length == 1 ? "" : "s");
  for (int i = 0; i < local_variable_table_length; i++)
  {
    printf("%*s%4d Start pc: %d, length: %d\n%*sName: %d < %s >\n%*sDescriptor: %d < %s >\n%*sLocal variable index: %d\n",
           offset * OFFSET_AMMOUNT, "", i,
           local_variable_table[i].start_pc, local_variable_table[i].length,
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "",
           local_variable_table[i].name_index, classFile.get_string_constant_pool(local_variable_table[i].name_index).c_str(),
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "",
           local_variable_table[i].descriptor_index, classFile.get_string_constant_pool(local_variable_table[i].descriptor_index).c_str(),
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", local_variable_table[i].index);
  }
}