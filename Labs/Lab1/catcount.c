#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

extern char **environ;
int main(int argc, char*argv[])
{
  char *fileLine;
  fileLine = argv[1];
  printf("%s",fileLine);
  pid_t pid;
  pid_t pid2;
  int status;
  int stuff;

  print_environment();
  pid = fork();
  if (pid == 0)//child process
{
  printf("I'm here.");
  stuff =  execlp("/bin/cat","cat", fileLine, NULL);
}
  else if(stuff != -1)
{
  waitpid(pid, &status, 0);
  pid2 = fork();//another child
  waitpid(pid2, &status, 0);
  if (pid2 == 0)
{
  printf("child2 doing it's thing");
  stuff = execlp("/usr/bin/wc","/usr/bin/wc", fileLine, NULL);
}
  if (stuff != -1){
    printf("parent about to terminate.");
    exit(0);}
}    
}

void print_environment(void)
{
  // extern char **environ;
  int i = 0;
  while (environ[i] != NULL)
{
  printf("%s\n", environ[i]);
  i++;
}
  //exit(0);
}
  
  
