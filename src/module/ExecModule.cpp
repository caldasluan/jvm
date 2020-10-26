#include <stack>
#include "ExecModule.h"
#include "../model/Frame.h"
#include "../attributes/instructions.h"

void exec_jvm(ClassFile &classFile, MethodInfo& method) {
    std::stack<Frame> stack_frames;
    Frame current_frame = Frame(classFile, method);

    while (current_frame.pc <= current_frame.code->code_length || stack_frames.size() > 0) {
        printf("pc: %d\n", current_frame.pc);
        instructions_mnemonics[current_frame.code->code[current_frame.pc]].execution(current_frame);
        current_frame.pc++;
    }
}

void ExecModule::exec(ClassFile &classFile)
{
    MethodInfo method_main;

    for (MethodInfo method : classFile.methods)
    {
        if (classFile.get_string_constant_complete(method.name_index).compare("main") == 0 &&
            classFile.get_string_constant_complete(method.descriptor_index).compare("([Ljava/lang/String;)V") == 0 &&
            method.access_flags == 0x0009)
        {
            method_main = method;
            break;
        }
    }

    if (method_main.access_flags != 0)
    {
        exec_jvm(classFile, method_main);
    }
    else
    {
        printf("Método main não encontrado!\n");
    }
}