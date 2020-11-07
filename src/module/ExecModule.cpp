#include <cstring>
#include "ExecModule.h"
#include "../model/Frame.h"
#include "../attributes/instructions.h"

void mostra(Frame& frame) {
    printf("\n%s.%s.%d  %s  pilha: %lu\n", frame.class_info->class_file->get_string_constant_pool(frame.class_info->class_file->this_class).c_str(), frame.class_info->class_file->get_string_constant_pool(frame.method->name_index).c_str(), frame.pc, instructions_mnemonics[frame.code->code[frame.pc]].mnemonic, frame.operand_stack.size());
    printf("vetor: ");
    for (int i = 0; i < frame.local_variables.size(); i++) {
        printf("%d = %d, ", i, frame.local_variables[i]);
    }
    printf("\n");
    if (frame.operand_stack.size() > 0) printf("topo pilha: %d\n", frame.operand_stack.top());
}

void ExecModule::exec_jvm(Runtime &runtime) {
    while (runtime.stack_frames.size() > 0) {
        Frame* frame = runtime.stack_frames.top();
        // mostra(frame);
        // printf("%s.%s %d %d(%s)\n", frame.class_info->class_file->get_string_constant_pool(frame.class_info->class_file->this_class).c_str(), frame.class_info->class_file->get_string_constant_pool(frame.method->name_index).c_str(), frame.pc, frame.code->code[frame.pc], instructions_mnemonics[frame.code->code[frame.pc]].mnemonic);
        //getchar();
        instructions_mnemonics[frame->code->code[frame->pc]].execution(*frame);
        frame->pc++;

        if (frame->pc >= frame->code->code_length)
        {
            if(frame->ret_words == 1)
            {
                uint32_t ret = frame->operand_stack.top();
                delete runtime.stack_frames.top();
                runtime.stack_frames.pop();
                runtime.stack_frames.top()->operand_stack.push(ret);
            }
            else if(frame->ret_words == 2)
            {
                uint32_t ret1 = frame->operand_stack.top();
                frame->operand_stack.pop();
                uint32_t ret2 = frame->operand_stack.top();
                delete runtime.stack_frames.top();
                runtime.stack_frames.pop();
                runtime.stack_frames.top()->operand_stack.push(ret2);
                runtime.stack_frames.top()->operand_stack.push(ret1);
            }
            else
                runtime.stack_frames.pop();
        }
    }
}

ClassInfo *ExecModule::prepare_class(Runtime &runtime, std::string fileName)
{
    auto it = runtime.classMap.find(fileName);
    if(it == runtime.classMap.end())
    {
        uint32_t size = runtime.stack_frames.size();
        ClassInfo *class_info = read_load_class(runtime, (fileName + ".class").c_str());
        clinit_loaded_classes(runtime, class_info);
        if(size == runtime.stack_frames.size()) // Caso nao tenha sido adicionado nenhum frame com metodo <clinit>
            return class_info;
        return nullptr;
    }
    return it->second;
}

//TODO fazer a classe Object ser carregavel, nao faco ideia de como fazer isso ainda
// Le e aloca memoria pras variaveis estaticas, deixa preparadas pra rodar clinit, se houver.
ClassInfo* ExecModule::read_load_class(Runtime &runtime, const char* fileName)
{
    ClassFile *classFile = ReadModule::read_file(fileName);

    runtime.classMap[classFile->get_string_constant_pool(classFile->this_class)] = nullptr;

    ClassInfo *superClassInfo = nullptr;
    
    // Despreza super class Object
    if(classFile->super_class != 0 && runtime.classMap.find(classFile->get_string_constant_pool(classFile->super_class)) == runtime.classMap.end() && classFile->get_string_constant_pool(classFile->super_class).compare("java/lang/Object") != 0)
    {
        superClassInfo = ExecModule::read_load_class(runtime, (classFile->get_string_constant_pool(classFile->super_class) + ".class").c_str());
    }
    
    for(uint16_t interface_index : classFile->interfaces)
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
    
    for(MethodInfo &method : class_info->class_file->methods)
    {
        if (class_info->class_file->get_string_constant_pool(method.name_index).compare("<clinit>") == 0 && class_info->class_file->get_string_constant_pool(method.descriptor_index).compare("()V") == 0 && method.access_flags & 0x0008)
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
    ar->lenght = argc - 2;
    ar->bytes = new uint8_t[ar->lenght > 1 ? ar->lenght * ar->size : 1]{0};
    for (int i = 2; i < argc; i++) {
        runtime.instances.push_back((uint8_t *)argv[i]);
        uint32_t value = runtime.instances.size() - 1;
        ar->bytes[(i - 2) * ar->size] = value >> 24;
        ar->bytes[(i - 2) * ar->size + 1] = value >> 16;
        ar->bytes[(i - 2) * ar->size + 2] = value >> 8;
        ar->bytes[(i - 2) * ar->size + 3] = value;
    }
    runtime.instances.push_back((uint8_t *)ar);
    runtime.stack_frames.top()->local_variables[0] = runtime.instances.size() - 1;

    ExecModule::clinit_loaded_classes(runtime, class_info); // Adiciona metodos <clinit> da super classe mais alta na hierarquia ate a classe atual.


    exec_jvm(runtime);
}