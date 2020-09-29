#ifndef JVM_ATTRIBUTE_RUNTIMEANNOTATIONS_H
#define JVM_ATTRIBUTE_RUNTIMEANNOTATIONS_H

#include "../model/AttributeInfo.h"
#include "attribute_annotationdefault.h"

class AttributeRuntimeAnnotations : public AttributeInfo
{
public:
  AttributeRuntimeAnnotations(uint8_t _name_index, uint32_t _length, bool _visible)
      : AttributeInfo(_name_index, _length),
        visible(_visible) {}
  bool visible;
  uint16_t num_annotations;
  std::vector<annotation> annotations;

  ~AttributeRuntimeAnnotations()
  {
    for (int i = 0; i < num_annotations; i++)
    {
      deleteAnnotation(annotations[i]);
    }
  }

  void fillAttribute(FILE *file, ClassFile* classFile);

  virtual void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_RUNTIMEANNOTATIONS_H