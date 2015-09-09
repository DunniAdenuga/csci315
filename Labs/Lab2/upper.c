#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define BUFFERSIZE 25
#define READEND 0
#define WRITEEND 1

int main(void)
{
char writemsg[BUFFERSIZE] = "Greetings";
char readmsg[BUFFERSIZE];
int pcfd[2];//file desc(read from p to c
 int cpfd[2];//file desc from c to p
pid_t pid;
int i = 0;
int x = 0; 
int closeR = 1;

/* create the pipe
if (pipe(fd) == -1) {
fprintf(stderr,"Pipe failed");
return 1;
}*/

Pipe(pcfd);
Pipe(cpfd);

/* fork a child process
pid = fork();
 if (pid < 0) {  //error occurred 
fprintf(stderr, "Fork Failed");
return 1;
}*/

pid = Fork();

if (pid > 0) 
{
 /* parent process */
/* close the unused end of the pipe */
close(pcfd[READEND]);
/* write to the pipe */
 while(writemsg[i] != NULL)
   {
     Write(pcfd[WRITEEND], writemsg[i], 1);
     //write(fd[WRITEEND],&writemsg[i],1);
     //printf("%c ", writemsg[i]);
   i++;
   }
/* close the write end of the pipe */
close(pcfd[WRITEEND]);
while((Read(cpfd[READEND], &readmsg[x], 1))  !=  0)
   {
  // closeR = read(fd[READEND], &readmsg[x], 1);             
 printf("read %c\n", readmsg[x]);
 x++;
   }
 close(cpfd[READEND]);
}
else 
{
 /* child process */
/* close the unused end of the pipe */
 close(pcfd[WRITEEND]);
/* read from the pipe */
 //printf("I'm here");
 //while((Read(fd[READEND], readmsg[x], 1))  !=  0)
 //closeR = read(fd[READEND], &readmsg[x], 1);
 //printf("read %c\n", readmsg[x]);
 //x++;
  while((Read(pcfd[READEND], &readmsg[x], 1))  !=  0)
   {
  // closeR = read(fd[READEND], &readmsg[x], 1);             
 printf("read %c\n", readmsg[x]);
 x++;
   }
/* close the read end of the pipe */
close(pcfd[READEND]);

/* write to the pipe */
 while(readmsg[i] != NULL)
   {
     Write(cpfd[WRITEEND],toupper(readmsg[i]), 1);
     //write(fd[WRITEEND],&writemsg[i],1);
     //printf("%c ", writemsg[i]);
   i++;
   }
/* close the write end of the pipe */
 close(cpfd[WRITEEND]);

return 0;
 }
}

int Pipe(int pipefd[2])
{
  if(pipe(pipefd) == -1)
    {
      perror("Pipe Failed");
      exit(-1);
    }
  return 1;
}

 int Read(int fd, void *buf, size_t count)
{
  int rid = read(fd, buf, count);
  if(rid  == -1)
    {
      perror("Read Failed");
      exit(-1);
    }
  return rid;
  }

int Write(int fd, const void *buf, size_t count)
{
  int wid = write(fd, &buf, count);
  if( wid  == -1)
    {
      perror("Write Failed");
      exit(-1);
    }
  return wid;
}

int Fork(void)
{
  int pidy = fork();
  if(-1 == pidy)
{
  perror("Error! No child process was created.");
  //printf("errno = %d.\n", errno);
  exit(-1);
}
  return pidy;
}

