#include "FieldInfo.h"

uint8_t FieldInfo::field_size_bytes(std::string descr)
{
  switch(descr[0])
  {
    case 'B': // Byte
    case 'C': // Char
    case 'Z': // Bool
      return 1;
    case 'S': // Short
      return 2;
    case 'F': // Float
    case 'I': // Int
      return 4;
    case 'D': // Double
    case 'J': // Long
      return 8;
    case 'L': // Reference
    case '[': // Array Reference
      return sizeof(void *);
  }
  return 0;
}