#include "ExecModule.h"
#include "../model/Frame.h"
#include "../attributes/instructions.h"

void mostra(Frame& frame) {
    printf("\npc: %d, instr: %02x pilha: %lu\n", frame.pc, (uint8_t)frame.code->code[frame.pc], frame.operand_stack.size());
    printf("vetor: ");
    for (int i = 0; i < frame.local_variables.size(); i++) {
        printf("%d = %d, ", i, frame.local_variables[i]);
    }
    printf("\n");
    if (frame.operand_stack.size() > 0) printf("topo pilha: %d\n", frame.operand_stack.top());
}

void ExecModule::exec_jvm(Runtime &runtime) {
    while (runtime.stack_frames.size() > 0) {
        Frame &frame = runtime.stack_frames.top();
        // mostra(frame);
         printf("%s.%s %d %d(%s)\n", frame.class_info->class_file->get_string_constant_pool(frame.class_info->class_file->this_class).c_str(), frame.class_info->class_file->get_string_constant_pool(frame.method->name_index).c_str(), frame.pc, frame.code->code[frame.pc], instructions_mnemonics[frame.code->code[frame.pc]].mnemonic);
         getchar();
        instructions_mnemonics[frame.code->code[frame.pc]].execution(frame);
        frame.pc++;
        if (frame.pc >= frame.code->code_length)
        {
            if(frame.ret_words == 1)
            {
                uint32_t ret = frame.operand_stack.top();
                runtime.stack_frames.pop();
                runtime.stack_frames.top().operand_stack.push(ret);
            }
            else if(frame.ret_words == 2)
            {
                uint32_t ret1 = frame.operand_stack.top();
                frame.operand_stack.pop();
                uint32_t ret2 = frame.operand_stack.top();
                runtime.stack_frames.pop();
                runtime.stack_frames.top().operand_stack.push(ret2);
                runtime.stack_frames.top().operand_stack.push(ret1);
            }
            else
                runtime.stack_frames.pop();
        }
    }
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
            runtime.stack_frames.push(Frame(class_info, method));
            class_info->clinitiated = true;
            break;
        }
    }

    // Despreza super class Object
    if (class_info->class_file->super_class != 0 && class_info->class_file->get_string_constant_pool(class_info->class_file->super_class).compare("java/lang/Object") != 0)
        clinit_loaded_classes(runtime, runtime.classMap[class_info->class_file->get_string_constant_pool(class_info->class_file->super_class)]);
}

// TODO passar argumentos da linha de comando pro metodo main
void ExecModule::initialize_jvm(const char *file_name)
{
    Runtime &runtime = Runtime::getInstance();

    ClassInfo *class_info = ExecModule::read_load_class(runtime, file_name);
    
    MethodInfo method_main;

    for (MethodInfo &method : class_info->class_file->methods)
    {
        if (class_info->class_file->get_string_constant_pool(method.name_index).compare("main") == 0 &&
            class_info->class_file->get_string_constant_pool(method.descriptor_index).compare("([Ljava/lang/String;)V") == 0 &&
            method.access_flags == 0x0009)
        {
            method_main = method;
            break;
        }
    }
    
    if (method_main.access_flags != 0)
    {
        runtime.stack_frames.push(Frame(class_info, method_main)); // Adiciona o metodo main como primeiro frame
        // so vai ser executado depois de todos os metodos <clinit> necessarios serem executados.
    }
    else
    {
        printf("Método main não encontrado!\n");
        return;
    }

    ExecModule::clinit_loaded_classes(runtime, class_info); // Adiciona metodos <clinit> da super classe mais alta na hierarquia ate a classe atual.

    exec_jvm(runtime);
}