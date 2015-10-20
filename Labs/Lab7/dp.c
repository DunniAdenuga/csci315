#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 1000000

void * Philosopher(void * param);
void napping(int t);

void napping(int t){
  unsigned int seedp = (unsigned int)pthread_self() + 1;

  int n = rand_r(&seedp)%t;
  usleep(n*1000000);
}
void* Philosopher(void* param){
  while(1){
  long long id = (long long)param;
  printf("Philosopher ID -%lli is thinking.\n", id);
  napping(2);
  printf("Philosopher ID -%lli is hungry.\n", id);
  printf("Philosopher ID -%lli is starting to eat.\n", id);
  napping(1);
  printf("Philosopher ID -%lli is done eating.\n", id);
  }
}

int main(){
  pthread_t pid[5];
  long long num;
  for(int i = 0; i<5; i++){
    num = (long long)i;
    pthread_create(&pid[i],NULL,Philosopher, (void *)num);
  }
  sleep(30);
  return(1);
}
