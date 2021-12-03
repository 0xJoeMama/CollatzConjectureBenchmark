cmake_minimum_required(VERSION 3.20)
project(CollatzConjBenchmark)

set(CMAKE_CXX_STANDARD 17)

add_executable(CollatzConjBenchmark src/Main.cpp src/impl/Benchmark.cpp)

target_include_directories(CollatzConjBenchmark PUBLIC src/include)
target_compile_options(CollatzConjBenchmark PUBLIC -Wall -Werror)

target_link_libraries(CollatzConjBenchmark PUBLIC pthread)
