#include "attribute_innerclasses.h"

void AttributeInnerClasses::fillAttribute(FILE *file, ClassFile* classFile)
{
  number_of_classes = u2Read(file);

  classes = std::vector<class_struct>(number_of_classes);

  for (int i = 0; i < number_of_classes; i++)
  {
    classes[i].inner_class_info_index = u2Read(file);
    classes[i].outer_class_info_index = u2Read(file);
    classes[i].inner_name_index = u2Read(file);
    classes[i].inner_class_access_flags = u2Read(file);
  }
}

void printAccessFlags(uint32_t accessFlags, const std::map<int, std::string> *access_flags_map)
{
  printf("Access flags: %#.4x   (", accessFlags);
  bool first = true;
  for (std::pair<int, std::string> el : *access_flags_map)
  {
    if ((accessFlags & el.first) != 0)
    {
      printf("%s%s", first ? "" : ", ", el.second.c_str());
      first = false;
    }
  }
  printf(")\n");
}

// TODO: test this
void AttributeInnerClasses::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d classes\n", offset * OFFSET_AMMOUNT, "", number_of_classes);
  for (int i = 0; i < number_of_classes; i++)
  {
    printf("%*s%-4d Inner class: %d < %s >\n%*s",
           offset * OFFSET_AMMOUNT, "", i,
           classes[i].inner_class_info_index, classFile.get_string_constant_pool(classes[i].inner_class_info_index).c_str(),
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "");
    if (classes[i].outer_class_info_index != 0)
      printf("Outer class: %d < %s >\n%*s",
             classes[i].outer_class_info_index, classFile.get_string_constant_pool(classes[i].outer_class_info_index).c_str(),
             offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "");
    if (classes[i].inner_name_index != 0)
      printf("Inner name: %d < %s >\n%*s",
             classes[i].inner_name_index, classFile.get_string_constant_pool(classes[i].inner_name_index).c_str(),
             offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "");
    printAccessFlags(classes[i].inner_class_access_flags, &INNERCLASS_ACCESS_FLAGS_MAP);
  }
}