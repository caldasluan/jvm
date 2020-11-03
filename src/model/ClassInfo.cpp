#include "ClassInfo.h"
#include <cstring>

// TODO incluir fields de interfaces, todos os fields de interfaces sao estaticos
ClassInfo *load_class(ClassFile *class_file, ClassInfo *super_class_info, std::map<std::string, ClassInfo *> classMap)
{
  ClassInfo *class_info = new ClassInfo(class_file);
  if(super_class_info != nullptr)
  {
    class_info->staticIndexByName.insert(super_class_info->staticIndexByName.begin(), super_class_info->staticIndexByName.end());
    class_info->staticVariablesBytesAmmount = super_class_info->staticVariablesBytesAmmount;
  }
  
  uint16_t field_size;
  for(uint16_t interface_index : class_file->interfaces)
  {
    ClassFile *interface_file = classMap[class_file->get_string_constant_pool(interface_index)]->class_file;
    for(FieldInfo field_info : interface_file->fields)
    {
      if(class_info->staticIndexByName.find(interface_file->get_string_constant_pool(field_info.name_index)) == class_info->staticIndexByName.end())
      {
        field_size = FieldInfo::field_size_bytes(interface_file->get_string_constant_pool(field_info.descriptor_index));
        class_info->staticIndexByName[interface_file->get_string_constant_pool(field_info.name_index)] = class_info->staticVariablesBytesAmmount;
        class_info->staticVariablesBytesAmmount += field_size;
      }
    }
  }

  for(FieldInfo field_info : class_file->fields)
  {
     // Field Static
    if(field_info.access_flags & 0x0008 && class_info->staticIndexByName.find(class_file->get_string_constant_pool(field_info.name_index)) == class_info->staticIndexByName.end())
    {
      field_size = FieldInfo::field_size_bytes(class_file->get_string_constant_pool(field_info.descriptor_index));
      class_info->staticIndexByName[class_file->get_string_constant_pool(field_info.name_index)] = class_info->staticVariablesBytesAmmount;
      class_info->staticVariablesBytesAmmount += field_size;
    }
  }

  if(class_info->staticVariablesBytesAmmount != 0)
    class_info->staticVariablesBytes = new uint8_t[class_info->staticVariablesBytesAmmount]{0};
  else
    class_info->staticVariablesBytes = nullptr;

  // Carrega variaveis estaticas finais
  /* if(super_class_info != nullptr)
    memcpy(class_info->staticVariablesBytes, super_class_info->staticVariablesBytes, super_class_info->staticVariablesBytesAmmount);
  
  for(uint16_t interface_index : class_file->interfaces)
  {
    ClassFile *interface_file = classMap[class_file->get_string_constant_pool(interface_index)]->class_file;
    for(FieldInfo field_info : interface_file->fields)
    {
      if(class_info->staticIndexByName.find(interface_file->get_string_constant_pool(field_info.name_index)) == class_info->staticIndexByName.end())
      {
        field_size = FieldInfo::field_size_bytes(interface_file->get_string_constant_pool(field_info.descriptor_index));
        class_info->staticIndexByName[interface_file->get_string_constant_pool(field_info.name_index)] = class_info->staticVariablesBytesAmmount;
        class_info->staticVariablesBytesAmmount += field_size;
      }
    }
  } */

  return class_info;
}