#ifndef _PERRY_POINTER_H_
#define _PERRY_POINTER_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#define and &&
#define or ||
#define nullptr (void *)0

#define DATA_ARRAY_INIT_SIZE 65536
#define DATA_ARRAY_MAX_SIZE 4200000000
#define PPT_STACK_INIT_SIZE 512

#define true 1
#define false 0
typedef int bool;

typedef enum{
  SUCCESS,

  HEAP_INIT_FAILED,

  DATA_ARRAY_CREATION_FAILED,
  DATA_ARRAY_CURRENT_SIZE_EXCEEDED,
  DATA_ARRAY_MAX_SIZE_EXCEEDED,
  DATA_ARRAY_UNALLOCATED,

  PPT_STACK_CREATION_FAILED,
  PPT_STACK_SPACE_NOT_FOUND,
  PPT_STACK_UNALLOCATED,
  PPT_STACK_SPACE_FOUND ,
  
  
} MSG;


typedef enum{

  ALLOCATED,
  FREED
  
}STATE;


typedef struct ppt{

  //perry pointer oviously
  uint32_t index;
  uint32_t mem_start;
  uint32_t mem_end;
  uint32_t len;
  STATE state;

}ppt;

typedef struct ppt_heap{

  ppt * ppt_stack;
  uint32_t stack_top;
  uint32_t stack_bottom;
  uint32_t ppt_stack_size;

  uint32_t * mem;
  uint32_t mem_index;
  uint32_t mem_size;
  
  
}ppt_heap;


MSG ppt_heap_init(ppt_heap * h);

MSG ppt_heap_clear(ppt_heap * h);

MSG ppt_heap_balance(); // uimplemented

ppt ppt_alloc(uint32_t len , ppt_heap * h);

void ppt_free(ppt p , ppt_heap * h);

void ppt_set_value(uint32_t value , ppt p , uint32_t offset , ppt_heap * h);

uint32_t ppt_get_value(ppt p , uint32_t offset , ppt_heap * h);



#endif //_PERRY_POINTER_H_
