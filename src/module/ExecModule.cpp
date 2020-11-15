#include <cstring>
#include "ExecModule.h"
#include "../model/Frame.h"
#include "../attributes/instructions.h"
#include "../attributes/attribute_code.h"

void mostra(Frame *frame)
{
    printf("\n%s.%s.%d  %s  pilha: %lu\n", frame->class_info->class_file->get_string_constant_pool(frame->class_info->class_file->this_class).c_str(), frame->class_info->class_file->get_string_constant_pool(frame->method->name_index).c_str(), frame->pc, instructions_mnemonics[frame->code->code[frame->pc]].mnemonic, frame->operand_stack.size());
    printf("vetor: ");
    for (int i = 0; i < frame->local_variables.size(); i++)
    {
        printf("%d = %d, ", i, frame->local_variables[i]);
    }
    printf("\n");
    if (frame->operand_stack.size() > 0)
        printf("topo pilha: %d\n", frame->operand_stack.top());
}

void ExecModule::exec_jvm(Runtime &runtime)
{
    while (runtime.stack_frames.size() > 0)
    {
        Frame *frame = runtime.stack_frames.top();

        if(runtime.watch && frame->pc == runtime.watchPc)
        {
            mostra(frame);
            getchar();
        }
        else
        {
            if(runtime.verbose)
                mostra(frame);
            if(runtime.step)
                getchar();
        }

        try
        {
            instructions_mnemonics[frame->code->code[frame->pc]].execution(*frame);
        }
        catch (int e)
        {
            exception_jvm(runtime);
        }

        if (!frame->exception)
        {
            frame->pc++;
        }
        else
        {
            exception_jvm(runtime);
        }
    }
}

void ExecModule::exception_jvm(Runtime &runtime)
{
    while (runtime.stack_frames.size() > 0) {
        Frame *frame = runtime.stack_frames.top();
        frame->exception = false;
        for (exception& e : frame->code->exceptions) {
            if (e.start_pc <= frame->pc && e.end_pc > frame->pc) {
                frame->pc = e.handler_pc;
                frame->operand_stack.push(0);
                return;
            }
        }
        delete frame;
        runtime.stack_frames.pop();
        if (runtime.stack_frames.size() > 0)
            runtime.stack_frames.top()->pc--;
    }
    printf("Erro de execução do programa!\n");
}

ClassInfo *ExecModule::prepare_class(Runtime &runtime, std::string fileName)
{
    auto it = runtime.classMap.find(fileName);
    if (it == runtime.classMap.end())
    {
        uint32_t size = runtime.stack_frames.size();
        ClassInfo *class_info = read_load_class(runtime, (fileName + ".class").c_str());
        if(class_info == nullptr)
        {
            runtime.stack_frames.top()->exception = true; // Classe nao encontrada.
            return nullptr;
        }

        clinit_loaded_classes(runtime, class_info);
        if (size == runtime.stack_frames.size()) // Caso nao tenha sido adicionado nenhum frame com metodo <clinit>
            return class_info;
        return nullptr;
    }
    return it->second;
}

//TODO fazer a classe Object ser carregavel, nao faco ideia de como fazer isso ainda
// Le e aloca memoria pras variaveis estaticas, deixa preparadas pra rodar clinit, se houver.
ClassInfo *ExecModule::read_load_class(Runtime &runtime, const char *fileName)
{
    ClassFile *classFile = ReadModule::read_file(fileName, false);

    if(classFile == nullptr)
    {
        return nullptr;
    }

    runtime.classMap[classFile->get_string_constant_pool(classFile->this_class)] = nullptr;

    ClassInfo *superClassInfo = nullptr;

    std::string super_name;

    if (classFile->super_class != 0 && runtime.classMap.find(super_name = classFile->get_string_constant_pool(classFile->super_class)) == runtime.classMap.end())
    {
        if(super_name.compare("java/lang/Object") == 0)
            super_name = "Object";
        superClassInfo = ExecModule::read_load_class(runtime, (super_name + ".class").c_str());
    }

    for (uint16_t interface_index : classFile->interfaces)
    {
        ExecModule::read_load_class(runtime, (classFile->get_string_constant_pool(interface_index) + ".class").c_str());
    }

    ClassInfo *classInfo = load_class(classFile, superClassInfo, runtime.classMap);

    runtime.classMap[classFile->get_string_constant_pool(classFile->this_class)] = classInfo;

    return classInfo;
}

void ExecModule::clinit_loaded_classes(Runtime &runtime, ClassInfo *class_info)
{
    if (class_info->clinitiated == true)
        return;

    for (MethodInfo &method : class_info->class_file->methods)
    {
        bool method_name_equal = class_info->class_file->get_string_constant_pool(method.name_index).compare("<clinit>") == 0;
        bool method_desc_equal = class_info->class_file->get_string_constant_pool(method.descriptor_index).compare("()V") == 0;
        if (method_name_equal && method_desc_equal && (method.access_flags & 0x0008 || class_info->class_file->major_version < 51)) // so precisa ser estatica em Java 7+
        {
            // Metodo <clinit> encontrado
            runtime.stack_frames.push(new Frame(class_info, method));
            class_info->clinitiated = true;
            break;
        }
    }

    // Despreza super class Object
    if (class_info->class_file->super_class != 0 && class_info->class_file->get_string_constant_pool(class_info->class_file->super_class).compare("java/lang/Object") != 0)
        clinit_loaded_classes(runtime, runtime.classMap[class_info->class_file->get_string_constant_pool(class_info->class_file->super_class)]);
}

void ExecModule::initialize_jvm(const char *file_name, int argc, char *argv[])
{
    Runtime &runtime = Runtime::getInstance();

    ClassInfo *class_info = ExecModule::read_load_class(runtime, file_name);

    if(class_info == nullptr)
    {
        return;
    }

    MethodInfo method_main;

    for (MethodInfo &method : class_info->class_file->methods)
    {
        bool method_name_equal = class_info->class_file->get_string_constant_pool(method.name_index).compare("main") == 0;
        bool method_desc_equal = class_info->class_file->get_string_constant_pool(method.descriptor_index).compare("([Ljava/lang/String;)V") == 0;
        if (method_name_equal && method_desc_equal && method.access_flags == 0x0009)
        {
            method_main = method;
            break;
        }
    }

    if (method_main.access_flags != 0)
    {
        runtime.stack_frames.push(new Frame(class_info, method_main)); // Adiciona o metodo main como primeiro frame
        // so vai ser executado depois de todos os metodos <clinit> necessarios serem executados.
    }
    else
    {
        printf("Método main não encontrado!\n");
        return;
    }

    // Prepara argumentos da main
    array_t *ar = new array_t;
    ar->size = 4;
    ar->type = new char[20]{0};
    strcpy(ar->type, "[Ljava/lang/String;");
    uint8_t ignore = 2 + ((runtime.step || runtime.verbose || runtime.watch) ? 1 : 0);
    ar->length = argc - ignore;
    ar->bytes = new uint8_t[ar->length >= 1 ? ar->length * ar->size : 1]{0};
    for (int i = 0; i < argc - ignore; i++)
    {
        uint32_t value = runtime.instances.size();

        array_t *str = new array_t{0};
        str->type = new char[17]{0};
        strcpy(str->type, "java/lang/String");
        str->size = 1;
        str->length = strlen(argv[i + ignore]) + 1;
        str->bytes = new uint8_t[str->length]{0};
        strcpy((char *)str->bytes, argv[i + ignore]);

        runtime.instances.push_back((uint8_t *)str);
        ar->bytes[i * ar->size] = value >> 24;
        ar->bytes[i * ar->size + 1] = value >> 16;
        ar->bytes[i * ar->size + 2] = value >> 8;
        ar->bytes[i * ar->size + 3] = value;
    }
    runtime.stack_frames.top()->local_variables[0] = runtime.instances.size();
    runtime.instances.push_back((uint8_t *)ar);

    ExecModule::clinit_loaded_classes(runtime, class_info); // Adiciona metodos <clinit> da super classe mais alta na hierarquia ate a classe atual.

    exec_jvm(runtime);

    while(runtime.stack_frames.size() > 0)
    {
        delete runtime.stack_frames.top();
        runtime.stack_frames.pop();
    }
    
    for(uint8_t *inst : runtime.instances)
    {
        if(inst == nullptr)
            continue;
        if(((instance_t*)inst)->bytes != nullptr)
            delete[] ((instance_t*)inst)->bytes;
        delete[] inst;
    }

    for(auto it = runtime.classMap.begin(); it != runtime.classMap.end();it++)
    {
        delete it->second->class_file;
        delete it->second->staticBytes;
        delete it->second;
    }
}