#include "module/ReadModule.h"
#include "module/DisplayModule.h"

int main(int argc, char *argv[])
{
    if(argc > 1 && argc <= 3) {
        char *file = argv[1];
        ClassFile* classFile = ReadModule::read_file(file);
        
        if(classFile == nullptr)
            return 0;

        if(argc == 3) {
            if(argv[2][0] == '-' && argv[2][1] == 'i') {
                DisplayModule::show(*classFile);
            }
            else {
                printf("Opção inválida\n");
                delete classFile;
                return 0;
            }
        }
        else {
            printf("Execução em desenvolvimento\n");
            delete classFile;
            return 0;
        }
        delete classFile;
    }
    else {
        printf("\nExecução: ./jvm arquivo opção\n");
        printf("\nOpções:\n");
        printf("\t-i: leitor/exibidor de bytecode\n\n");
        return 0;
    }
}
