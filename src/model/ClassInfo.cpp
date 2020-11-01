#include "ClassInfo.h"

ClassInfo *load_class(ClassFile *class_file, ClassInfo *super_class_info)
{
  ClassInfo *class_info = new ClassInfo(class_file);
  if(super_class_info != nullptr)
  {
    class_info->staticIndexByName.insert(super_class_info->staticIndexByName.begin(), super_class_info->staticIndexByName.end());
    class_info->staticVariablesBytesAmmount = super_class_info->staticVariablesBytesAmmount;
  }

  uint16_t field_size;
  for(FieldInfo fieldInfo : class_file->fields)
  {
     // Field Static
    if(fieldInfo.access_flags & 0x0008 && class_info->staticIndexByName.find(class_file->get_string_constant_pool(fieldInfo.name_index)) == class_info->staticIndexByName.end())
    {
      switch(class_file->get_string_constant_pool(fieldInfo.descriptor_index)[0])
      {
        case 'B':
        case 'C':
        case 'Z':
          field_size = 1;
          break;
        case 'S':
          field_size = 2;
          break;
        case 'F':
        case 'I':
          field_size = 4;
          break;
        case 'D':
        case 'J':
          field_size = 8;
          break;
        case 'L':
        case '[':
          field_size = sizeof(void *);
          break;
      }
      class_info->staticIndexByName[class_file->get_string_constant_pool(fieldInfo.name_index)] = class_info->staticVariablesBytesAmmount;
      class_info->staticVariablesBytesAmmount += field_size;
    }
  }

  class_info->staticVariablesBytes = new uint8_t[class_info->staticVariablesBytesAmmount]{0};

  return class_info;
}