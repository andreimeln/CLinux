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
  
  printf("status = %d, data = %s\n", Mem->status, Mem->szData);

  shmdt( (void*)Mem); // disconnect memory from pointer
  shmctl(idMem, IPC_RMID, 0); // disconnect memory from program
  return 0;
}
