#include "thread-pool.h"

#include "../common_task.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char const threads[] = "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31";
  char params[64] = {0};
  assert(NUM_THREADS > 0 && NUM_THREADS < 33);
  if(NUM_THREADS < 11)
    memcpy(params, threads, 2*NUM_THREADS - 1 );
  else
    memcpy(params, threads, 2*NUM_THREADS + ((NUM_THREADS -10) - 1) );

  tpool_t  pool = {0};
  initTpool(params,&pool, false);

  notifiedFIFO_t worker_back;
  initNotifiedFIFO(&worker_back);

  int const sz_elm = sizeof(notifiedFIFO_elt_t)+ sizeof(pair_t) + 32;
  notifiedFIFO_elt_t* arr = calloc(NUM_JOBS, sz_elm);

  int i = 0; 
  for (; i < NUM_JOBS; i++) {
    notifiedFIFO_elt_t *work = (notifiedFIFO_elt_t *)&((uint8_t*)arr)[i*(sz_elm)] ;
    work->reponseFifo = &worker_back;
    work->processingFunc = do_work;
    work->msgData = (void *)((uint8_t*)work+sizeof(notifiedFIFO_elt_t));

    pair_t* p = (pair_t*)NotifiedFifoData(work);
    p->a = 0;
    p->time = 0;
    pushTpool(&pool, work);
  }

  while (i > 0) {
    notifiedFIFO_elt_t* tmp = pullTpool(&worker_back,&pool);
  //  if (tmp) {
  //     delNotifiedFIFO_elt(tmp);
  //   }
    --i;
  }

  free(arr);
  return 0;
}

