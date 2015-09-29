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

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if(l->elems == 0){
    l->start ++;
    //printf("here\n");fflush(stdout);
  }
  l->end++;
  l->buffer[l->end] = i;
  //printf("%f\n", l->buffer[l->end]);fflush(stdout);
  l->elems++;
  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  int x = 0;
  int check = 0;
  int y;
  while((x < l->elems)&& (check == 0)){
    if(l->buffer[x] == *i){
      y = x;
      
      check = 1;
      while (y < l->elems){
      l->buffer[y] = l->buffer[y+1];
      y++;
      }
l->end--;
 l->elems--;
     }
    x++;
      if(check == 1){
	l->buffer[l->elems] = 0;}
      
 
}
  return 0;
}

