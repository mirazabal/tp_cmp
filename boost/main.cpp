#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>

#include "../common_task.h" 

int main()
{

  // Launch the pool with num threads.
  boost::asio::thread_pool pool(NUM_THREADS);

  pair_t* arr = (pair_t*)calloc(NUM_JOBS, sizeof(pair_t));
  assert(arr != NULL);

  for(int i = 0; i < NUM_JOBS; ++i){
    arr[i] = fill_pair(i); 
    pair_t* p = &arr[i];  
    // Submit a lambda object to the pool.
    boost::asio::post(pool, [p]() { do_work(p);  });
  }
  // Wait for all tasks in the pool to complete.
  pool.join();

  free(arr);



}

