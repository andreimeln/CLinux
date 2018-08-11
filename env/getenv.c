#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define VARNAME "YMY"

int main(int argc, char *argv[])
{

  if (argc < 2) {
    fprintf(stderr,"???\n");
    return 2;
  }

  const char *NewValue = argv[1]; // bad style??

  int Result = setenv(VARNAME,NewValue,1);
  if (Result)
    {
      fprintf(stderr,"Ashipka %d\n", errno);
      return 3;
    }

  char *Value = getenv(VARNAME);
  if (!Value)
    {
      fprintf(stderr,"Variable \"%s\" not found\n", VARNAME);
      return 1;
    }
  printf("%s\n", Value);
  return 0;
}
