#include "perry_pointer.h"

int main(){

  ppt_heap * h = malloc(sizeof(ppt_heap));

  ppt_heap_init(h);
  
   
  ppt a = ppt_alloc(350 , h);
  
  ppt b = ppt_alloc(70000 , h);

  
  for(uint32_t i = 0 ;  i < 350 ; i++){
    ppt_set_value(i , a , i , h);
  }


  for(uint32_t i = 0 ;  i < 70000 ; i++){
    ppt_set_value(i , b , i , h);
  }

  for(uint32_t i = 0 ; i < 350 ; i ++){
    printf(" %ud : ",ppt_get_value(a , i , h));
  }

  
  for(uint32_t i = 0 ; i < 70000 ; i ++){
    printf(" %ud : ",ppt_get_value(b , i , h));
  }

  ppt_free(a , h);

  ppt c = ppt_alloc(200 , h);

  for(uint32_t i = 0 ;  i < 200 ; i++){
    ppt_set_value(69 , c , i , h);
  }

  for(uint32_t i = 0 ;  i < 200 ; i++){
    printf("%d \n",h->mem[0]);
  }

  
  
  

  ppt_heap_clear(h);
  
}
