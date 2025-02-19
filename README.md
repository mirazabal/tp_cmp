## Thread Pool comparison
# Build
git clone https://github.com/mirazabal/tp_cmp.git && cd tp_cmp && mkdir build && cd build && cmake .. && make -j8
# Run
sudo perf stat ./ws_tp
sudo perf stat ./oai_tp
... 
# Configuration
The amount of jobs and threads can be configured at common_task.h and the job to be emulated at common_task.c -> do_work
This test, shows that the Work Stealing Thread Pool is scalable and beats (at least in the tests I could run in the hardware I had) production ready thread pools.
It also shows that OpenAirInterface Thread Pool simply does not scale
