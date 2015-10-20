#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 256

void * Philosopher(void * param);
void napping(int t);

void napping(int t){
  unsigned int seedp = 10;
  int n = rand_r(&seedp)%t;
  sleep(n);
}
void* Philosopher(void* param){
  long long id = (long long)param;
  printf("Philosopher ID -%lli is thinking.\n", id);
  napping(2);
  printf("Philosopher ID -%lli is hungry.\n", id);
  printf("Philosopher ID -%lli is starting to eat.\n", id);
  napping(1);
  printf("Philosopher ID -%lli is done eating.\n", id);
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
