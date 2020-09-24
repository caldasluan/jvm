#ifndef JVM_ATTRIBUTE_INNERCLASSES_H
#define JVM_ATTRIBUTE_INNERCLASSES_H

#include "../model/AttributeInfo.h"
#include <map>

typedef struct
{
  uint16_t inner_class_info_index;
  uint16_t outer_class_info_index;
  uint16_t inner_name_index;
  uint16_t inner_class_access_flags;
} class_struct;

class AttributeInnerClasses : public AttributeInfo
{
public:
  AttributeInnerClasses(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t number_of_classes;
  std::vector<class_struct> classes;

  void fillAttribute(FILE *file, ClassFile* classFIle);

  void showAttribute(int offset, int index, ClassFile& classFIle);
};
const std::map<int, std::string> INNERCLASS_ACCESS_FLAGS_MAP = {
    {0x0001, "ACC_PUBLIC"},
    {0x0002, "ACC_PRIVATE"},
    {0x0004, "ACC_PROTECTED"},
    {0x0008, "ACC_STATIC"},
    {0x0010, "ACC_FINAL"},
    {0x0200, "ACC_INTERFACE"},
    {0x0400, "ACC_ABSTRACT"},
    {0x1000, "ACC_SYNTHETIC"},
    {0x2000, "ACC_ANNOTATION"},
    {0x4000, "ACC_ENUM"}};

void printAccessFlags(uint32_t accessFlags, const std::map<int, std::string> *access_flags_map);

#endif // JVM_ATTRIBUTE_INNERCLASSES_H