cmake_minimum_required(VERSION 3.10)
project(Chumbimuni_Andre_pc2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# ejecutable principal
add_executable(program_exec src/main.cpp)

# tests
add_executable(tests_exec tests/test_main.cpp)