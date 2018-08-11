#include "sema.h"
#include <stdio.h>

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

const char	* MySemaphore::szName = SEMNAME;
key_t	MySemaphore::iKey = -1;
int	MySemaphore::idSem = -1;
int	MySemaphore::nCount = 0;

MySemaphore::MySemaphore(int index)
{

  if (iKey < 0)
    {
      iKey = ftok(szName, 1);
      if (iKey == -1)
	throw (int)1;
      idSem = semget(iKey, 2, 0666 | IPC_CREAT);
    }
  iIndex = index;
  Buf.sem_num = iIndex;
  Buf.sem_flg = SEM_UNDO;
  union semun D;
  D.val = 1;
  semctl(idSem, 0, SETVAL, D);
  nCount++;
  lock();
}

MySemaphore::~MySemaphore()
{
  free();
  if (--nCount <= 0)
    {
      semctl(idSem, 2, IPC_RMID); // sem destruction
      iKey = -1;
      idSem = -1;
    }

}

void MySemaphore::lock() // sem grab
{
  Buf.sem_op = 1;
  int R = semop(idSem, (struct sembuf*)&Buf, 1);
  printf("%d\n", R);
}

void MySemaphore::free()
{

  Buf.sem_op = -1;
  int R = semop(idSem, (struct sembuf*)&Buf, 1);
  printf("%d\n", R);
}

