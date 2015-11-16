#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
extern char **environ;


char* tokenizer(char* instruction);
void tokenizeBySemiColon(char* command, char** firstInstruction, char** secondInstruction);
int runFirst(char* firstInstruction);
void runSecond(char* secondInstruction);
int count;
int main(){
  
 
  
  while(1){
     pid_t pid = NULL;
     int status= NULL;
     int status2 = NULL;
     pid_t pid2 = NULL;
     char* command = NULL;
    
    char *firstInstruction = NULL;
    char *secondInstruction = NULL;
    command = readline("ishell> ");
    strcat(command, ";");
    tokenizeBySemiColon(command, &firstInstruction, &secondInstruction);
    // printf("%s\n", firstInstruction);
    //printf("%s\n", secondInstruction);
    if((pid = fork()) == -1){
      perror("Perror fork!");
    }
    if(pid > 0)//parent process
      {
	wait(&status);
	if(WIFEXITED(status) == true){
	  if((pid2 = fork()) == -1){
      perror("Perror fork!");
	  }
	  if(pid2 > 0){//still parent
	  printf("[ishell: program terminated successfully]\n");
	  kill(pid , SIGKILL);
	  wait(&status2);
	  }
	  else{
	    if(secondInstruction != NULL){
	    runSecond(secondInstruction);
	    // kill(pid2, SIGKILL);
	    return(0);
	    }
	    else{
	      return(0);
	    }
	  }
	}
	else{
	  printf("[ishell: program terminated abnormally][return status: %d]\n", status);
	}
      }
    else//1st child process
      {
	 runFirst(firstInstruction);
	 exit(1);
    }
    
}
  return 0;
}




char *tokenizer(char* instruction){
  
  const char space[2] = " ";
  char *token;
 
  if (count == 0){
  token = strtok(instruction, space);
  count++;
  }
  else{
  token = strtok(NULL, space);
  }
  return token;
  }

void tokenizeBySemiColon(char* command, char** firstInstruction, char** secondInstruction){

  const char *semiColon = ";";
  *firstInstruction  = strtok(command, semiColon);
  *secondInstruction = strtok(NULL, semiColon);
  // printf("second - %s\n", *secondInstruction);
  
}

int runFirst(char* firstInstruction){
 char *argvs[50];
	count = 0;
	//char *token1 = tokenizer();
	char *file = tokenizer(firstInstruction);
	//printf("here %s\n", file);
	int i = 1;
	
	char *token = tokenizer(firstInstruction);
	while( token != NULL){
	  argvs[i] = token;
	  //printf("%s\n", argvs[i]);
	  i++;
	  token = tokenizer(firstInstruction);
	}
	argvs[i] = NULL;
	execvp(file, argvs);
	return 0;
	
}
void runSecond(char* secondInstruction){
  char *argvs[50];
	count = 0;
	//char *token1 = tokenizer();
	char *file = tokenizer(secondInstruction);
	//printf("%s\n", file);
	int i = 1;
	
	char *token = tokenizer(secondInstruction);
	while( token != NULL){
	  argvs[i] = token;
	  i++;
	  token = tokenizer(secondInstruction);
	}
	argvs[i] = NULL;
	execvp(file, argvs);
	
	}
