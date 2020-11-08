#include "ReadModule.h"
#include "../constants/CpTagConst.h"
#include "../model/FieldInfo.h"
#include "../model/AttributeInfo.h"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <fstream>

uint8_t u1Read(FILE* file) {
    uint8_t a;
    fread(&a, sizeof(uint8_t), 1, file);

    return a;
}

uint16_t u2Read(FILE* file) {
    return (u1Read(file) << 8) + u1Read(file);
}

uint32_t u4Read(FILE* file) {
    return (u2Read(file) << 16) + u2Read(file);
}

void fill_attributes_info(FILE* file, uint16_t size, std::vector<std::shared_ptr<AttributeInfo>>& attributes, ClassFile* classFile)
{
  attributes.clear();
  attributes.reserve(size);

  while (size--)
  {
    attributes.push_back(std::move(getAttribute(file, classFile)));
  }
}

void fill_constant_pool(FILE* file, uint16_t size, std::vector<CpInfo>& pool) {
    int i;
    pool.clear();
    pool.reserve(--size);

    while (size--) {
        CpInfo cpInfo;
        cpInfo.tag = u1Read(file);
        i = 0;

        if (cpInfo.tag == CpTagConst::CONSTANT_Class ||
                cpInfo.tag == CpTagConst::CONSTANT_String ||
                cpInfo.tag == CpTagConst::CONSTANT_MethodType) {
            i = 2;
        } else if (cpInfo.tag == CpTagConst::CONSTANT_MethodHandle) {
            i = 3;
        } else if (cpInfo.tag == CpTagConst::CONSTANT_Fieldref || 
                cpInfo.tag == CpTagConst::CONSTANT_NameAndType || 
                cpInfo.tag == CpTagConst::CONSTANT_Methodref ||
                cpInfo.tag == CpTagConst::CONSTANT_InterfaceMethodref ||
                cpInfo.tag == CpTagConst::CONSTANT_Integer ||
                cpInfo.tag == CpTagConst::CONSTANT_Float ||
                cpInfo.tag == CpTagConst::CONSTANT_InvokeDynamic) {
            i = 4;
        } else if (cpInfo.tag == CpTagConst::CONSTANT_Utf8) {
            cpInfo.info.push_back(u1Read(file));
            cpInfo.info.push_back(u1Read(file));
            i = (cpInfo.info[0] << 8) + cpInfo.info[1];
        } else if (cpInfo.tag == CpTagConst::CONSTANT_Long || cpInfo.tag == CpTagConst::CONSTANT_Double) {
            CpInfo cp;
            cp.tag = cpInfo.tag;
            cpInfo.tag = CpTagConst::CONSTANT_LargeNumeric;
            i = 8;
            while (i--) {
                cp.info.push_back(u1Read(file));
            }
            i = 0;
            pool.push_back(cp);
            size--;
        }

        while (i--) {
            cpInfo.info.push_back(u1Read(file));
        }
        pool.push_back(cpInfo);
    }
}

void fill_field_info(FILE* file, uint16_t size, std::vector<FieldInfo>& fields, ClassFile* classFile) {
    fields.clear();
    fields.reserve(size);
    while (size--) {
        FieldInfo field;

        field.access_flags = u2Read(file);
        field.name_index = u2Read(file);
        field.descriptor_index = u2Read(file);
        field.attributes_count = u2Read(file);

        fill_attributes_info(file, field.attributes_count, field.attributes, classFile);

        fields.push_back(field);
    }
}

void fill_method_info(FILE* file, uint16_t size, std::vector<MethodInfo>& methods, ClassFile* classFile) {
    methods.clear();
    methods.reserve(size);
    while (size--) {
        MethodInfo method;

        method.access_flags = u2Read(file);
        method.name_index = u2Read(file);
        method.descriptor_index = u2Read(file);
        method.attributes_count = u2Read(file);

        fill_attributes_info(file, method.attributes_count, method.attributes, classFile);

        methods.push_back(method);
    }
}

// TODO adicionar verificações na leitura da classe, retirar aviso na execucao quando nome da classe e arquivo forem diferentes
ClassFile* ReadModule::read_file(const char* file_name) {
    ClassFile *classFile = new ClassFile;
    FILE* fp;
    fp = fopen(file_name, "r");
    
    if(!fp)
    {
        printf("Nao foi possivel ler o arquivo!\n");
        return nullptr;
    }

    classFile->magic = u4Read(fp);
    classFile->minor_version = u2Read(fp);
    classFile->major_version = u2Read(fp);
    classFile->constant_pool_count = u2Read(fp);
    printf("");

    fill_constant_pool(fp, classFile->constant_pool_count, classFile->constant_pool);

    classFile->access_flags = u2Read(fp);
    classFile->this_class = u2Read(fp);
    
    std::string className = classFile->get_string_constant_pool(classFile->this_class) + ".class";
    std::string sFileName(file_name);
    if(sFileName.rfind(className, sFileName.find_last_of("/\\") + 1) == std::string::npos)
    {
        printf("Warning! Class name is different from file name!\n");
    }

    classFile->super_class = u2Read(fp);
    classFile->interfaces_count = u2Read(fp);

    classFile->interfaces.clear();
    classFile->interfaces.reserve(classFile->interfaces_count);
    for (int i = 0; i < classFile->interfaces_count; i++) {
        classFile->interfaces.push_back(u2Read(fp));
    }

    classFile->fields_count = u2Read(fp);

    fill_field_info(fp, classFile->fields_count, classFile->fields, classFile);

    classFile->methods_count = u2Read(fp);

    fill_method_info(fp, classFile->methods_count, classFile->methods, classFile);

    classFile->attributes_count = u2Read(fp);

    fill_attributes_info(fp, classFile->attributes_count, classFile->attributes, classFile);

    fclose(fp);

    return classFile;
}