#include "attribute_runtimeannotations.h"

void AttributeRuntimeAnnotations::fillAttribute(FILE *file, ClassFile* classFile)
{
  num_annotations = u2Read(file);
  annotations = std::vector<annotation>(num_annotations);

  for (int i = 0; i < num_annotations; i++)
  {
    getAnnotation(file, classFile, annotations[i]);
  }
}

// TODO test this
void AttributeRuntimeAnnotations::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sAttr num annotations: %d\n",
         offset * OFFSET_AMMOUNT, "",
         num_annotations);
  for (int i = 0; i < num_annotations; i++)
    showAnnotation(annotations[i], offset + 1, i, classFile);
}