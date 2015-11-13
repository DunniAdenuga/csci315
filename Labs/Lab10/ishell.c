#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 0
extern char **environ;

char* command;
int count;
char* tokenizer(void);
int main(){
  
  pid_t pid;
  int status;
  char *argvs[50];
  while(1){
    //printf("ishell> ");
    command = readline("ishell> ");

    if((pid = fork()) == -1){
      return (0);
    }
    if(pid > 0)//parent process
      {
	wait(&status);
	if(WIFEXITED(&status) == TRUE){
	  printf("[ishell: program terminated successfully]\n");
  }
	else{
	  printf("[ishell: program terminated abnormally][return status: %d]\n", status);
	}
      }
    else//child process
      {
	count = 0;
	//char *token1 = tokenizer();
	char *file = tokenizer();
	int i = 1;
	
	char *token = tokenizer();
	while( token != NULL){
	  argvs[i] = token;
	  i++;
	  token = tokenizer();
	}
	argvs[i] = NULL;
	execvp(file, argvs);
    }
}
  return 0;
}




char *tokenizer(void){
  
  const char space[2] = " ";
  char *token;
  if (count == 0){
  token = strtok(command, space);
  count++;
  }
  else{
  token = strtok(NULL, space);
  }
  return token;
  }
