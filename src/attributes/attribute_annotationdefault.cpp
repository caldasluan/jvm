#include "attribute_annotationdefault.h"

AttributeAnnotationDefault::~AttributeAnnotationDefault()
{
  deleteElement(value);
}

void AttributeAnnotationDefault::fillAttribute(FILE *file, ClassFile* classFile)
{
  getElement(file, classFile, value);
}

void AttributeAnnotationDefault::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  showElement(value, offset, index, classFile);
}

void getElement(FILE *file, ClassFile* classFile, element_value &value)
{
  value.tag = u1Read(file);
  std::string CONST_VALUE_INDEX_TAGS = "BCDFIJSZs";
  if (CONST_VALUE_INDEX_TAGS.find(value.tag) != CONST_VALUE_INDEX_TAGS.size())
  {
    value.v.const_value_index = u2Read(file);
  }
  else if (value.tag == 'e')
  {
    value.v.enum_const_value.type_name_index = u2Read(file);
    value.v.enum_const_value.const_name_index = u2Read(file);
  }
  else if (value.tag == 'c')
  {
    value.v.class_info_index = u2Read(file);
  }
  else if (value.tag == '@')
  {
    value.v.annotation_value = new annotation;
    getAnnotation(file, classFile, *value.v.annotation_value);
  }
  else if (value.tag == '[')
  {
    value.v.array_value.num_values = u2Read(file);
    value.v.array_value.values = new std::vector<element_value>(value.v.array_value.num_values);
    for (int i = 0; i < value.v.array_value.num_values; i++)
    {
      getElement(file, classFile, (*value.v.array_value.values)[i]);
    }
  }
}

/*
Nao testado:
byte, char, short, boolean, array
O resto __deve__ funcionar
*/
void showElement(element_value &e, int offset, int index, ClassFile& classFile)
{
  printf("%*s    %c\n%*s",
         offset * OFFSET_AMMOUNT, "", e.tag,
         offset * OFFSET_AMMOUNT, "");
  switch (e.tag)
  {
  case 'B':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'C':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'D':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'F':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'I':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'J':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'S':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'Z':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 's':
    printf("Const index: %d < %s >\n",
           e.v.const_value_index,
           classFile.get_string_constant_pool(e.v.const_value_index).c_str());
    break;
  case 'e':
    printf("Enum type name index: %d < %s >\n%*sEnum const name index: %d < %s >\n",
           e.v.enum_const_value.type_name_index,
           classFile.get_string_constant_pool(e.v.enum_const_value.type_name_index).c_str(),
           offset * OFFSET_AMMOUNT, "",
           e.v.enum_const_value.const_name_index,
           classFile.get_string_constant_pool(e.v.enum_const_value.const_name_index).c_str());
    break;
  case 'c':
    printf("Const index: %d < %s >\n",
           e.v.class_info_index,
           classFile.get_string_constant_pool(e.v.class_info_index).c_str());
    break;
  case '@':
    showAnnotation(*e.v.annotation_value, offset + 1, 0, classFile);
    break;
  case '[':
    for (int i = 0; i < e.v.array_value.num_values; i++)
      showElement((*e.v.array_value.values)[i], offset + 1, i, classFile);
    break;
  }
}
void deleteElement(element_value &e)
{
  if (e.tag == '@')
  {
    deleteAnnotation(e.v.annotation_value);
    delete e.v.annotation_value;
  }
  else if (e.tag == '[')
  {
    for (int i = 0; i < e.v.array_value.values->size(); i++)
    {
      deleteElement(e.v.array_value.values->at(i));
    }
    delete e.v.array_value.values;
  }
}

void getAnnotation(FILE *file, ClassFile* classFile, annotation &a)
{
  a.type_index = u2Read(file);
  a.num_pairs = u2Read(file);

  if (a.num_pairs == 0)
  {
    return;
  }

  a.pairs = std::vector<std::pair<uint16_t, element_value>>(a.num_pairs);

  for (int i = 0; i < a.num_pairs; i++)
  {
    a.pairs[i].first = u2Read(file);
    getElement(file, classFile, a.pairs[i].second);
  }
}

void showAnnotation(annotation &a, int offset, int index, ClassFile& classFile)
{
  printf("%*s%4d Type index: %d < %s >\n%*sNum pairs: %d\n",
         offset * OFFSET_AMMOUNT, "", index,
         a.type_index, classFile.get_string_constant_pool(a.type_index).c_str(),
         (offset * OFFSET_AMMOUNT) + OFFSET_AMMOUNT, "",
         a.num_pairs);

  offset++;

  for (int i = 0; i < a.num_pairs; i++)
  {
    printf("%*s%4d Element name index: %d < %s >\n",
           offset + OFFSET_AMMOUNT, "", i,
           a.pairs[i].first, classFile.get_string_constant_pool(a.pairs[i].first).c_str());
    showElement(a.pairs[i].second, offset, i, classFile);
  }
}

void deleteAnnotation(annotation *a)
{
  for (int i = 0; i < a->num_pairs; i++)
  {
    deleteElement(a->pairs[i].second);
  }
  delete a;
}

void deleteAnnotation(annotation &a)
{
  for (int i = 0; i < a.num_pairs; i++)
  {
    deleteElement(a.pairs[i].second);
  }
}