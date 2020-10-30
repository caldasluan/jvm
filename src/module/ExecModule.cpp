#include <stack>
#include "ExecModule.h"
#include "../model/Frame.h"
#include "../attributes/instructions.h"

void mostra(Frame& frame) {
    printf("\npc: %d, instr: %02x pilha: %d\n", frame.pc, (uint8_t)frame.code->code[frame.pc], frame.operand_stack.size());
    printf("vetor: ");
    for (int i = 0; i < frame.local_variables.size(); i++) {
        printf("%d = %d, ", i, frame.local_variables[i]);
    }
    printf("\n");
    if (frame.operand_stack.size() > 0) printf("topo pilha: %d\n", frame.operand_stack.top());
}

void exec_jvm(ClassFile &classFile, MethodInfo& method) {
    std::stack<Frame> stack_frames;
    stack_frames.push(Frame(classFile, method));

    while (stack_frames.size() > 0) {
        // mostra(stack_frames.top());
        instructions_mnemonics[(uint8_t)stack_frames.top().code->code[stack_frames.top().pc]].execution(stack_frames.top());
        stack_frames.top().pc++;
        if (stack_frames.top().pc >= stack_frames.top().code->code_length) {
            stack_frames.pop();
        }
    }
}

// TODO passar argumentos da linha de comando pro metodo main
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