#include "module/ReadModule.h"
#include "module/DisplayModule.h"
#include "module/ExecModule.h"
#include <cstring>

using namespace std;

void help ()
{
    printf("\nExecucao: ./jvm [flag] arquivo [argumentos]\n");
    printf("\nFlags:\n");
    printf("\t-i: Leitor/exibidor de bytecode\n\n");
    printf("Observacao: argumentos entre [] sao opcionais\n\n");
}

// JVM tem que passar argumentos pela linha de comando pro programa executado.
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'i' && strlen(argv[1]) == 2)
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
                printf("\nFlag invalida\n");
                help();
            }
        }
        else
        {
            char *fileName = argv[1];
            ExecModule::initialize_jvm(fileName, argc, argv);
        }
    }
    else
    {
        help();
    }
    return 0;
}