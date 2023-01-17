#ifndef COMMON_TASK_H
#define COMMON_TASK_H 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define NUM_THREADS 4
#define NUM_JOBS 8*1024*1024

typedef struct{
  int64_t a;
  int64_t time;
} pair_t;

pair_t fill_pair(int64_t a);

int64_t time_now_us(void);

void do_work(void* arg);




#ifdef __cplusplus
}
#endif



#endif

