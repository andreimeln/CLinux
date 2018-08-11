#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "sema.h"

int main(int argc, char *argv[])
{
  struct shared_memory *Mem = 0;
  int key = ftok("./server", 1);
  int idMem = shmget(key, sizeof(struct shared_memory), 0666 | IPC_CREAT);
  Mem = (struct shared_memory *)shmat(idMem, 0, 0);
  
  try
    {
      MySemaphore M(0);

      printf("%s [1]\n", argv[2]);

      Mem->status = 1;
      strncpy(Mem->szData, "Hello!\n", DATASIZE);
      Mem->sizedata = strlen(Mem->szData);

      sleep(atoi(argv[1]));
      printf("%s [2]\n", argv[2]);
    } catch (int)
    {
      fprintf(stderr, "Cannot create semaphore\n");
    }

  shmdt( (void*)Mem); // disconnect memory from pointer
  shmctl(idMem, IPC_RMID, 0); // disconnect memory from program
  return 0;
}
