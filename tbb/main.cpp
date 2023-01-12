
#include <oneapi/tbb/task_group.h>
#include <oneapi/tbb/global_control.h>

#include <assert.h>
#include <stdlib.h>
#include "../common_task.h"


int main()
{
  oneapi::tbb::global_control global_limit(oneapi::tbb::global_control::max_allowed_parallelism, NUM_THREADS);

  tbb::task_group g;

  pair_t* arr = (pair_t*)calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  for (int i = 0; i < NUM_JOBS; ++i){
    arr[i] = fill_pair(i); 
    pair_t* pa = &arr[i]; 
    g.run([&pa]{do_work(pa); });
  }
  g.wait();

  free(arr);
}

