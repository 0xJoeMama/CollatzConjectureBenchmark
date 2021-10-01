cmake_minimum_required(VERSION 3.0)
project(CollatzConjBenchmark)

# Benchmark Project
set(CMAKE_CXX_STANDARD 17)

add_executable(CollatzConjBenchmark src/Main.cpp src/impl/Benchmark.cpp)

target_link_directories(CollatzConjBenchmark PUBLIC src/include)

target_link_libraries(CollatzConjBenchmark PUBLIC -static-libstdc++ -static-libgcc)
