#include "module/ReadModule.h"
#include "module/DisplayModule.h"

int main(int argc, char *argv[])
{
    char file[] = "input/MainAct.class";

    ClassFile* classFile = ReadModule::read_file(file);
    DisplayModule::show(*classFile);

    delete classFile;
}
