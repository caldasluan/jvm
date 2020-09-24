#include "AttributeInfo.h"
#include "../attributes/attribute_code.h"
#include "../attributes/attribute_synthetic.h"
#include "../attributes/attribute_signature.h"
#include "../attributes/attribute_exceptions.h"
#include "../attributes/attribute_deprecated.h"
#include "../attributes/attribute_sourcefile.h"
#include "../attributes/attribute_innerclasses.h"
#include "../attributes/attribute_constantvalue.h"
#include "../attributes/attribute_stackmaptable.h"
#include "../attributes/attribute_enclosingmethod.h"
#include "../attributes/attribute_linenumbertable.h"
#include "../attributes/attribute_bootstrapmethods.h"
#include "../attributes/attribute_annotationdefault.h"
#include "../attributes/attribute_localvariabletable.h"
#include "../attributes/attribute_sourcedebugextension.h"
#include "../attributes/attribute_localvariabletypetable.h"
#include "../attributes/attribute_runtimeannotations.h"
#include "../attributes/attribute_runtimeparameterannotations.h"


  void AttributeInfo::showAttribute(int offset, int index, ClassFile& classFile)
  {
    printf("%*s%4d Attr name: %d < %s >\n%*sAttr length: %d\n",
           offset * OFFSET_AMMOUNT - 5, "", index,
           name_index, classFile.get_string_constant_pool(name_index).c_str(),
           offset * OFFSET_AMMOUNT, "",
           length);
  }

AttributeInfo *getAttribute(FILE* file, ClassFile* classFile)
{
  AttributeInfo *attr;
  uint16_t name_index = u2Read(file);
  uint32_t length = u4Read(file);

  switch (std::find(ATTRIBUTE_NAMES.begin(), ATTRIBUTE_NAMES.end(), classFile->get_string_constant_pool(name_index).c_str()) - ATTRIBUTE_NAMES.begin())
  {
   case ATTRIBUTE_CODE:
    attr = new AttributeCode(name_index, length);
    break;
  case ATTRIBUTE_SYNTHETIC:
    attr = new AttributeSynthetic(name_index);
    break;
  case ATTRIBUTE_SIGNATURE:
    attr = new AttributeSignature(name_index, length);
    break;
  case ATTRIBUTE_EXCEPTIONS:
    attr = new AttributeExceptions(name_index, length);
    break;
  case ATTRIBUTE_SOURCE_FILE:
    attr = new AttributeSourceFile(name_index, length);
    break;
  case ATTRIBUTE_DEPRECATED:
    attr = new AttributeDeprecated(name_index, length);
    break;
  case ATTRIBUTE_INNER_CLASSES:
    attr = new AttributeInnerClasses(name_index, length);
    break;
  case ATTRIBUTE_CONSTANT_VALUE:
    attr = new AttributeConstantValue(name_index, length);
    break;
  case ATTRIBUTE_STACK_MAP_TABLE:
    attr = new AttributeStackMapTable(name_index, length);
    break;
  case ATTRIBUTE_ENCLOSING_METHOD:
    attr = new AttributeEnclosingMethod(name_index, length);
    break;
  case ATTRIBUTE_LINE_NUMBER_TABLE:
    attr = new AttributeLineNumberTable(name_index, length);
    break;
  case ATTRIBUTE_BOOTSTRAP_METHODS:
    attr = new AttributeBootstrapMethods(name_index, length);
    break;
  case ATTRIBUTE_ANNOTATION_DEFAULT:
    attr = new AttributeAnnotationDefault(name_index, length);
    break;
  case ATTRIBUTE_LOCAL_VARIABLE_TABLE:
    attr = new AttributeLocalVariableTable(name_index, length);
    break;
  case ATTRIBUTE_SOURCE_DEBUG_EXTENSION:
    attr = new AttributeSourceDebugExtension(name_index, length);
    break;
  case ATTRIBUTE_LOCAL_VARIABLE_TYPE_TABLE:
    attr = new AttributeLocalVariableTypeTable(name_index, length);
    break;
  case ATTRIBUTE_RUNTIME_VISIBLE_ANNOTATIONS:
    attr = new AttributeRuntimeAnnotations(name_index, length, true);
    break;
  case ATTRIBUTE_RUNTIME_INVISIBLE_ANNOTATIONS:
    attr = new AttributeRuntimeAnnotations(name_index, length, false);
    break;
  case ATTRIBUTE_RUNTIME_VISIBLE_PARAMENTER_ANNOTATIONS:
    attr = new AttributedRuntimeParameterAnnotations(name_index, length, true);
    break;
  case ATTRIBUTE_RUNTIME_INVISIBLE_PARAMETER_ANNOTATIONS:
    attr = new AttributedRuntimeParameterAnnotations(name_index, length, false);
    break; 
  default:
    attr = new AttributeInfo(name_index, length); 
    fseek(file, length, SEEK_CUR);
    break;
  }

  attr->fillAttribute(file, classFile);

  return attr;
}

// Offset is given in collumns, each having 4 whitespaces.
void show_attributes(int offset, std::vector<std::shared_ptr<AttributeInfo>> &attributes, ClassFile& classFile)
{
  if (offset == 0)
    printf("Attributes:\n");
  printf("%*sAttribute ammount:\t%d\n",
         offset * OFFSET_AMMOUNT, "",
         (int)attributes.size());
  offset++;
  for (int i = 0; i < attributes.size(); i++)
  {
    attributes[i]->showAttribute(offset, i, classFile);
  }
}