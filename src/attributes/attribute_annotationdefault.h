#ifndef JVM_ATTRIBUTE_ANNOTATIONDEFAULT_H
#define JVM_ATTRIBUTE_ANNOTATIONDEFAULT_H

#include "../model/AttributeInfo.h"

struct annotation;

typedef struct element_value
{
  uint16_t element_name_index;
  uint8_t tag;
  union
  {
    uint16_t const_value_index;

    struct
    {
      uint16_t type_name_index;
      uint16_t const_name_index;
    } enum_const_value;

    uint16_t class_info_index;

    annotation *annotation_value;

    struct
    {
      uint16_t num_values;
      std::vector<element_value> *values;
    } array_value;
  } v;
} element_value;

struct annotation
{
  uint16_t type_index;
  uint16_t num_pairs;

  std::vector<std::pair<uint16_t, element_value>> pairs;
};

class AttributeAnnotationDefault : public AttributeInfo
{
public:
  AttributeAnnotationDefault(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  element_value value;

  ~AttributeAnnotationDefault();

  void fillAttribute(FILE *file, ClassFile* classFile);

  void showAttribute(int offset, int index, ClassFile& classFile);
};

void getElement(FILE *file, ClassFile* classFile, element_value &value);

void showElement(element_value &e, int offset, int index, ClassFile& classFile);

void deleteElement(element_value &e);

void getAnnotation(FILE *file, ClassFile* classFile, annotation &a);

void showAnnotation(annotation &a, int offset, int index, ClassFile& classFile);

void deleteAnnotation(annotation *a);

void deleteAnnotation(annotation &a);

#endif // JVM_ATTRIBUTE_ANNOTATIONDEFAULT_H