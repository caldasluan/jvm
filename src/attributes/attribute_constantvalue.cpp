#include "attribute_constantvalue.h"

void AttributeConstantValue::fillAttribute(FILE *file, ClassFile* classFile)
{
  constant_value = u2Read(file);
}

void AttributeConstantValue::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sConstant: %d < %s >\n",
         offset * OFFSET_AMMOUNT, "",
         constant_value, classFile.get_string_constant_pool(constant_value).c_str());
}
