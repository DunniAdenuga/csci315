#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
char* string;
int status;
 pid_t pid;

string = (char*)malloc(20);
strcpy(string, "I'm new to C...");

pid = fork();
if (pid == 0)
  {
    printf("String is: %s  Address is %u\n", string, string);
    strcpy(string, "I'm new to C bla bla...");
    printf("String is: %s Address is %u\n", string, string);
  }
 else
   {
     pid = fork();
     if (pid == 0)
       {
	 printf("String is: %s Address is %u\n", string, string);
	 
	 printf("String is: %s Address is %u\n", string, string);
       }
     wait(&status);
     exit(0);
   }
}
