
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 1000000

pthread_mutex_t chopsticks[5];
void * Philosopher(void * param);
void napping(int t);


void napping(int t){
  unsigned int seedp = (unsigned int)pthread_self() + 1;

  int n = rand_r(&seedp)%t;
  usleep(n*NUM);
}


void* Philosopher(void* arg){
 while(1){
  long long id = (long long)arg;
  printf("Philosopher ID -%lli is thinking.\n", id);
  napping(2);
  printf("Philosopher ID -%lli is hungry.\n", id);
  if(id < ((id+1)%5)){
  pthread_mutex_lock(&chopsticks[(int)id]);
  printf("Philosopher ID -%lli picking up chopstick %d\n", id, (int)id );
  napping(25);
  pthread_mutex_lock(&chopsticks[(int)(id+1)%5]);
  printf("Philosopher ID -%lli picking up chopstick %d\n", id, (int)(id+1)%5 );
  }
  else{
     pthread_mutex_lock(&chopsticks[(int)(id+1)%5]);
  printf("Philosopher ID -%lli picking up chopstick %d\n", id, (int)(id+1)%5 );
  napping(25);
  pthread_mutex_lock(&chopsticks[(int)id]);
  printf("Philosopher ID -%lli picking up chopstick %d\n", id, (int)id );
  }
  printf("Philosopher ID -%lli is starting to eat.\n", id); 
  printf("Philosopher ID -%lli is done eating.\n", id);

  pthread_mutex_unlock(&chopsticks[(int)id]);
  printf("Philosopher ID -%lli putting down chopstick %d\n", id, (int)id );
  napping(25);
  pthread_mutex_unlock(&chopsticks[(int)(id+1)%5]);
   printf("Philosopher ID -%lli putting down chopstick %d\n", id, (int)(id+1)%5 );
  }
}

int main(){
  pthread_t pid[5];
  long long num;
  for(int i = 0; i< 5; i++){
    pthread_mutex_init(&chopsticks[i], NULL);
		       }
  for(int i = 0; i< 5; i++){
     num = (long long)i;
    pthread_create(&pid[i], NULL, Philosopher,(void*)num);
}
sleep(30);
  return(1);
}
