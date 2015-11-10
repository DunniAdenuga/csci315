#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Usage: frag-eval [algorithm] [seed] [int requests]");
    return 0;
  }
  int algor = atoi(argv[1]);
  if( ( algor > 2) ||(algor < 0)) {
    printf("algorithm can only be 0, 1, 2");
    return 0;
  }

  int seed = atoi(argv[2]);
  uint32_t requests = (uint32_t)atoi(argv[3]);
  
  allocator_init(10240, algor);
  srandom(seed);

  int r = 0;
  int size = 0;
  void *p = NULL;
  while(r < requests){
    size = rand()%900 + 100;
    p = allocate(size);
    //printf("Size %d is: %d\n", r+1, size);
    r++;
    //showFreeList();
    //showAllocatedList();
    deallocate(p);
}
  printf("%d,", 1);
  printf("%d,", seed);
	 printf("%f\n", average_frag());
}
