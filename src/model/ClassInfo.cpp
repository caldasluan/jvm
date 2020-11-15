#include "ClassInfo.h"
#include <cstring>

ClassInfo *load_class(ClassFile *class_file, ClassInfo *super_class_info, std::map<std::string, ClassInfo *> classMap)
{
  ClassInfo *class_info = new ClassInfo(class_file);
  if(super_class_info != nullptr)
  {
    class_info->staticIndexByName.insert(super_class_info->staticIndexByName.begin(), super_class_info->staticIndexByName.end());
    class_info->staticBytesAmmount = super_class_info->staticBytesAmmount;
    class_info->fieldIndexByName.insert(super_class_info->fieldIndexByName.begin(), super_class_info->fieldIndexByName.end());
    class_info->fieldBytesAmmount = super_class_info->fieldBytesAmmount;
  }
  
  uint16_t field_size;
  std::string field_name;
  for(uint16_t interface_index : class_file->interfaces)
  {
    ClassFile *interface_file = classMap[class_file->get_string_constant_pool(interface_index)]->class_file;
    for(FieldInfo field_info : interface_file->fields)
    {
      field_name = interface_file->get_string_constant_pool(field_info.name_index);
      if(class_info->staticIndexByName.find(field_name) == class_info->staticIndexByName.end())
      {
        field_size = FieldInfo::field_size_bytes(interface_file->get_string_constant_pool(field_info.descriptor_index));
        class_info->staticIndexByName[field_name] = class_info->staticBytesAmmount;
        class_info->staticBytesAmmount += field_size;
      }
    }
  }

  for(FieldInfo field_info : class_file->fields)
  {
    field_name = class_file->get_string_constant_pool(field_info.name_index);
    field_size = FieldInfo::field_size_bytes(class_file->get_string_constant_pool(field_info.descriptor_index));

    if(field_info.access_flags & 0x0008 && class_info->staticIndexByName.find(field_name) == class_info->staticIndexByName.end()) // static
    {
      class_info->staticIndexByName[field_name] = class_info->staticBytesAmmount;
      class_info->staticBytesAmmount += field_size;
    }
    else if(~field_info.access_flags & 0x0008 && class_info->fieldIndexByName.find(field_name) == class_info->fieldIndexByName.end()) // non static
    {
      class_info->fieldIndexByName[field_name] = class_info->fieldBytesAmmount;
      class_info->fieldBytesAmmount += field_size;
    }
  }

  // Cria um vetor onde serao armazenadas os campos estaticos dessa classe, caso haja algum.
  if(class_info->staticBytesAmmount != 0)
    class_info->staticBytes = new uint8_t[class_info->staticBytesAmmount]{0};

  return class_info;
}