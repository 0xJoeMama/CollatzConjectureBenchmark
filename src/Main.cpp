//
// Created by JoeMama on 26/09/2021.
//

#include "include/Benchmark.hpp"

int main()
{
    // this benchmark
    // it grinds nombers and tells you how long it took.
    // it also supports multithreading
    CurrentRun currentRun = identifyRun();

    switch (currentRun.type) {
        case SINGLECORE:
            currentRun.runSinglecore();
            break;
        case MULTICORE:
            currentRun.runMulticore();
            break;
    }
}
