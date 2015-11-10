#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

int main(int argc, char *argv[]){
  void *ptr1;
  void *ptr2;
 void *ptr3;
 void *ptr4, *ptr5, *ptr6;
  printf("malloc: %p\n", malloc(30));
  /*int re = allocator_init(1000, 0);
 showFreeList();
  showAllocatedList();
  ptr1 = allocate(100);
 showFreeList();
  showAllocatedList();
  ptr2 = allocate(400);
 showFreeList();
  showAllocatedList();
   ptr3 = allocate(300);
 showFreeList();
  showAllocatedList();
  ptr4 = allocate(500);
 showFreeList();
  showAllocatedList();
  if(re == 0){
  printf("1st allocation of 100 %p:\n", allocate(100));
  printf("2nd allocation of 400 %p:\n", allocate(400));
  printf("3rd allocation of 300 %p:\n", allocate(300));
  printf("4th allocation of 500 %p:\n",allocate(500));
  }
  showFreeList();
  showAllocatedList();
  deallocate(ptr1);
  showFreeList();
  showAllocatedList();
  deallocate(ptr2);
  showFreeList();
  showAllocatedList();
  */

  /*
  int re = allocator_init(1000, 1);
 showFreeList();
  showAllocatedList();
  ptr1 = allocate(100);
 showFreeList();
  showAllocatedList();
  ptr2 = allocate(400);
 showFreeList();
  showAllocatedList();
   ptr3 = allocate(300);
 showFreeList();
  showAllocatedList();
  ptr4 = allocate(500);
 showFreeList();
  showAllocatedList();
  if(re == 0){
  printf("1st allocation of 100 %p:\n", allocate(100));
  printf("2nd allocation of 400 %p:\n", allocate(400));
  printf("3rd allocation of 300 %p:\n", allocate(300));
  printf("4th allocation of 500 %p:\n",allocate(500));
  }
  showFreeList();
  showAllocatedList();
  deallocate(ptr1);
  showFreeList();
  showAllocatedList();
  deallocate(ptr2);
  showFreeList();
  showAllocatedList();

ptr5 = allocate(100);
 showFreeList();
  showAllocatedList();
  ptr6 = allocate(400);
 showFreeList();
  showAllocatedList();
  deallocate(ptr5);
  showFreeList();
  showAllocatedList();
  deallocate(ptr6);
  showFreeList();*/

allocator_init(1000, 2);
 showFreeList();
  showAllocatedList();
  ptr1 = allocate(100);
 showFreeList();
  showAllocatedList();
  ptr2 = allocate(400);
 showFreeList();
  showAllocatedList();
   ptr3 = allocate(300);
 showFreeList();
  showAllocatedList();
  ptr4 = allocate(500);
 showFreeList();
  showAllocatedList();
  /*if(re == 0){
  printf("1st allocation of 100 %p:\n", allocate(100));
  printf("2nd allocation of 400 %p:\n", allocate(400));
  printf("3rd allocation of 300 %p:\n", allocate(300));
  printf("4th allocation of 500 %p:\n",allocate(500));
  }
  showFreeList();
  showAllocatedList();*/
  deallocate(ptr1);
  showFreeList();
  showAllocatedList();
  deallocate(ptr2);
  showFreeList();
  showAllocatedList();

ptr5 = allocate(100);
 showFreeList();
  showAllocatedList();
  ptr6 = allocate(400);
 showFreeList();
  showAllocatedList();
  deallocate(ptr5);
  showFreeList();
  showAllocatedList();
  deallocate(ptr6);
  showFreeList();
}
