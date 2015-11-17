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
void runEnter(void);
int count;
int noOfEnters;
int main(){
  
 
  
  while(1){
     pid_t pid = NULL;
     int status= NULL;
     int status2 = NULL;
     pid_t pid2 = NULL;
     char* command = (char *) NULL;
    
    char *firstInstruction = NULL;
    char *secondInstruction = NULL;
    command = readline("ishell> ");
    if(strcmp(command, "") == 0){
      noOfEnters++;
      // printf("no -%d\n", noOfEnters);
       if(noOfEnters == 2){
	 noOfEnters = 0;
	    runEnter();
	    //noOfEnters = 0;
	  }
       //exit(1);
    }
    
    
    else{
    //strcat(command, ";");
    tokenizeBySemiColon(command, &firstInstruction, &secondInstruction);
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
	    if(secondInstruction != (char *)NULL){
	    runSecond(secondInstruction);
	    // kill(pid2, SIGKILL);
	    exit(1);
	    }
	    else{
	      //return (0);
	      exit(1);
	    }
	  
	  }
	  }
	  
	
	else{
	  printf("[ishell: program terminated abnormally][return status: %d]\n", status);
	}
	
      }
    else//1st child process
      {
	if(strcmp(firstInstruction, "null") != 0){
	  
	 runFirst(firstInstruction);
	 exit(1);
	}
     
    }
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
  if (strcmp(command, ";") == 0){
    *firstInstruction = "null";
    *secondInstruction = "null";
  }
  else{
  *firstInstruction  = strtok(command, semiColon);
  *secondInstruction = strtok(NULL, semiColon);
  }
  //printf("%s\n", command);
  //printf("%s\n", *firstInstruction);
  //printf("second - %s\n", *secondInstruction);
  
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

void runEnter(void){
  pid_t pid;
  if((pid = fork()) ==  -1){
    perror("fork for enter function error");
  }
  int status;
  if(pid > 0){
    wait(&status);
    kill(pid, SIGKILL);
  }
  else{
    
  execlp("ls", "ls", (char *) NULL);
  }
  //exit(0);
}
