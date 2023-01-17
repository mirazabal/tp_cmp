cmake_minimum_required (VERSION 3.0)
project (thread_pools_analysis)

#-std=c11 requests strict POSIX compliance; no extensions like pthread_rwlock_t needed by libuv
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -march=native -flto -fopenmp -O3 -DNDEBUG")



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -march=native -O3 -flto -fopenmp -DNDEBUG")


########
### SANITIZER 
########

set(SANITIZER "NONE" CACHE STRING "Sanitizers")
set_property(CACHE SANITIZER PROPERTY STRINGS "NONE" "ADDRESS" "THREAD")
message(STATUS "Selected SANITIZER TYPE: ${SANITIZER}")

if(${SANITIZER} STREQUAL "ADDRESS")
   add_compile_options("-fno-omit-frame-pointer;-fsanitize=address")
   add_link_options("-fsanitize=address")
elseif(${SANITIZER} STREQUAL "THREAD")
  add_compile_options("-fsanitize=thread;-g;")
  add_link_options("-fsanitize=thread")
elseif(${SANITIZER} STREQUAL "STACK")
  add_compile_options("-fstack-protector-all")
  add_link_options("-fstack-protector-all")
endif()

option(CODE_COVERAGE "Code coverage" OFF)
if(CODE_COVERAGE)
  add_compile_options("-fprofile-arcs;-ftest-coverage")
  add_link_options("-lgcov;-coverage")
  message(STATUS "Code Coverage ON. Example usage: lcov --capture --directory . --output-file coverage.info && genhtml coverage.info --output-directory out && cd out && firefox index.html")

endif()

option(CODE_PROFILER "Code Profiler" OFF)
if( CODE_PROFILER )
  add_compile_options("-pg")
  add_link_options("-pg")
  message(STATUS "Code Profiler ON. Example usage: gprof test/test_near_ric gmon.out > prof.txt && vim prof.txt")
endif()



add_executable(ws_tp 
    "common_task.c"
    "ws_tp/main.c"
    "ws_tp/notification_queue.c"
    "ws_tp/seq_ring_task.c"
    "ws_tp/task_manager.c"
    "ws_tp/spinlock.c"
  )

add_executable(oai_tp 
    "common_task.c"
    "oai_tp/main.c"
    "oai_tp/system.c"
    "oai_tp/thread-pool.c"
  )

add_executable(openmp_tp 
    "common_task.c"
    "open_mp/main.c"
    ) 

add_executable(github_c_tp 
    "common_task.c"
    "C-Thread-Pool/main.c"
    "C-Thread-Pool/thpool.c"
    ) 

add_executable(github_bs_tp 
    "common_task.c"
    "bs-thread-pool/main.cpp"
    ) 

add_executable(glib_tp 
    "common_task.c"
    "glib/main.c"
    ) 

include_directories(glib_tp /usr/lib/x86_64-linux-gnu/glib-2.0/include/)
include_directories(glib_tp /usr/include/glib-2.0/)
target_link_libraries(glib_tp glib-2.0)

add_executable(tbb_tp 
    "common_task.c"
    "tbb/main.cpp"
    ) 

target_link_libraries(tbb_tp tbb)


add_executable(boost_tp 
    "common_task.c"
    "boost/main.cpp"
    ) 

add_executable(libuv_tp 
    "common_task.c"
    "libuv/main.c"
    ) 

target_link_libraries(libuv_tp -l:libuv_a.a )

