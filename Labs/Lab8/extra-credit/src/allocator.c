#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

int type;
struct dlist *free_list;
 struct dlist *allocated_list;

int allocator_init(size_t sizee, int typee){
  type = typee;
  struct dnode *startNode = dnode_create();
  if( (startNode->data = malloc(sizee)) == NULL){
    return -1;
  }
  printf("Initial: %p\n", startNode->data);
  startNode->size = sizee;
  free_list = dlist_create();
  allocated_list = dlist_create();

  dlist_add_back(free_list, startNode);
  return 0;
}

void* allocate(size_t size){
  
  if(type == 0){//first-fit
   return  allocateFirstFit(size);    
  }
  if(type == 1){//best-fit
    return  allocateBestFit(size); 

  }
  if(type == 2){//worst-fit
     return  allocateWorstFit(size);
  }
  return NULL;
}

int deallocate(void *ptr){
  allocated_list->iter = allocated_list->front;
  struct dnode *start;
  int i = 0;
for(start = dlist_iter_begin(allocated_list); i < dlist_num_elems(allocated_list);  start = dlist_iter_next(allocated_list)){
  if(start->data == ptr){
    struct dnode *newNode = dnode_create();
    newNode->data = ptr;
    newNode->size = start->size;
    dlist_add_back(free_list, newNode);
    dlist_find_remove(allocated_list, start->data);
    //free ?
    
    return 0;
  }
  i++;
 }
 return -1;
}
void* allocateFirstFit(size_t size){
free_list->iter = free_list->front;
 struct dnode* start;
  uint32_t i = 0;
 struct dnode *newNode;
    for(start = dlist_iter_begin(free_list); i < dlist_num_elems(free_list);  start = dlist_iter_next(free_list)){
      if(start->size >= size){
	newNode = dnode_create();
	newNode->data = start->data;
	newNode->size = size;
	start->data = start->data + size;
	start->size = start->size - size;
	break;
      }
      i++;
}
    if(newNode->data != NULL){
    dlist_add_back(allocated_list,newNode);
    return newNode->data;
    }
    else{
      printf("Memory has finish\n");
     
}   
 return NULL;
}

void* allocateBestFit(size_t size){
struct dnode* start;
  uint32_t i = 0;
free_list->iter = free_list->front;
struct dnode *tempNode = dnode_create();
    
 tempNode->size = (dlist_iter_begin(free_list))->size;
 free_list->iter = free_list->front;
    struct dnode *newNode = dnode_create();
    for(start = dlist_iter_begin(free_list); i < dlist_num_elems(free_list);  start = dlist_iter_next(free_list)){
      if((start->size >= size)&& (start->size <= tempNode->size)){
	tempNode = start;
      }
      i++;
    }
    newNode->data = tempNode->data;
    newNode->size = size;
    tempNode->data = tempNode->data + size;
    tempNode->size = tempNode->size - size;
    if(newNode->data != NULL){
    dlist_add_back(allocated_list,newNode);
    return newNode->data;
    }
else{
      printf("Memory has finish\n");
     
}   
 return NULL;
}

void* allocateWorstFit(size_t size){
struct dnode* start;
  uint32_t i = 0;
free_list->iter = free_list->front;
struct dnode *tempNode = dnode_create();
    
    tempNode->size = (dlist_iter_begin(free_list))->size;
 free_list->iter = free_list->front;
    struct dnode *newNode = dnode_create();
    for(start = dlist_iter_begin(free_list); i < dlist_num_elems(free_list);  start = dlist_iter_next(free_list)){
      if((start->size >= size)&& (start->size >= tempNode->size)){
	tempNode = start;
      }
      i++;
    }
    newNode->data = tempNode->data;
    newNode->size = size;
    tempNode->data = tempNode->data + size;
    tempNode->size = tempNode->size - size;
    if(newNode->data != NULL){
    dlist_add_back(allocated_list,newNode);
    return newNode->data;
    }
else{
      printf("Memory has finish\n");
     
}   
 return NULL;
}

void showFreeList(){
  struct dnode* start;
  uint32_t i = 0;
  free_list->iter = free_list->front;
  printf("Free List:\n");
  for(start = dlist_iter_begin(free_list); i < dlist_num_elems(free_list);  start = dlist_iter_next(free_list)){
    printf(" Node %d has size %d.\n", i, start->size);
    i++;
  }
}

void showAllocatedList(){
 struct dnode* start;
  uint32_t i = 0;
 allocated_list->iter = allocated_list->front;
 printf("Allocated List:\n");
  for(start = dlist_iter_begin(allocated_list); i < dlist_num_elems(allocated_list);  start = dlist_iter_next(allocated_list)){
    printf(" Node %d has size %d.\n", i, start->size);
    i++;
  }
}

void modifyFreeList(){
struct dnode* start;
 struct dnode* newNode = dnode_create();
 //newNode->size = 0;
  uint32_t i = 0;
  free_list->iter = free_list->front;
  for(start = dlist_iter_begin(free_list); i < dlist_num_elems(free_list);  start = dlist_iter_next(free_list)){
    struct dnode* tempNode = dlist_iter_next(free_list);
    if((start->data+start->size) == (tempNode->data)){
      newNode->size = newNode->size + start->size+tempNode->size;
      newNode->data = start->data;
      dlist_find_remove(free_list, start->data);
      dlist_find_remove(free_list, tempNode->data);
      dlist_add_back(free_list, newNode);
      free_list->iter = free_list->front;
  }
    i++;
  }
}
