#ifndef JVM_ATTRIBUTE_BOOTSTRAPMETHODS_H
#define JVM_ATTRIBUTE_BOOTSTRAPMETHODS_H

#include "../model/AttributeInfo.h"

typedef struct
{
  uint16_t bootstrap_method_ref;
  uint16_t num_bootstrap_arguments;
  std::vector<uint16_t> bootstrap_arguments;
} bootstrap_method;

class AttributeBootstrapMethods : public AttributeInfo
{
public:
  AttributeBootstrapMethods(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  uint16_t num_bootstrap_methods;
  std::vector<bootstrap_method> bootstrap_methods;

  void fillAttribute(FILE *file, ClassFile* classFile);

  virtual void showAttribute(int offset, int index, ClassFile& classFile);
};

#endif // JVM_ATTRIBUTE_BOOTSTRAPMETHODS_H