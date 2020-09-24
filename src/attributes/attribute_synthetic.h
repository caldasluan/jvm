#ifndef JVM_ATTRIBUTE_SYNTHETIC
#define JVM_ATTRIBUTE_SYNTHETIC

#include "../model/AttributeInfo.h"

class AttributeSynthetic : public AttributeInfo
{
public:
  AttributeSynthetic(uint16_t _name_index) : AttributeInfo(_name_index, 0) {}
  // Nada;
};

#endif // JVM_ATTRIBUTE_SYNTHETIC