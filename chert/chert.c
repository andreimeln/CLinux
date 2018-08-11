#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

/* gcc -D_REENTRANT -o chert chert.c */

void mylog(char *szText)
{
  int fd = open("my.log",O_WRONLY | O_APPEND | O_CREAT, 0644);
  char Buf[16*1024];
  sprintf(Buf, "%5d -- %s\n", getpid(), szText);
  write(fd, Buf, strlen(Buf));
  close(fd);

}

void term_handler(int sigid)
{
  mylog("Terminating");
  unlink("/var/lock/chert-lock");
  //exit(0);
  _exit(0);
}

void child_handler(int sigid)
{
  wait();
}

int main(int argc, char *argv[])
{

  mylog("Daemon is ready to start");

  int fd = open("/var/lock/chert-lock", O_WRONLY, 0600);
  if (fd >= 0)
    {
      mylog("Already started, terminating\n");
      return 1;
    }

  if (argc > 1) {
    if (strcmp(argv[1], "-d"))
      {

	// Daemon started:
	pid_t pid = fork(); // typedef int pid_t
	if (pid)
	  {
	    mylog("I am starter, daemon started");
	    return 0;
	  }
      }
  }

  fd = open("/var/lock/chert-lock", O_WRONLY | O_CREAT | O_TRUNC, 0600);
  //int fd = open("/var/lock/chert-lock", O_WRONLY | O_CREAT | O_TRUNC, 0600);
  char szBuf[16*1024];
  sprintf(szBuf, "%d", getpid());
  write(fd,szBuf, strlen(szBuf));
  close(fd);
  
  struct sigaction sa;
  sa.sa_handler = term_handler;
  sigaction(SIGTERM, &sa, 0);

  int sock = socket(AF_INET, SOCK_STREAM, 0); // AF_INET - ip4
  if (sock < 0)
    {
      mylog("Cannot create socket, exiting");
      return 1;
    }

  struct sockaddr_in sadr;
  sadr.sin_family = AF_INET;
  sadr.sin_addr.s_addr = INADDR_ANY; // not recommended, better ip address; listening address;; sin_addr - union
  sadr.sin_port = htons(5431);
  if (bind(sock, (struct sockaddr*)&sadr, sizeof(sadr)) < 0)
    {
      mylog("Cannot bind socket");
      return 2;
    }
  
  for (;;) {
    mylog("I am daemon, I am running");
    //sleep(2);

    //listen(sock, 10);

    int R = listen(sock);
    if (R)
      {
	switch(errno)
	  {
	  case EADDRINUSE : 	mylog("Address in use")		; break;
	  case EBADF   	  : 	mylog("Invalid descriptor")	; break;
	  case ENOTSOCK   :	mylog("Not a socket")		; break;
	  case EOPNOTSUPP : 	mylog("Operation not supported") ; break;
	  default: mylog("Error listening"); break;
	  }
	sleep(2);
	continue;
      }

    int pid = fork();
    if (!pid)
      break;

    struct sockaddr_in client;
    int clen = sizeof(client); // client data length
    int newsock = accept(sock,(struct sockaddr*)&client, &clen); // returns dupl of descr of our socket
    if(newsock < 0) {
      mylog("Error accepting");
      return 3;
    }

    char Buf[16*1024];
    read(newsock, Buf, sizeof(Buf));
    mylog(Buf);
    write(newsock, "OK", 2);
    close(newsock);
  }

  return 0;

}
