#include "module/ReadModule.h"
#include "module/DisplayModule.h"
#include "module/ExecModule.h"
#include <cstring>

using namespace std;

void help ()
{
    printf("\nExecucao: ./jvm [flag] arquivo [argumentos]\n");
    printf("\nFlags (somente uma deve ser usada):\n");
    printf("\t-i:   Leitor/exibidor de bytecode\n\n");
    printf("\t-v:   Executa o .class mostrando cada instrucao executada\n\n");
    printf("\t-s:   Executa o .class mostrando cada instrucao e fazendo\n");
    printf("\t      uma pausa antes de executa-la\n\n");
    printf("\t-wpc: pc deve ser um numero inteiro. Executa o .class, quando\n");
    printf("\t      pc do frame atual for igual ao pc passado a instrucao\n");
    printf("\t      em pc eh exibida e uma pausa eh feita. Exemplo: -w53\n\n");
    printf("Observacao: argumentos entre [] sao opcionais\n\n");
}

// JVM tem que passar argumentos pela linha de comando pro programa executado.
int main(int argc, char *argv[])
{
    bool show = false;
    if (argc > 1)
    {
        char *fileName = argv[1];

        if (argv[1][0] == '-')
        {
            Runtime &runtime = Runtime::getInstance();
            if (strlen(argv[1]) == 2 && argv[1][1] == 'i')
            {
                show = true;
            }
            else if(strlen(argv[1]) == 2 && (argv[1][1] == 'v' || argv[1][1] == 's'))
            {
                runtime.verbose = true;
                runtime.step = argv[1][1] == 's';
            }
            else if(strlen(argv[1]) > 2 && (argv[1][1] == 'w') && std::isdigit(argv[1][2]))
            {
                runtime.watch = true;
                runtime.watchPc = std::atoi((argv[1] + 2));
            }
            else
            {
                printf("\nFlag %s invalida\n", argv[1]);
                help();
                return 1;
            }
            fileName = argv[2];
        }

        if(show)
        {
            ClassFile *classFile = ReadModule::read_file(fileName, true);
            if (classFile == nullptr)
                return 0;

            DisplayModule::show(*classFile);
            delete classFile;
        }
        else
        {
            ExecModule::initialize_jvm(fileName, argc, argv);
        }
    }
    else
    {
        help();
        return 1;
    }
    return 0;
}