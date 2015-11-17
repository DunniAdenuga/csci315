#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  char fileName[256];
  unsigned int   offset;
  unsigned int size;
  char* buffer;
  FILE *file;
  if(argc != 4){
    printf("Usage: fdump [fileName: char[]] [offset: int] [size: int]\n");
    return 0;
  }
  else{
    strcpy(fileName, argv[1]);
    offset = atoi(argv[2]);
    size = atoi(argv[3]);
    file = fopen(fileName, "r");
    fseek(file, (long)offset, SEEK_SET);
    //int fd;
    //int no = read(fd = fileno(file), (void *)buffer, size);
    //printf("file - %s, no - %d, fd -%d\n", buffer, no, fd);
    
    fgets(buffer, size+1, file);
    printf("buffer %s\n", buffer);
    //printf("file - %s, no - %d, fd -%d\n", buffer, no, fd);
    hexdump(buffer, strlen(buffer));
    printf("\n");
    close(fileno(file));
  }
  return 0;
}
