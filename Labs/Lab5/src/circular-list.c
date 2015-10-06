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
#include "circular-list.h" 
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t full ;
pthread_mutex_t lock;

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  sem_init(&empty, 0, size);
  sem_init(&full, 0, 0);
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  pthread_mutex_init(&lock, NULL);
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  sem_wait(&empty);
  pthread_mutex_lock(&lock);
  if(l->elems == 0){
    l->start ++;
  }
  l->end++;
  l->buffer[l->end] = i;
  l->elems++;
  pthread_mutex_unlock(&lock);
  sem_post(&full);
  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  
 
  sem_wait(&full);
  pthread_mutex_lock(&lock);
   
   //printf("lstart %d ", l->start);
  *i = (l->buffer[l->start]);
  //printf("*i %f", *i);
  int y = 0;
   while ((y+1) < l->elems){  //shift everything to left
      l->buffer[y] = l->buffer[y+1];
      y++;
      }
  //l->buffer[l->elems] = 0;
   //l->start++;
l->elems--;
 pthread_mutex_unlock(&lock);
 sem_post(&empty);
  return 0;
  }

/**int circular_list_remove(struct circular_list *l, item *i){
  int x =0;
  i  = calloc(l->elems, sizeof(item));
  while(x < l->elems){
    i[l->start] = l->buffer[x];
    printf("%f\n", i[l->start]);
    l->start++;
    l->buffer[x] = 0;
    x++;
    l->elems--;
    }}**/
