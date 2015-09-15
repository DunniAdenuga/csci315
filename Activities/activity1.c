
/**   Receives a integer number N as a command line parameter.
    Contains a function called summation that receives two integer arguments i and j, calculates the sum of the integers from i to j-1 and returns the result to the caller.
    In your main program, use your summation function to create two threads to compute the summation of integers: from 1 to (N/2 – 1) and from (N/2 -1) to N. Of course, N is the number you received through the command line. •
    When each thread terminates, it passes the result of its computation back to the main function, which adds the two results and prints it out to the standard terminal.**/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

int main(int argc, char *argv[])
{
  int N = atoi(argv[1]);

  int resultz;

  resultz = summation(1, N);
  printf("The result is: %d\n", resultz); 
}

 struct threadData{
    int u;
    int v;
    int result;
  };

void *sum(void *argh)
{
  int x;
  int y;
  int results = 0;

  // printf("entered thread creating threads\n");

  struct threadData *mydata;
  mydata = (struct threadData *)argh;
  x = mydata->u;
  //printf("%d\n", x);
  y = mydata->v;
  //printf("%d\n", y);
  //results = mydata.result;
  
  while(x <= y)
    {
      results = results + x;
      x++;
    }
  mydata->result = results;
  //pthread_exit(NULL);
  return argh;
}


int summation(int i, int j)
{
 
  pthread_t threadid[2];
  
  struct threadData thread1;
  thread1.u = i;
  thread1.v = j/2;
  //thread.result = 0;

  struct threadData thread2;
  thread2.u = j/2 + 1;
  thread2.v = j;
 

  pthread_create(&threadid[0], NULL, sum, (void*)&thread1);
  pthread_create(&threadid[1], NULL, sum, (void*)&thread2);

 

  pthread_join(threadid[0], NULL);
  pthread_join(threadid[1], NULL);



  //printf("thread1.result %d\n", thread1.result);
  //printf("thread2.result %d\n", thread2.result);
  int x = thread1.result + thread2.result;
  return x;
}

