#include "module/ReadModule.h"
#include "module/DisplayModule.h"
#include "module/ExecModule.h"

// JVM tem que passar argumentos pela linha de comando pro programa executado.
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'i')
        {
            char *fileName = argv[2];
            ClassFile *classFile = ReadModule::read_file(fileName);
            if (classFile == nullptr)
                return 0;

            DisplayModule::show(*classFile);
            delete classFile;
        }
        else
        {
            char *fileName = argv[1];
            ExecModule::initialize_jvm(fileName, argc, argv);
        }
    }
    else
    {
        printf("\nExecucao: ./jvm arquivo opcao\n");
        printf("\nOpcoes:\n");
        printf("\t-i: leitor/exibidor de bytecode\n\n");
    }
    return 0;
}
