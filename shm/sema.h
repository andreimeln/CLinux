#ifndef SEMA_H
#define SEMA_H

#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
	      
#define SEMNAME "./server"

class MySemaphore
{
 private:
  static const char *szName;
  static key_t iKey;
  static int idSem;
  static int nCount;

 private:
  int iIndex;
  struct sembuf Buf;

 private:
  void lock();
  void free();

 public:
  MySemaphore(int index);
  ~MySemaphore();
};

#define DATASIZE 512
struct shared_memory
{
  int status;
  int sizedata;
  char szData[DATASIZE];
};

#endif // SEMA_H
