#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  char fileName[256];
  unsigned int   offset;
  unsigned int size;
  char buffer[999] ;
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
    
    //fgets(buffer, size+1, file);
    fread(buffer, 1, size, file);
    //printf("buffer %s\n", buffer);
    //printf("file - %s, no - %d, fd -%d\n", buffer, no, fd);
    hexdump((unsigned char*)buffer, (unsigned int)size);
    printf("\n");
    close(fileno(file));
  }
  return 0;
}
