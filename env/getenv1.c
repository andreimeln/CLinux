#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VARNAME ("XMY")

int main(int argc, char *argv[])
{
  char *Value = getenv(VARNAME);
  if (!Value)
    {
      fprintf(stderr,"Variable \"%s\" not found\n", VARNAME);
      return 1;
    }
  printf("%s\n", Value);
  return 0;
}
