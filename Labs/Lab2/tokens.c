#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFFERSIZE 500
#define READEND 0
#define WRITEEND 1

int main()
{
  const char space[2] = " ";
  char readmsg[BUFFERSIZE];
  int pcfd[2];//file desc(read from p to c
  int cpfd[2];//file desc from c to p
  pid_t pid;
  int i = 0;
  int x = 0; 
  char *token;
  char writemsg[BUFFERSIZE];


  /* create the pipe*/

  Pipe(pcfd);
  Pipe(cpfd);

  /* fork a child process*/

  pid = Fork();

  if (pid > 0) 
    {
      while(1){
	printf("Please enter your string:\n");
	fgets(writemsg, BUFFERSIZE, stdin);

	/* parent process */
	/* close the unused end of the pipe */
	close(pcfd[READEND]);

	/* write to the pipe */
	int size;
    
	size = strlen(writemsg) + 1;
    
	Write(pcfd[WRITEEND], (void*) &size, 4);
	Write(pcfd[WRITEEND],  writemsg,  size);
    
	Read(cpfd[READEND], &size, 4);
	Read(cpfd[READEND], readmsg, size);            
	printf("%s\n", readmsg); fflush(stdout);
      }

      close(cpfd[READEND]);
      /* close the write end of the pipe */
      close(pcfd[WRITEEND]);
    }
  else 
    {
      while(1)
	{
      /* child process */
      /* close the unused end of the pipe */
      close(pcfd[WRITEEND]);
      
      int size;
      Read(pcfd[READEND], &size, 4);
      Read(pcfd[READEND], readmsg, size);            
      //printf("read1 %s\n", readmsg); fflush(stdout);


      token = strtok(readmsg, space);
      //printf("%s", token); fflush(stdout);
      strcpy(writemsg, token);
      token = strtok(NULL, space);

      while(token != NULL)
	{
	  strcat(writemsg, space);
	  strcat(writemsg, token);
	  token = strtok(NULL, space);
	  //printf("%s", token);
	
	}
      
      //printf("%s", writemsg);fflush(stdout);
      /* write to the pipe */
      size = strlen(writemsg) + 1;
      Write(cpfd[WRITEEND],(void*)&size, 4);
      Write(cpfd[WRITEEND], writemsg,size);
      
	}
      /* close the read end of the pipe */
       close(pcfd[READEND]);
      /* close the write end of the pipe */
      close(cpfd[WRITEEND]);

      //return 0;
    

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
  int wid = write(fd, buf, count);
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

