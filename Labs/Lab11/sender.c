#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
 #include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#define MAX 99999

int main(){
  char msg[MAX];
  sem_t* file ;
  strcpy(msg, readline("> sender "));

  file = sem_open("/socaMusic", O_CREAT, S_IRWXU, 1);
  /*if(file == SEM_FAILED){
    printf("issue\n");
    }*/
  sem_wait(file);
  //printf("here\n");
  int fd = open("channel.txt", O_WRONLY);
  // printf("fd - %d\n", fd);
  write(fd, msg, MAX);
  close(fd);
  sem_post(file);
  sem_close(file);
  return 0;
  
}
