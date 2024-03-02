#include "perry_pointer.h"


MSG ppt_heap_init(ppt_heap * h){

  h->ppt_stack = calloc(PPT_STACK_INIT_SIZE,sizeof(ppt));
  if(h->ppt_stack == NULL){

    return PPT_STACK_CREATION_FAILED;
  }
  h->ppt_stack_size = PPT_STACK_INIT_SIZE;
  h-> stack_top = 0;
  h-> stack_bottom = 0;

  
  h->mem = calloc(DATA_ARRAY_INIT_SIZE,sizeof(uint32_t));
  if(h->mem == NULL){

    return DATA_ARRAY_CREATION_FAILED;
  }
  h->mem_size = DATA_ARRAY_INIT_SIZE;
  h->mem_index = 0;

  return SUCCESS;
  
}


MSG ppt_push( uint32_t len , STATE state , ppt_heap * h){

  h->ppt_stack[h->stack_top].index = h->stack_top;
  h->ppt_stack[h->stack_top].mem_start = h->mem_index;
  h->ppt_stack[h->stack_top].mem_end = h->mem_index + len;
  h->ppt_stack[h->stack_top].len = len;
  h->ppt_stack[h->stack_top].state = state;
  h->stack_top = h->stack_top + 1;
  h->mem_index = h->mem_index + len;

  return SUCCESS;
  
}

MSG ppt_search(ppt_heap * h , uint32_t len){

  for (uint32_t i = 0 ; i < h->stack_top ;i++){

    if(h->ppt_stack[i].state == FREED){

      if(len <= (h->ppt_stack[i].mem_end - h->ppt_stack[i].mem_start) ){
	  return PPT_STACK_SPACE_FOUND;
	}
    }
  }

  return PPT_STACK_SPACE_NOT_FOUND;
    
    
}

MSG ppt_heap_grow(ppt_heap * h , uint32_t len){
  uint32_t new_mem_size = h->mem_size + (h->mem_size/2);
  if((new_mem_size - h->mem_index) < len ){
    new_mem_size = new_mem_size + len;
  }
  if(new_mem_size > DATA_ARRAY_MAX_SIZE){
    return DATA_ARRAY_MAX_SIZE_EXCEEDED;
  }
  printf("hehe\n");
  uint32_t new_stack_size = h->ppt_stack_size + (h->ppt_stack_size/2);

  ppt * new_ppt_stack = calloc(new_stack_size,sizeof(ppt));
  uint32_t * new_mem = calloc(new_mem_size , sizeof(uint32_t));

  for(uint32_t i = 0 ; i < h->stack_top ; i++ ){
    new_ppt_stack[i] = h->ppt_stack[i];
  }

  
  for(uint32_t i = 0 ; i < h->mem_index ; i++ ){
    new_mem[i] = h->mem[i];
  }

  free(h->mem);
  free(h->ppt_stack);

  h->mem = new_mem ;
  h->ppt_stack = new_ppt_stack;
  return SUCCESS;
  
}


MSG ppt_heap_clear(ppt_heap * h){

  free(h->ppt_stack);
  free(h->mem);
  free(h);
  
}


MSG ppt_heap_balance(){

  
}

ppt ppt_alloc(uint32_t len , ppt_heap * h){
  printf("%u  > %u\n",len,(h->mem_size - h->mem_index));
  if(len > (h->mem_size - h->mem_index)){
    ppt_heap_grow(h, len);
  }
  
  if(h->stack_top == 0){
    ppt_push(len , ALLOCATED , h);
    return h->ppt_stack[0];
  }

  if(ppt_search(h, len) == PPT_STACK_SPACE_FOUND){

    for (uint32_t i = 0 ; i < h->stack_top ;i++){
      
      if(h->ppt_stack[i].state == FREED){

	if(len <= (h->ppt_stack[i].mem_end - h->ppt_stack[i].mem_start) ){
	  h->ppt_stack[i].state = ALLOCATED;
	  return h->ppt_stack[i];
	}

      }

    }
    
  }else{

    ppt_push(len , ALLOCATED , h);
    return h->ppt_stack[h->stack_top - 1];
    
  }
  
}


void ppt_free(ppt p , ppt_heap * h){

  h->ppt_stack[p.index].state = FREED;
  
}

void ppt_set_value(uint32_t value , ppt p , uint32_t offset , ppt_heap * h){
  
  if(h->ppt_stack[p.index].state == FREED){
    printf("Trying to set to freed memory\n");
    exit(-1);
  }

  if((h->ppt_stack[p.index].mem_end - h->ppt_stack[p.index].mem_start) < offset){
    printf("Array length is insufficient\n");
    exit(-1);
  }

  h->mem[h->ppt_stack[p.index].mem_start + offset] = value; 
  
  
}

uint32_t ppt_get_value(ppt p , uint32_t offset , ppt_heap * h){

  if(h->ppt_stack[p.index].state == FREED){
    printf("Trying to derefrence freed pointer\n");
    exit(-1);
  }

  if((h->ppt_stack[p.index].mem_end - h->ppt_stack[p.index].mem_start) < offset){
    printf("Array length is insufficient\n");
    exit(-1);
  }

  return h->mem[h->ppt_stack[p.index].mem_start + offset];
  
}

