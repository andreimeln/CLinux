#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

  //int fd = open("data.txt", O_WRONLY);
  int fd = open("data.txt", O_RDONLY);

  struct flock fi;
  //fi.l_type = F_WRLCK;
  fi.l_type = F_RDLCK;
  fi.l_whence = SEEK_SET;
  fi.l_start = 16;
  fi.l_len = 8;

  
  int R = fcntl(fd, F_SETLK, &fi);
  //int R = fcntl(fd, F_SETLK, &fi); // getlock
  if (R)
    {
      fprintf(stderr, "Already locked\n");
      return 1;
    }
  
  
  //lseek (fd, 16, SEEK_SET);
  //write(fd, "00000000", 8);

  //getch(); //bad style
  fgetc(stdin);

  fi.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &fi);

  close(fd);
  
  return 0;
}
