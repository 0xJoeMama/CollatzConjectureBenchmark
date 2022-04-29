//
// Created by JoeMama on 26/09/2021.
//

#include <iostream>

#include "benchmark.hpp"

int main()
{
    // this benchmark
    // it grinds nombers and tells you how long it took.
    // it also supports multithreading
    clz_bench::current_run currentRun = clz_bench::identify_run();

    switch (currentRun.type) {
        case clz_bench::run_type::SINGLECORE:
            currentRun.run_singlecore();
            break;
        case clz_bench::run_type::MULTICORE:
            currentRun.run_multicore();
            break;
    }
}
