
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <omp.h>

#include "../common_task.h"

int main()
{
  omp_set_num_threads(NUM_THREADS);

  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

//  const int64_t last = time_now_us() ;
#pragma omp parallel
  {
#pragma omp single
    {
      for(int i = 0; i < NUM_JOBS; ++i){
        pair_t* pa = &arr[i]; 
        pa->a = 0; //i%10;
        pa->time = 0;
#pragma omp task
        do_work(pa);
      }
    }
  }
#pragma omp taskwait

//  printf("Last time elapsed = %ld \n", arr[ (8*1024*1024) - 1 ].time - last );
  free(arr);
  return 0;
}
