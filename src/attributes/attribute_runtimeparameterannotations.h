#ifndef JVM_RUNTIMEPARAMETERANNOTATIONS_H
#define JVM_RUNTIMEPARAMETERANNOTATIONS_H

#include "../model/AttributeInfo.h"
#include "attribute_annotationdefault.h"

class AttributedRuntimeParameterAnnotations : public AttributeInfo
{
public:
  AttributedRuntimeParameterAnnotations(uint8_t _name_index, uint32_t _length, bool _visible)
      : AttributeInfo(_name_index, _length),
        visible(_visible) {}
  bool visible;
  uint8_t num_parameters;
  std::vector<std::vector<annotation>> parameter_annotations;

  ~AttributedRuntimeParameterAnnotations()
  {
    for (int i = 0; i < num_parameters; i++)
    {
      for (int j = 0; j < parameter_annotations[i].size(); j++)
      {
        deleteAnnotation(parameter_annotations[i][j]);
      }
    }
  }

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_RUNTIMEPARAMETERANNOTATIONS_H