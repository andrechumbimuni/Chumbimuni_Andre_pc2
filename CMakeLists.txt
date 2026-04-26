cmake_minimum_required(VERSION 3.10)
project(Chumbimuni_Andre_pc2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#optimización extrema: set(CMAKE_CXX_FLAGS "-O3")

include_directories(include)

# ejecutable demo
add_executable(demo_lfu 
    demos/demos_LFU_Cache.cpp 
    src/LFUCache.cpp
)
# Tests
add_executable(test_lfu 
    tests/test_lfu.cpp 
    src/LFUCache.cpp
)

# Benchmark
add_executable(benchmark_lfu 
    benchmark/benchmark_lfu.cpp 
    src/LFUCache.cpp
)