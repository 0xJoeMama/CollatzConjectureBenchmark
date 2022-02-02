cmake_minimum_required(VERSION 3.20)
project(collatz-benchmark)

set(CMAKE_CXX_STANDARD 17)

add_executable(collatz-benchmark src/main.cpp src/impl/benchmark.cpp)

target_include_directories(collatz-benchmark PUBLIC src/include)
target_compile_options(collatz-benchmark PUBLIC -Wall -Werror -pedantic -O3)

target_link_libraries(collatz-benchmark PUBLIC pthread)
