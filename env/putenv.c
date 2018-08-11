#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define VARNAME "YMY"
#define BUFSIZE (16*1024)

int main(int argc, char *argv[])
{

  if (argc < 2) {
    fprintf(stderr,"???\n");
    return 2;
  }

  const char *NewValue = argv[1];

  char *Buf = (char *)malloc(BUFSIZE);
  memset(Buf,0,BUFSIZE);

  strncpy(Buf,VARNAME,BUFSIZE-1);
  strncat(Buf,"=",BUFSIZE);
  strncat(Buf, NewValue, BUFSIZE-1);
  printf("%s\n", Buf);

  //int Result = setenv(VARNAME,NewValue,1);
  int Result = putenv(Buf);
  if (Result)
    {
      fprintf(stderr,"Ashipka %d\n", errno);
      return 3;
    }

  strncpy(Buf,"Vasya=Hello, world", BUFSIZE-1);

  char *Value = getenv(VARNAME);
  if (!Value)
    {
      fprintf(stderr,"Variable \"%s\" not found\n", VARNAME);
      return 1;
    }
  printf("%s\n", Value);

  free(Buf);

  return 0;
}
