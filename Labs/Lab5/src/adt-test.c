#include "circular-list.h" 
#include <stdlib.h>
#include <stdio.h>
#define BUFFERSIZE 10

int main(){
  struct circular_list l;
  item i;
  item num ;
  circular_list_create(&l, 10);
  double m = 0;

  while(m < 10){
    i = m;
  circular_list_insert(&l, i);
  m++;
  }
 printf("After inserting:\n");
  int x = 0;
  while(x < l.elems){
    printf("%f\n", l.buffer[x]);fflush(stdout);
   x++;
  }

  circular_list_remove(&l, &num);
  printf("Number removed %f\n", num);
  printf("After removing :\n");
   int y = 0;
  while(y < l.elems){
    printf("%f\n", l.buffer[y]);fflush(stdout);
   y++;
   }
 circular_list_remove(&l, &num);
  printf("Number removed %f\n", num);
  printf("After removing :\n");
   int k = 0;
  while(k < l.elems){
    printf("%f\n", l.buffer[k]);fflush(stdout);
   k++;
   }
   circular_list_remove(&l, &num);
  printf("Number removed %f\n", num);
  printf("After removing :\n");
   int t = 0;
  while(t < l.elems){
    printf("%f\n", l.buffer[t]);fflush(stdout);
   t++;
   }
 circular_list_remove(&l, &num);
  printf("Number removed %f\n", num);
  printf("After removing :\n");
   int r = 0;
  while(r < l.elems){
    printf("%f\n", l.buffer[r]);fflush(stdout);
   r++;
   }
 circular_list_remove(&l, &num);
  printf("Number removed %f\n", num);
  printf("After removing :\n");
   int v = 0;
  while(v < l.elems){
    printf("%f\n", l.buffer[v]);fflush(stdout);
   v++;
   }
  
}
