#include "BS_thread_pool.hpp"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "../common_task.h"




int main()
{
  BS::thread_pool pool(NUM_THREADS);
  pair_t* arr = (pair_t*)calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  for (int i = 0; i < NUM_JOBS; ++i){

    pair_t* pa = &arr[i]; 
    pa->a = 0; 
    pa->time = 0;

    pool.push_task(
        [pa] {
        do_work(pa);
        });
  }

  pool.wait_for_tasks();
  free(arr);
  return 0;
}

