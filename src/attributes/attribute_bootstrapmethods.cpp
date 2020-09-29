#include "attribute_bootstrapmethods.h"

void AttributeBootstrapMethods::fillAttribute(FILE *file, ClassFile* classFile)
{
  num_bootstrap_methods = u2Read(file);
  bootstrap_methods = std::vector<bootstrap_method>(num_bootstrap_methods);

  for (int i = 0; i < num_bootstrap_methods; i++)
  {
    bootstrap_methods[i].bootstrap_method_ref = u2Read(file);
    bootstrap_methods[i].num_bootstrap_arguments = u2Read(file);
    bootstrap_methods[i].bootstrap_arguments = std::vector<uint16_t>(bootstrap_methods[i].num_bootstrap_arguments);

    for (int j = 0; j < bootstrap_methods[i].num_bootstrap_arguments; j++)
    {
      bootstrap_methods[i].bootstrap_arguments[j] = u2Read(file);
    }
  }
}

// TODO: test this
void AttributeBootstrapMethods::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*s%d bootstrap method%s\n",
         offset * OFFSET_AMMOUNT, "",
         num_bootstrap_methods,
         num_bootstrap_methods <= 1 ? "" : "s");
  uint16_t aux1;
  for (int i = 0; i < num_bootstrap_methods; i++)
  {
    printf("%*s%-4d Bootstrap method ref: %d < %s : %s >\n%*s%d argument%s\n",
           offset * OFFSET_AMMOUNT, "", i,
           bootstrap_methods[i].bootstrap_method_ref,
           classFile.get_string_constant_pool(bootstrap_methods[i].bootstrap_method_ref, 0).c_str(),
           (classFile.get_string_constant_pool(bootstrap_methods[i].bootstrap_method_ref)
           + "." + classFile.get_string_constant_pool(bootstrap_methods[i].bootstrap_method_ref, 1)).c_str(),
           offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", bootstrap_methods[i].num_bootstrap_arguments,
           bootstrap_methods[i].num_bootstrap_arguments == 1 ? "" : "s");
    for (int j = 0; j < bootstrap_methods[i].num_bootstrap_arguments; j++)
    {
      aux1 = bootstrap_methods[i].bootstrap_arguments[j];
      printf("%*s%-4d %d < %s >\n",
             offset * OFFSET_AMMOUNT + OFFSET_AMMOUNT, "", j,
             aux1, classFile.get_string_constant_pool(aux1).c_str());
    }
  }
}