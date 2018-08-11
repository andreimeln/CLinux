#include <stdio.h>
#include <string.h>

int parent(int SRC)
{
  //printf("Parent\n");

  char Buf[16*1024];

  for(;;)
    {
      int Count = read(SRC, Buf, sizeof(Buf));
      if (Count <= 0)
	break;
      printf("[%s]\n", Buf);
    }

  return 0;
}

int child(int TRG)
{
      printf("Child\n");
      char Buf[16*24];
      printf(": ");
      fgets(Buf, sizeof(Buf),stdin);

      write(TRG,Buf,strlen(Buf)+1);

      close(TRG);

      return 0;
}

int main(int argc, char *argv[])
{

  printf("!!!!!\n");

  int pipes[2];
  pipe(pipes);
  
  int pid = fork();

  if (pid > 0)
    {
      int SRC = pipes[0];
      close(pipes[1]);
      return parent(SRC);
      
    } else if (pid == 0)
    {

      int TRG = pipes[1];
      close(pipes[0]);
      return child(TRG);
    }
  else {
    fprintf(stderr,"ERROR\n");
  }
  
  return 0;

}
