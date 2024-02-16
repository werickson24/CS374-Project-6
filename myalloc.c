#include "myalloc.h"
#include <stddef.h> //NULL
#include <sys/mman.h>
#include <stdio.h>

void * heap = NULL;

void *myalloc(int size){
  if(heap == NULL){
    //printf("[DEBUG] No heap, creating new one...\n");
    heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    struct block * head = heap;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
    head->next = NULL;
  }

  struct block * block = heap;
  while(block != NULL){
    if(block->in_use || block->size < size){
      block = block->next;
    }else{
      block->in_use = 1;
      return block + PADDED_SIZE(sizeof(struct block));
    }
  }

  return NULL;
}

void print_data(void)
{
  struct block *b = heap;

  if (b == NULL) {
    printf("[empty]\n");
    return;
  }

  while (b != NULL) {
    // Uncomment the following line if you want to see the pointer values
    //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
    printf("[%d,%s]", b->size, b->in_use? "used": "free");
    if (b->next != NULL) {
      printf(" -> ");
    }

    b = b->next;
  }

  printf("\n");
}

//void myfree(void *p){}
