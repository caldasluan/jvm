#include "attribute_stackmaptable.h"

// THIS WILL BREAK
// TODO maybe make this not break
void AttributeStackMapTable::fillAttribute(FILE *file, ClassFile* classFile)
{
  entry_ammount = u2Read(file);
  entries = std::vector<stack_map_frame>(entry_ammount);
  for (int i = 0; i < entry_ammount; i++)
  {
    entries[i].frame_type = u1Read(file);
  }
}

// TODO the above is not implemented, will break d'oh
void AttributeStackMapTable::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d entr%s\n",
         offset * OFFSET_AMMOUNT, "",
         entry_ammount, entry_ammount == 1 ? "y" : "ies");

  int32_t currentOffset = -1;
  for (int i = 0; i < entry_ammount; i++)
  {
    currentOffset += entries[i].frame_type + 1;
    printf("%*s%-4d %d (%+d)\n",
           offset * OFFSET_AMMOUNT, "",
           i,
           currentOffset,
           entries[i].frame_type);
  }
}