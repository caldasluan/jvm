#include "attribute_sourcefile.h"

void AttributeSourceFile::fillAttribute(FILE *file, ClassFile* classFile)
{
  sourcefile_index = u2Read(file);
}

void AttributeSourceFile::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sSource file index: %d < %s >\n",
         offset * OFFSET_AMMOUNT, "",
         sourcefile_index,
         classFile.get_string_constant_pool(sourcefile_index).c_str());
}