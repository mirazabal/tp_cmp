/* 
 * WHAT THIS EXAMPLE DOES
 * 
 * We create a pool of 4 threads and then add 40 tasks to the pool(20 task1 
 * functions and 20 task2 functions). task1 and task2 simply print which thread is running them.
 * 
 * As soon as we add the tasks to the pool, the threads will run them. It can happen that 
 * you see a single thread running all the tasks (highly unlikely). It is up the OS to
 * decide which thread will run what. So it is not an error of the thread pool but rather
 * a decision of the OS.
 * 
 * */

#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

#include "thpool.h"
#include "../common_task.h"

int main(){
	
	threadpool thpool = thpool_init(NUM_THREADS);

  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

	for (int i=0; i< NUM_JOBS; i++){

    pair_t* pa = &arr[i];
    pa->a = 0; // i%10;
    pa->time =  0;

		thpool_add_work(thpool,do_work, pa );
	};

	thpool_wait(thpool);
	thpool_destroy(thpool);
  free(arr);
	return 0;
}
