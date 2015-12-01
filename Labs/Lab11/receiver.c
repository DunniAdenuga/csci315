#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
 #include <sys/types.h>
#define MAX 99999

int main(){
  char msg[MAX];
  sem_t* file ;
  file = sem_open("/socaMusic", O_CREAT, S_IRWXU, 1);
  while(1){
  

  sem_wait(file);
  int fd = open("channel.txt", O_RDONLY);
  read(fd, msg, sizeof(msg));
  printf("receiver [msg arrival]: %s\n", msg);
  close(fd);
  sem_post(file);
  }
  sem_close(file);
  return 0;
}
