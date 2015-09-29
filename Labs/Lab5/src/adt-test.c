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

  while(m < 5){
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
  printf("After removing :\n");
   int y = 0;
  while(y < l.elems){
    printf("%f\n", l.buffer[y]);fflush(stdout);
   y++;
   }
}
