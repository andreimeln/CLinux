#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "sema.h"

int main(int argc, char *argv[])
{

  try
    {
      MySemaphore M(0);

      printf("%s [1]\n", argv[2]);
      sleep(atoi(argv[1]));
      printf("%s [2]\n", argv[2]);
    } catch (int)
    {
      fprintf(stderr, "Cannot create semaphore\n");
    }
  return 0;
}
