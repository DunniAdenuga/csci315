/**
 *John Simmons
 *Ari Faust
 *Dunni Adenuga
 **/
/*
New Features:
-Cat(used as readout)- read a file:preferably files in current directory and print contents to stdout
name: readout
if more than one file it concatenates all files sent to it and prints to stdout
To use, enter: readout fileName1 fileName2
- exit
exits shell
: works indidually
- ^
does previous instruction
: works individually
 */
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
int runCat(char* instruction, char* argvs[]);
void runEnter(void);
int runIO(char* string1, char* string2);
int count;
int noOfEnters;
int main(){
  
  char *prev_command = "";
  
  while(1){
     pid_t pid ;
     int status;
     int status2;
     pid_t pid2;
     char* command = (char *) NULL;
     char*  stringValue = (char *) NULL;
     char*  stringValue1 = (char *) NULL;
     char* stringValue2 = (char *) NULL;
     char *firstInstruction = NULL;
     char *secondInstruction = NULL;

     command = readline("gshell> ");
      stringValue = strstr(command, "|");
     if(stringValue != NULL){
       stringValue1 = strtok(command, "|");
       stringValue2 = strtok(NULL, "|");
       //printf("io\n");
       runIO(stringValue1, stringValue2);
       //exit(1);
       }

     if(strcmp(command, "^") == 0){
       if(strcmp(prev_command, "") != 0){
	 //reset command to the previous command
	 command = prev_command;
	 //signal the user previous command is being executed
	 printf("Executing: %s\n", command);
     }else{
       //set previous command
       prev_command = command;
       }
     }else{
       //set previous command
       prev_command = command;
     }

     if(strcmp(command, "") == 0){
       noOfEnters++;
       // printf("no -%d\n", noOfEnters);
       if(noOfEnters == 2){
	 noOfEnters = 0;
	 runEnter();
	 //noOfEnters = 0;
       }
       //exit(1);
     }else if(strcmp(command, "exit")==0){
       printf("Exiting gshell\n");
       exit(0);
     }/**else if(strcmp((stringValue = strtok(command, "|")), NULL ) != 0){
       stringValue2 = strtok(NULL, "|");
       printf("io\n");
       runIO(stringValue, stringValue2);
       }**/
    
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
	       printf("[gshell: program terminated successfully]\n");
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
	     printf("[gshell: program terminated abnormally][return status: %d]\n", status);
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
  if(strcmp(file, "readout") != 0){
    execvp(file, argvs);
  }
  else{
    runCat(file, argvs);
  }
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
  if(strcmp(file, "readout") != 0){
    execvp(file, argvs);
  }
  else{
    runCat(file, argvs);
  }
  
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

/*
  Bash's cat,- read a file and print contents to stdout
  name - readout
*/
int runCat(char* instruction, char* argvs[]){
  FILE* file;
  int i = 1;
  //int fd;
  int c;
  char* buffer;
  if(strcmp(instruction, "readout") == 0){
    while(argvs[i] != NULL){
      file = fopen(argvs[i], "r");
      while ((c = getc(file)) != EOF)
        putchar(c);
      fclose(file);
      i++;
    }    
  } 
  return 0;
}
	     
	    



int runIO(char* string1, char* string2){
  //printf("string1 - %s\n", string1);
  //printf("string2 - %s\n", string2);
int status;
 int status2;
  //int pcfd[2];//file desc(read from p to c
int cpfd[2];//file desc from c to p
int pid;
 int pid2;

//pipe(pcfd);
 pipe(cpfd);
 
 pid  = fork();
 if(pid > 0){
   wait(&status);
   pid2 = fork();
   if(pid2 > 0)//parent
     {
       kill(pid, SIGKILL);
       wait(&status2);
       printf("here5- ");
       //kill(pid2, SIGKILL);
     }
   else{//second child
     char *argvs[50];
  //char *token1 = tokenizer();
  char *file = tokenizer(string2);
  //printf("here %s\n", file);
  int i = 1;
  
  char *token = tokenizer(string2);
  while( token != NULL){
    argvs[i] = token;
    //printf("%s\n", argvs[i]);
    i++;
    token = tokenizer(string2);
  }
  argvs[i] = NULL;
  
  close(cpfd[1]);
  
  dup2(cpfd[0], 0); 
  close(cpfd[0]);
  //printf("k - %s", file);
   execvp(file, argvs);
   //return 1;
   }
 }
 else{//1st child 

//child process
  char *argvs[50];
  count = 0;
  //char *token1 = tokenizer();
  char *file = tokenizer(string1);
  // printf("argvs 0: %s\n", file);
  int i = 1;
  
  char *token = tokenizer(string1);
  while( token != NULL){
    argvs[i] = token;
    //printf("%s\n", argvs[i]);
    i++;
    token = tokenizer(string1);
  }
  argvs[i] = NULL;
  //int x = 1;
   
  close(cpfd[0]);//close reading
  dup2(cpfd[1], 1); 
  close(cpfd[1]);
   printf("k - %s\n", file);
  execvp(file, argvs);
  
  //return 1;
 }
 
 
 //return 0;
}
