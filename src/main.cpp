#include "module/ReadModule.h"
#include "module/DisplayModule.h"
#include "module/ExecModule.h"

int main(int argc, char *argv[])
{
    if(argc > 1 && argc <= 3) {
        char *fileName = argv[1];
        
        if(argc == 3) {
            if(argv[2][0] == '-' && argv[2][1] == 'i') {
                ClassFile* classFile = ReadModule::read_file(fileName);
                if(classFile == nullptr)
                    return 0;
                
                DisplayModule::show(*classFile);
                delete classFile;
            }
            else {
                printf("Opcao invalida\n");
                return 0;
            }
        }
        else {
            ExecModule::initialize_jvm(fileName);
        }
    }
    else {
        printf("\nExecucao: ./jvm arquivo opcao\n");
        printf("\nOpcoes:\n");
        printf("\t-i: leitor/exibidor de bytecode\n\n");
    }
    return 0;
}
