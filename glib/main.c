
#include "../common_task.h"
#include <assert.h>
#include <stdlib.h>
#include <glib.h>

// The thread executes the function, prints the data after entering, and sleeps for 5 seconds
static inline
void thread_execute (gpointer data, gpointer user_data)
{
  do_work(data);
}

int main(void)
{
  gint max_threads = NUM_THREADS;
  gboolean exclusive = TRUE;
  GError *error = NULL;
  GFunc func = thread_execute;
  gpointer user_data = NULL;
  GThreadPool* tp = g_thread_pool_new (func, user_data, max_threads, exclusive, &error);

  pair_t* arr = calloc(NUM_JOBS, sizeof(pair_t));

  for(int i = 0; i < NUM_JOBS; ++i){
    pair_t* pa = &arr[i]; 
    pa->a = 0; //i%10;
    pa->time = 0;
		g_thread_pool_push(tp, (gpointer)(pa), &error);
    assert(error == NULL);
  }
  //Wait for all tasks in the task queue to be completed
	g_thread_pool_free (tp, FALSE, TRUE);
  free(arr);

  return EXIT_SUCCESS;
}

