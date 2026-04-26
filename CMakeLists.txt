cmake_minimum_required(VERSION 3.10)
project(Chumbimuni_Andre_pc2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# ejecutable demo
add_executable(demo_lfu 
    demos/demos_LFU_Cache.cpp 
    src/LFUCache.cpp
)
# tests
#add_executable(tests_exec tests/test_main.cpp)