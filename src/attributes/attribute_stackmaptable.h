#ifndef JVM_ATTRIBUTE_STACKMAPTABLE_H
#define JVM_ATTRIBUTE_STACKMAPTABLE_H

#include "../model/AttributeInfo.h"

/*struct same_frame
{
};*/

/*typedef union
{
  uint8_t frame_type;
  //struct same_frame *sameFrame;
  //same_locals_1_stack_item_frame sameLocals1StackItemFrame;
  //same_locals_1_stack_item_frame_extended sameLocals1StackItemFrameExtended;
  //chop_frame chopFrame;
  //same_frame_extended sameFrameExtended;
  //append_frame appendFrame;
  //full_frame fullFrame;
} stack_map_frame;*/

class AttributeStackMapTable : public AttributeInfo
{
public:
  AttributeStackMapTable(uint16_t _name_index, uint32_t _length) : AttributeInfo(_name_index, _length) {}

  void fillAttribute(FILE *file, ClassFile* classFile);

  // Nao necessario.
};

#endif // JVM_ATTRIBUTE_STACKMAPTABLE_H