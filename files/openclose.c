#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FAMSIZE (35)

struct _man_str
{
  char szFam[FAMSIZE];
  int nResult;
};

typedef struct _man_str MAN;

int main(int argc, char *argv[])
{

  int TRG = open("myfile.dat",O_CREAT | O_WRONLY,0644);

  MAN X;

  strncpy(X.szFam,"Pupkin", FAMSIZE-1);
  X.nResult = 25;
  write(TRG,&X,sizeof(X));

  /*
    strncpy(X.szFam,"Vaskin", FAMSIZE-1);
    X.nResult = 15;
    write(TRG,&X,sizeof(X));
  */

  strncpy(X.szFam,"Ivanoff", FAMSIZE-1);
  X.nResult = 15;
  write(TRG,&X,sizeof(X));

  //lseek(TRG,sizeof(MAN),SEEK_CUR);
  lseek(TRG,1000*sizeof(MAN),SEEK_END);

  strncpy(X.szFam,"Petroff", FAMSIZE-1);
  X.nResult = 21;
  write(TRG,&X,sizeof(X));


  /*
    strncpy(X.szFam,"Petkin", FAMSIZE-1);
    X.nResult = 17;
    write(TRG,&X,sizeof(X));
  */

  close(TRG);
  return 0;
}
