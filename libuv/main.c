

#include "../common_task.h"
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "uv.h"

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

static inline 
void work_cb(uv_work_t* req)
{
  do_work(req->data);
}

int main()
{
  int overwrite = 1;
  const char *value = STRINGIFY(NUM_THREADS);
  printf("Value = %s \n", value);                          //

  int r = setenv("UV_THREADPOOL_SIZE" , value , overwrite );
  assert(r == 0);

  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  uv_work_t* work_req = calloc(NUM_JOBS, sizeof(uv_work_t));
  assert(work_req != NULL);

  void (*after_work_cb)(uv_work_t* req, int status) = NULL;

  for(int i = 0; i < NUM_JOBS; ++i){
    arr[i] = fill_pair(i); 
    work_req[i].data = &arr[i];
    int r = uv_queue_work(uv_default_loop(), &work_req[i], work_cb, after_work_cb);
    assert(r == 0);
  }

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  assert(r == 0);

  free(arr);
  free(work_req);

  return 0;
}
