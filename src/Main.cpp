//
// Created by JoeMama on 26/09/2021.
//

#include <iostream>
#include "Benchmark.hpp"

int main()
{
    // this benchmark
    // it grinds nombers and tells you how long it took.
    // it also supports multithreading
    CurrentRun currentRun = identifyRun();

    switch (currentRun.type) {
        case RunType::SINGLECORE:
            currentRun.runSinglecore();
            break;
        case RunType::MULTICORE:
            currentRun.runMulticore();
            break;
    }

    std::cout << "Press ENTER key to continue..." << std::endl;
    std::cin.get();
}
