/*
 * CSCI 315 Operating Systems Design
 * Date: 2014-09-02
 * Copyright (c) 2014 Bucknell University
 *
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int i = 7;
double x = 3.14;

int main(int argc, char* argv[]) {

  int pid;
  int j = 6;
  double y = 2.18;

  char buf_parent[10];
  char buf_child[6]; 
  int status; // exit status to be filled by wait
  int fileDesc;//file descriptor from open

  // create and open a file called data.txt
  // use open (file descriptors)
  fileDesc = open("data.txt", O_RDWR);
  // write into data.txt the following string:
  // "this is a test for processes created with fork\nthis is another line"
  write(fileDesc, "this is a test for processes created with fork\nthis is another line",100);
  close(fileDesc);

  //Fork();
  pid = Fork();
  if (pid == 0) 
    {
    // child process
    
    // read 5 characters from file into buf_child
    fileDesc = open("data.txt", O_RDWR);
    read(fileDesc,buf_child, 5);
    int i = 0;
    // print the characters in buf_child to terminal
    while(i< 5)
      {
       	printf("%c ", buf_child[i]);
	i++;
      }
     // close the file
      close(fileDesc);

    // printf("pid= %d -- initially, child sees x= %lf, y=%lf\n", pid, x, y);
    x = 0;
    y = 0;
    
  } 
  else 
    {

    // parent process

    // read 5 characters from file into buf_parent
    fileDesc = open("data.txt", O_RDWR);
    read(fileDesc,buf_parent, 5);
    
    // print the characters in buf_parent to terminal
    int m = 0;
    while( m< 5)
      {
	printf("%c", buf_parent[m]);
	//printf("I did this");
	m++;
      }

    

    wait(&status); // note we are not catching the return value of wait!
   
      
    // read another 5 characters from file into buf_parent
    // fileDesc = open("data.txt", O_RDWR);
    read(fileDesc,buf_parent, 5);
    // print the characters in buf_parent to terminal
    int n = 0;
     while( n< 5)
     {
       //printf("I'm gonna do this");
       printf("%c\n ", buf_parent[n]);//this doesn't seem to be working
       n++;
       
      }
    // close the file
      close(fileDesc);
    //printf("parent is terminating\n");
    exit(0);
  }

}
int Fork(void)
{
  int pid;
  pid = fork();
  if(pid == -1)
{
  perror("Error! No child process was created.");
  //printf("errno = %d.\n", errno);
  exit(-1);
}
  return pid;
  }
