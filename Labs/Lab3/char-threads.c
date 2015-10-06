/**
Print one character; the character to print depends on which thread it is:
Thread 1 prints a digit followed by a newline character. In each iteration of the loop, the thread should print a digit in [0:9], starting with 0, then 1, 2, 3,  …, and 9, repeating the sequence all over again.
Thread 2 prints a letters followed by a newline character. The thread should cycle through the lowercase letters of the alphabet a to z, and cycle back to ‘a‘, repeating the sequence all over again.
Thread 3 prints always the same character ‘#‘ followed by a newline character.
After printing the one character, the thread computes the sum of all integers from 1 to 10,000. Do nothing with the result; we just want to the thread to spend some time doing CPU-bound work.
 **/
#include <pthread.h>
//#define NUM_THREADS 3

void *digits(void *stuff)
{
  int m = (int)stuff;
  printf("I'm in thread: %d\n", m);
  while(1)
{
    int i = 0;
    while(i < 10)
      {
	printf("%d\n", i);
	i++;
      }
}
}

void *letters(void *stuff)
{
  int m = (int)stuff;
  printf("I'm in thread: %d\n", m);
  char alpha[26] = {'a', 'b', 'c', 'd','e', 'f', 'g', 'h', 'i', 'j','k','l','m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  while(1)
     {
  int i = 0;
  while(i < 26)
    {
  printf("%c\n", alpha[i]);
  i++;
    }
    }
}

void *hash(void *stuff)
{
  int m = (int)stuff;
  printf("I'm in thread: %d\n", m);
  while(1)
    {
      printf("#\n");
      int i = 1;
      int result = 0;
      while(i <= 10000)
	{
	  result = result + i;
        }
    }
}

int main(){
  pthread_t threadid[3];
  int x = 1;
  int y = 2;
  int z = 3;
  
  pthread_create(&threadid[0], NULL, digits, (void*) x);
  pthread_create(&threadid[1], NULL, letters, (void*) y);
  pthread_create(&threadid[2], NULL, hash, (void*) z);

  pthread_join(threadid[0], NULL);
  pthread_join(threadid[1], NULL);
  pthread_join(threadid[2], NULL);
  

}

 
