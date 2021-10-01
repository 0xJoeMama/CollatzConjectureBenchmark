cmake_minimum_required(VERSION 3.0)
project(ProjectEulerProblem)

# Benchmark Project
set(CMAKE_CXX_STANDARD 17)

add_executable(ProjectEulerProblem src/Main.cpp src/impl/Benchmark.cpp)

target_link_directories(ProjectEulerProblem PUBLIC src/include)

target_link_libraries(ProjectEulerProblem PUBLIC -static-libstdc++ -static-libgcc)
