/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include<pthread.h>

#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX
 *
 *  where RAND_MAX is the largest random numver returned
 *  by rand_r. If the numerator is smaller than RAND_MAX,
 *  the quotient of the integer division is ZERO!
 */
#define SCALE_FACTOR 9567

// global variables -----------------------

struct circular_list mylist;
pthread_mutex_t lock;
// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = 1234;
  int id = (int)param;
  seed =  seed * (id+7);
  // while (true) {
    // sleep for random period of time
  int sleeptime;
  sleeptime = (SCALE_FACTOR * rand_r(&seed)) / (RAND_MAX/1000);
  if (sleeptime< 0){
    sleeptime = sleeptime * -1;}
    printf("sleep-time-prod: %d\n", sleeptime);
    usleep(sleeptime); 
    
    // generate a random number
    i = (item) (((double) rand_r(&seed))*(id +2 ) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
    // }
    pthread_exit(0);
}

void *consumer (void *param) {
  item i;
  int id = (int)param;
  unsigned int seed = 999;
  seed = seed*(id+5);
  //while (true) {
  int sleeptime  = (rand_r(&seed))*SCALE_FACTOR;
   if (sleeptime< 0){
    sleeptime = sleeptime * -1;}
  sleeptime =  sleeptime / (RAND_MAX/1000);
  if (sleeptime< 0){
    sleeptime = sleeptime * -1;}
  printf("sleeptime-cons is: %d\n", sleeptime);
   usleep(sleeptime);
   
   //pthread_mutex_lock(&lock);
    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER : consumed value %lf\n",  i);
    }
    //pthread_mutex_unlock(&lock);
    //}
    pthread_exit(0);
}

int main (int argc, char *argv[]) {
  int num_prod;
  int num_cons;
  int sleep_time;
  pthread_mutex_init(&lock, NULL);
  
  // if error in command line argument usage, terminate with helpful
  if(argc != 4){
    printf("prodcons [num_prod] [num_cons] [sleep_time]\n [num_prod] is the number of producer threads\n [num_cons] is the number of consumer threads \n [sleep_time] is the number of seconds to sleep before the process terminates\n");
    exit(-1);
  }
  
// get command line arguments
  num_prod = atoi(argv[1]);
  num_cons = atoi(argv[2]);
  sleep_time = atoi(argv[3]);
  // message
  pthread_t prod[num_prod];
  pthread_t cons[num_cons];
  // initialize buffer
  circular_list_create(&mylist, 20);
  
  // create producer thread(s)
  for(int i = 0; i < num_prod; i++){
    pthread_create(&prod[i], NULL, producer, (void*)i);
  }
  
  // create consumer thread(s)
   for(int i = 0; i < num_cons; i++){
     pthread_create(&cons[i], NULL, consumer, (void*)i );
  }
  // sleep to give time for threads to run
   usleep(sleep_time);
 

  //join producer threads
  for(int i = 0; i<  num_prod; i++){
    pthread_join(prod[i], NULL);
  }
  //join consumer threads
 for(int i = 0; i < num_cons; i++){
   pthread_join(cons[i], NULL);
  }

 
  return 0;
}
 
