#ifndef JVM_CLASS_INFO_H
#define JVM_CLASS_INFO_H

#include <map>
#include <string>

#include "ClassFile.h"

class ClassInfo {
public:
    ClassFile *class_file;
    uint32_t fieldBytesAmmount;
    uint32_t staticBytesAmmount;
    uint8_t *staticBytes;
    bool clinitiated;
    std::map<std::string, uint32_t> staticIndexByName;
    std::map<std::string, uint32_t> fieldIndexByName;

    ClassInfo(ClassFile *_classFile) : class_file(_classFile), staticBytes(nullptr), staticBytesAmmount(0), fieldBytesAmmount(0), clinitiated(false) {};
};

ClassInfo *load_class(ClassFile *classFile, ClassInfo *superClassInfo, std::map<std::string, ClassInfo *> classMap);

#endif // JVM_CLASS_INFO_H