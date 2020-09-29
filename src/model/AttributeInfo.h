#ifndef ATTRIBUTE_INFO_H
#define ATTRIBUTE_INFO_H

#include <cstdint>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>

class ClassFile;

#include "CpInfo.h"

#define OFFSET_AMMOUNT 8

#define ATTRIBUTE_CODE 0
#define ATTRIBUTE_SYNTHETIC 1
#define ATTRIBUTE_SIGNATURE 2
#define ATTRIBUTE_EXCEPTIONS 3
#define ATTRIBUTE_DEPRECATED 4
#define ATTRIBUTE_SOURCE_FILE 5
#define ATTRIBUTE_INNER_CLASSES 6
#define ATTRIBUTE_CONSTANT_VALUE 7
#define ATTRIBUTE_STACK_MAP_TABLE 8
#define ATTRIBUTE_ENCLOSING_METHOD 9
#define ATTRIBUTE_LINE_NUMBER_TABLE 10
#define ATTRIBUTE_BOOTSTRAP_METHODS 11
#define ATTRIBUTE_ANNOTATION_DEFAULT 12
#define ATTRIBUTE_LOCAL_VARIABLE_TABLE 13
#define ATTRIBUTE_SOURCE_DEBUG_EXTENSION 14
#define ATTRIBUTE_LOCAL_VARIABLE_TYPE_TABLE 15
#define ATTRIBUTE_RUNTIME_VISIBLE_ANNOTATIONS 16
#define ATTRIBUTE_RUNTIME_INVISIBLE_ANNOTATIONS 17
#define ATTRIBUTE_RUNTIME_VISIBLE_PARAMENTER_ANNOTATIONS 18
#define ATTRIBUTE_RUNTIME_INVISIBLE_PARAMETER_ANNOTATIONS 19

class AttributeInfo
{
public:
  uint16_t name_index;
  uint32_t length;
  AttributeInfo() {}
  AttributeInfo(uint16_t _name_index, uint32_t _length)
      : name_index(_name_index),
        length(_length) {}

  virtual void fillAttribute(FILE* file, ClassFile* classFile) {}
  virtual void showAttribute(int offset, int index, ClassFile& classFile);
};

#include "ClassFile.h"
#include "../module/ReadModule.h"

std::shared_ptr<AttributeInfo> getAttribute(FILE* file, ClassFile* classFile);

void show_attributes(int offset, std::vector<std::shared_ptr<AttributeInfo>> &attributes, ClassFile& classFile);

const std::array<std::string, 20> ATTRIBUTE_NAMES = {
    "Code",
    "Synthetic",
    "Signature",
    "Exceptions",
    "Deprecated",
    "SourceFile",
    "InnerClasses",
    "ConstantValue",
    "StackMapTable",
    "EnclosingMethod",
    "LineNumberTable",
    "BootstrapMethods",
    "AnnotationDefault",
    "LocalVariableTable",
    "SourceDebugExtension",
    "LocalVariableTypeTable",
    "RuntimeVisibleAnnotations",
    "RuntimeInvisibleAnnotations",
    "RuntimeVisibleParameterAnnotations",
    "RuntimeInvisibleParameterAnnotations"};

#endif // ATTRIBUTE_INFO_H