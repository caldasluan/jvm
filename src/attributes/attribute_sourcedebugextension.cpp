#include "attribute_sourcedebugextension.h"

void AttributeSourceDebugExtension::fillAttribute(FILE *file, ClassFile* classFile)
{
  debug_extension = new char[length];
  fread(debug_extension, length, 1, file);
}

// TODO test this (may be broken)
void AttributeSourceDebugExtension::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sDebug extension: %s",
         offset * OFFSET_AMMOUNT, "", debug_extension);
}