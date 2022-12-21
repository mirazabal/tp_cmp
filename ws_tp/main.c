#include <assert.h>
#include <stdlib.h>
#include "task_manager.h"
#include "../common_task.h"

int main()
{
  task_manager_t man;
  init_task_manager(&man, NUM_THREADS);

  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  for(int i = 0; i < NUM_JOBS; ++i){
    pair_t* pa = &arr[i]; 
    pa->a = 0; //i%10;
    pa->time = 0;
    task_t t = {.args = pa, t.func = do_work};
    async_task_manager(&man, t);
  }

  wait_all_task_manager(&man); 
  free(arr);
  free_task_manager(&man, NULL);

  return EXIT_SUCCESS;
}

