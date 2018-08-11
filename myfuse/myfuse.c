#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/*
#define TXT "This is an example\n"
#define SH "#!/bin/bash\n\necho Hello!!!\n"
*/
char *TXT = "This is an example\n";
char *SH = "#!/bin/bash\n\necho Hello!!!\n";

int my_getattr(const char *path, struct stat *stbuf)
{
  int Result = 0;
  memset(stbuf, 0, sizeof(struct stat));

  /*
  FILE *LOG = fopen("/home/andrei/WORK/myfuse/log.log","at");
  fprintf(LOG, "[%s]\n", path);
  fclose(LOG);
  */
  if (strcmp(path, "/") == 0)
    {
      stbuf->st_mode = S_IFDIR | 0755;
      stbuf->st_nlink = 2;
      stbuf->st_uid = getuid();
      stbuf->st_gid = getgid();
      
    } else if (strcmp(path,"/example.txt"))
    {
      /*
      FILE *LOG = fopen("/home/andrei/WORK/myfuse/log.log","at");
      fprintf(LOG, ">>>[%s]\n", path);
      fclose(LOG);
      */
      
      stbuf->st_mode = S_IFREG | 0644;
      stbuf->st_nlink = 1;
      stbuf->st_uid = getuid();
      stbuf->st_gid = getgid();
      stbuf->st_size = strlen(TXT);

    } else if (strcmp(path,"/example.sh"))
    {
      stbuf->st_mode = S_IFREG | 0755;
      stbuf->st_nlink = 1;
      stbuf->st_uid = getuid();
      stbuf->st_gid = getgid();
      stbuf->st_size = strlen(SH);

    } else
      {
	Result = -ENOENT;
      }

  return Result;
}

/*******************************************************/

int my_readdir(const char *path, void *buf,
	       fuse_fill_dir_t filler,
	       off_t offset, struct fuse_file_info fi)
{

  int Result = 0;

  if (strcmp(path,"/" == 0))
    {

      filler(buf, ".", NULL, 0);
      filler(buf, "..", NULL, 0);
      filler(buf, "example.txt", NULL, 0);
      filler(buf, "example.sh", NULL, 0);

    } else {

      Result = -ENOENT; // doesn't exist
    }

    return Result;

}

/*******************************************************/

int my_open(const char *path, struct fuse_file_info *fi)
{

  int Result = 0;

  if (strcmp(path,"/example.txt") == 0)
    {

      if ((fi->flags & 3) != O_RDONLY) // 3 - access mask
	Result = -EACCES;
      
    } else if (strcmp(path,"/example.sh") == 0)
    {
    
      if ((fi->flags & 3) != O_RDONLY) // 3 - access mask
	Result = -EACCES;
    } else
    {

      Result = -ENOENT;
    }

  return Result;
}


/*******************************************************/

int my_read(const char *path, char *buf, size_t size, off_t offset,
	    struct fuse_file_info *fi)
{

  int Result = 0;

  if (strcmp(path, "/example.txt") == 0)
    {
      int N = strlen(TXT);
      if (offset < N)
	{
	  if (offset + size > N)
	    size = N - offset;
	  
	  memcpy(buf, TXT+offset, size);
	  Result = size;
	}
    } else if (strcmp(path,"/example.sh") == 0) {

    int N = strlen(SH);
    if (offset < N)
      {
	if (offset + size > N)
	  size = N - offset;
	  
	memcpy(buf, TXT+offset, size);
	Result = size;

      }
  } else {

    Result = -ENOENT;
  }
    
    return Result;
}

/*******************************************************/

struct fuse_operations oper;

int main(int argc, char *argv[])
{
  // Initializing oper struct
  memset(&oper, 0, sizeof(oper));
  oper.getattr = my_getattr;
  oper.readdir = my_readdir;
  oper.open = my_open;
  oper.read = my_read;

  return fuse_main(argc,argv,&oper,NULL);
}
