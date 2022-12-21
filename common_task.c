#define _GNU_SOURCE

#include "common_task.h"


#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <time.h>

int64_t time_now_us(void)
{
  struct timespec tms;

  /* The C11 way */
  /* if (! timespec_get(&tms, TIME_UTC))  */

  /* POSIX.1-2008 way */
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
    return -1;
  }
  /* seconds, multiplied with 1 million */
  int64_t micros = tms.tv_sec * 1000000;
  /* Add full microseconds */
  int64_t const tv_nsec = tms.tv_nsec;
  micros += tv_nsec/1000;
  /* round up if necessary */
  if (tv_nsec % 1000 >= 500) {
    ++micros;
  }
  return micros;
}

static inline
int64_t naive_fibonnacci(int64_t a)
{
  assert(a < 100);
  if(a < 2)
    return a;
  
  return naive_fibonnacci(a-1) + naive_fibonnacci(a-2);
}

void do_work(void* arg)
{
  pair_t* a = (pair_t*)arg;
  naive_fibonnacci(19 + a->a);
  a->time = time_now_us();
}

