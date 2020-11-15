#include "attribute_signature.h"

void AttributeSignature::fillAttribute(FILE *file, ClassFile* classFile)
{
  signature_index = u2Read(file);
  file += 8;
}

void AttributeSignature::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sAttr const. index: %d < %s > \n",
         offset * OFFSET_AMMOUNT, "",
         signature_index, classFile.get_string_constant_pool(signature_index).c_str());
}