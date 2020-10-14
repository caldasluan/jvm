#include "attribute_code.h"

AttributeCode::~AttributeCode()
{
  delete[] code;
  exceptions.clear();
  attributes.clear();
}

inline void AttributeCode::fillAttribute(FILE *file, ClassFile* classFile)
{
  max_stack = u2Read(file);
  max_locals = u2Read(file);
  code_length = u4Read(file);
  code = new char[code_length];
  fread(code, code_length, 1, file);
  exceptions_length = u2Read(file);
  exceptions.clear();
  exceptions.reserve(exceptions_length);
  for (int i = 0; i < exceptions_length; i++)
  {
    exception e;
    e.start_pc = u2Read(file);
    e.end_pc = u2Read(file);
    e.handler_pc = u2Read(file);
    e.catch_type = u2Read(file);
    exceptions.push_back(e);
  }
  attribute_count = u2Read(file);
  attributes.clear();
  attributes.reserve(attribute_count);
  for (int i = 0; i < attribute_count; i++)
  {
    attributes.push_back( std::move( std::shared_ptr<AttributeInfo>( getAttribute(file, classFile) ) ) );
  }
}

void AttributeCode::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sMax stack: %d\n%*sMax locals: %d\n%*sCode Length: %d\n%*sCode:\n",
         offset * OFFSET_AMMOUNT, "", max_stack,
         offset * OFFSET_AMMOUNT, "", max_locals,
         offset * OFFSET_AMMOUNT, "", code_length,
         offset * OFFSET_AMMOUNT, "");

  showCode(offset, classFile);

  // TODO: test this
  showExceptions(offset, classFile);

  show_attributes(offset, attributes, classFile);
}

uint8_t getU1(const char *&source)
{
  uint8_t target = *((uint8_t *)source);
  source += 1;
  return target;
}

uint16_t getU2(const char *&source)
{
  uint16_t target = *(const uint16_t *)source;
  target = __builtin_bswap16(target);

  source += 2;

  return target;
}

uint32_t getU4(const char *&source)
{
  uint32_t target = *(const uint32_t *)source;
  target = __builtin_bswap32(target);

  source += 4;

  return target;
}

void AttributeCode::showCode(int offset, ClassFile& classFile)
{
  uint32_t aux1, aux2, aux3, aux4;
  const char *codeV = code, *codeHelper;
  while (codeV < code + code_length)
  {
    printf("%*s%-4d %s",
           (offset * OFFSET_AMMOUNT) + OFFSET_AMMOUNT, "",
           (uint32_t)(codeV - code),
           instructions_mnemonics[(uint8_t)*codeV].mnemonic);

    switch (instructions_mnemonics[(uint8_t)*codeV++].operands)
    {
    case OP_NO:
      printf("\n");
      break;
    case OP_1_LV:
      printf(" %d\n", getU1(codeV));
      break;
    case OP_LDC:
      aux1 = getU1(codeV);
      printf(" #%d < %s >\n", (uint8_t)aux1, classFile.get_string_constant_complete(aux1).c_str());
      break;
    case OP_BIPUSH:
      printf(" %d\n", (int8_t)getU1(codeV));
      break;
    case OP_2_CP:
    case OP_2_CPWIDE:
      aux1 = getU2(codeV);
      printf(" #%d < %s >\n", aux1, classFile.get_string_constant_complete(aux1).c_str());
      break;
    case OP_SIPUSH:
      aux1 = getU2(codeV);
      printf(" %d\n", (int16_t)aux1);
      break;
    case OP_2_BRANCH:
      aux1 = getU2(codeV);
      printf(" %d (%+d)\n", (uint32_t)(codeV - code + (int32_t)aux1) - 3, (int32_t)aux1);
      break;
    case OP_4_BRANCH:
      aux1 = getU4(codeV);
      printf(" %d (%+d)\n", (uint32_t)(codeV - code + (int32_t)aux1) - 5, (int32_t)aux1);
      break;
    case OP_IINC:
      aux1 = getU1(codeV);
      aux2 = getU1(codeV);
      printf(" %d +(%d)\n", aux1, (int32_t)aux2);
      break;
    case OP_INVOKE_DYNAMIC:
      aux1 = getU2(codeV);
      printf(" #%d < %s >\n", aux1, classFile.get_string_constant_complete(aux1).c_str());
      codeV += 2;
      break;
    case OP_INVOKE_INTERFACE:
      aux1 = getU2(codeV);
      aux2 = getU1(codeV);
      printf(" #%d < %s >, count %d\n", aux1, classFile.get_string_constant_complete(aux1).c_str(), aux2);
      codeV++;
      break;
    case OP_LOOKUPSWITCH:
      codeHelper = codeV - 1;
      codeV += (uint64_t)codeV % 4;
      aux1 = getU4(codeV);
      aux2 = getU4(codeV);
      printf(" def %u(%+d), pairs: %d\n", (uint32_t)(codeHelper - code + (int32_t)aux1), (int32_t)aux1, aux2);
      for(int i = 0; i < aux2; i++)
      {
        aux3 = getU4(codeV);
        aux4 = getU4(codeV);
        printf("%*s%-4d %d - %u(%+d)\n",
          (offset * OFFSET_AMMOUNT) + 2 * OFFSET_AMMOUNT, "",
          i, (int32_t)aux3, (uint32_t)(codeHelper - code + (int32_t)aux4), (int32_t)aux4);
      }
      break;
    case OP_MULTIANEWARRAY:
      aux1 = getU2(codeV);
      aux2 = getU1(codeV);
      printf(" #%d < %s >, dimensions: %d\n", aux1, classFile.get_string_constant_complete(aux1).c_str(), aux2);
      break;
    case OP_NEWARRAY:
      aux1 = getU1(codeV);
      printf(" %d (%s)\n", aux1, array_types[aux1]);
      break;
    case OP_TABLESWITCH:
      codeHelper = codeV - 1;
      codeV += (uint64_t)codeV % 4;
      aux1 = getU4(codeV);
      aux2 = getU4(codeV);
      aux3 = getU4(codeV);
      printf(" def %u(%+d), low: %d, high: %d\n", (uint32_t)(codeHelper - code + (int32_t)aux1), (int32_t)aux1, (int32_t)aux2, (int32_t)aux3);
      for(int i = 0; i < (int32_t)aux3 - (int32_t)aux2 + 1; i++)
      {
        aux4 = getU4(codeV);
        printf("%*s%-4d %u(%+d)\n",
          (offset * OFFSET_AMMOUNT) + 2 * OFFSET_AMMOUNT, "",
          (int32_t)aux2 + i, (uint32_t)(codeHelper - code + (int32_t)aux4), (int32_t)aux4);
      }
      break;
    case OP_WIDE:
      aux1 = getU1(codeV);
      aux2 = getU2(codeV);
      if (aux1 == 0x84)
      {
        aux3 = getU2(codeV);
        printf(" iinc %d, %d\n", aux2, (int32_t)aux3);
        break;
      }
      printf(" %s %d\n", instructions_mnemonics[aux1].mnemonic, aux2);
      break;
    default:
      printf("\n");
      break;
    }
  }
}

void AttributeCode::showExceptions(int offset, ClassFile& classFile)
{
  printf("%*s%d exception%s\n", offset * OFFSET_AMMOUNT, "", exceptions_length, exceptions_length == 1 ? "" : "s");
  for (int i = 0; i < exceptions_length; i++)
  {
    printf("%*s%-4d Start pc: %d\n%*sEnd pc: %d\n%*sHandler pc: %d\n%*sCatch type: %d < %s >\n",
           offset * OFFSET_AMMOUNT, "", i, exceptions[i].start_pc,
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", exceptions[i].end_pc,
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", exceptions[i].handler_pc,
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", exceptions[i].catch_type,
           exceptions[i].catch_type ? classFile.get_string_constant_pool(exceptions[i].catch_type).c_str() : "All");
  }
}