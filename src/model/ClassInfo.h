#ifndef JVM_CLASS_INFO_H
#define JVM_CLASS_INFO_H

#include <map>
#include <string>

#include "ClassFile.h"

class ClassInfo {
public:
    ClassFile *class_file;
    uint16_t staticVariablesBytesAmmount;
    uint8_t *staticVariablesBytes;
    bool clinitiated;
    std::map<std::string, uint16_t> staticIndexByName;

    ClassInfo(ClassFile *_classFile) : class_file(_classFile), staticVariablesBytes(nullptr), staticVariablesBytesAmmount(0), clinitiated(false) {};
};

ClassInfo *load_class(ClassFile *classFile, ClassInfo *superClassInfo);

#endif // JVM_CLASS_INFO_H