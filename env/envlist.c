#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[])
{
  for (int k = 0; environ[k]; k++)
    {
      printf("%s\n", environ[k]);
    }

  return 0;
}
