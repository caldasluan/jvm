#ifndef JVM_ATTRIBUTE_DEPRECATED_H
#define JVM_ATTRIBUTE_DEPRECATED_H

#include "../model/AttributeInfo.h"

class AttributeDeprecated : public AttributeInfo
{
public:
  AttributeDeprecated(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}
  // Nada;
};

#endif