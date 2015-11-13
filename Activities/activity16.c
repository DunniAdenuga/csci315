#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char*argv[]){
  char* fileName;
  struct statvfs buf;
  struct stat buf2;
  int fd;
  if(argc != 2){
    printf("Error\n");
    return 0;
  }
  strcpy(fileName, argv[1]);
  fd = open(fileName, O_RDWR);
  fstatvfs(fd, &buf);
  fstat(fd, &buf2);
  printf("Block size: %lu\n", buf.f_bsize);
  printf("Maximum filename length size: %lu\n", buf.f_namemax);
  printf("Protection Mode: %d\n", buf2.st_mode);
  printf("Creation Time not provided\n");
  char stringR[200];
  strftime(stringR, sizeof(stringR), "%d.%m.%Y %H:%M:%S", localtime(&(buf2.st_atime)));
  printf("Last access time: %s\n", stringR);
  char stringR2[200];
  strftime(stringR2, sizeof(stringR2), "%d.%m.%Y %H:%M:%S", localtime(&(buf2.st_mtime)));
  printf("Last modified time: %s\n", stringR2);
char stringR3[200];
  strftime(stringR3, sizeof(stringR3), "%d.%m.%Y %H:%M:%S", localtime(&(buf2.st_ctime)));
  printf("Last status change: %s\n", stringR3);
 printf("ID of device containing file: %d\n", buf2.st_dev);
   close(fd);
   return 0;
}
