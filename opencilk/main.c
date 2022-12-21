#include <assert.h>
#include <stdlib.h>

#include <cilk/cilk.h>

#include "../common_task.h"

int main()
{
  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  for(int i = 0; i < NUM_JOBS; ++i){
    pair_t* pa = &arr[i]; 
    pa->a = 0; //i%10;
    pa->time = 0;

    cilk_spawn do_work(pa);
  }
  cilk_sync; 

  return EXIT_SUCCESS;
}
