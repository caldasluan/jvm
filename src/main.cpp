#include "module/ReadModule.h"
#include "module/DisplayModule.h"
#include "module/ExecModule.h"
#include <cstring>

using namespace std;

void help ()
{
    printf("\nExecucao: ./jvm [opcao] arquivo\n");
    printf("\nOpcoes:\n");
    printf("\t-i: Leitor/exibidor de bytecode\n\n");
}

// JVM tem que passar argumentos pela linha de comando pro programa executado.
int main(int argc, char *argv[])
{
    if (argc > 1 && argc < 4)
    {
        if (argc == 2)
        {
            char *fileName = argv[1];
            ExecModule::initialize_jvm(fileName, argc, argv);
        }
        else
        {
            if (argv[1][0] == '-' && argv[1][1] == 'i' && strlen(argv[1]) == 2)
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
                help();
            }
        }
    }
    else
    {
        help();
    }
    return 0;
}
