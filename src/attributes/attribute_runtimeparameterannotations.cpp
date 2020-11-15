#include "attribute_runtimeparameterannotations.h"

void AttributedRuntimeParameterAnnotations::fillAttribute(FILE *file, ClassFile* classFile)
{
  num_parameters = u2Read(file);
  parameter_annotations = std::vector<std::vector<annotation>>(parameter_annotations);

  int num_annotations;
  for (int i = 0; i < num_parameters; i++)
  {
    num_annotations = u2Read(file);
    parameter_annotations[i] = std::vector<annotation>(num_annotations);

    for (int j = 0; j < num_annotations; j++)
    {
      getAnnotation(file, classFile, parameter_annotations[i][j]);
    }
  }
}

void AttributedRuntimeParameterAnnotations::showAttribute(int offset, int index, ClassFile& classFile)
{
  AttributeInfo::showAttribute(offset, index, classFile);
  printf("%*sAttr num annotations: %d\n",
         offset * OFFSET_AMMOUNT, "",
         num_parameters);
  for (int i = 0; i < num_parameters; i++)
  {
    printf("%*s%4d %d annotation%s\n",
           offset * OFFSET_AMMOUNT, "", i,
           (int)parameter_annotations[i].size(), parameter_annotations[i].size() == 1 ? "" : "s");
    for (int j = 0; j < parameter_annotations[i].size(); j++)
      showAnnotation(parameter_annotations[i][j], offset + 2, i, classFile);
  }
}