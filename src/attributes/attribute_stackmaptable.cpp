#include "attribute_stackmaptable.h"

// At least it doesn't break
void AttributeStackMapTable::fillAttribute(FILE *file, ClassFile* classFile)
{
  fseek(file, length, SEEK_CUR);
}