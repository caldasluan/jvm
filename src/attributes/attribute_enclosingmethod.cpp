#include "attribute_enclosingmethod.h"

void AttributeEnclosingMethod::fillAttribute(FILE *file, ClassFile* classFile)
{
  class_index = u2Read(file);
  method_index = u2Read(file);
}

// TODO: test this
void AttributeEnclosingMethod::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sClass: %d < %s >\n%*sMethod: %d < %s >\n",
         offset * OFFSET_AMMOUNT, "", class_index, classFile.get_string_constant_pool(class_index).c_str(),
         offset * OFFSET_AMMOUNT, "", method_index, classFile.get_string_constant_pool(method_index).c_str());
}
