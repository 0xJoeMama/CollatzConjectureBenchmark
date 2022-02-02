//
// Created by JoeMama on 26/09/2021.
//

#include "benchmark.hpp"

#include <chrono>
#include <vector>
#include <future>
#include <iostream>
#include <thread>

using std::chrono::system_clock;
using clz_bench::run_type;
using clz_bench::current_run;

typedef std::chrono::time_point<system_clock> time_point;
typedef std::chrono::duration<double, std::milli> duration;

static std::mutex mutex;

static int iterate(uint64_t number)
{
    int iterations = 0;
    while (number != 1) {
        iterations++;

        if (number % 2 == 0) {
            number /= 2;
        } else {
            number = 3 * number + 1;
        }
    }

    return iterations;
}

void current_run::run_singlecore() const
{
    time_point startingPoint = system_clock::now();
    result result = run_test(1, this->maxNumber);

    if (this->showTime) {
        time_point endingPoint = system_clock::now();

        double elapsedTime = duration(endingPoint - startingPoint).count();
        std::cout << "Elapsed time " << elapsedTime << " ms(" << elapsedTime / 1000 << " seconds)" << std::endl;
    }

    if (this->showResult) {
        std::cout << result.maxIndex << ", " << result.iterationMax << std::endl;
    }
}

void current_run::run_multicore() const
{
    result finalResult = {0};
    std::vector<std::future<result>> futureResults(this->maxThreads);
    uint64_t numberPerThread = maxNumber / maxThreads;

    const time_point start = system_clock::now();
    for (uint32_t i = 0; i < this->maxThreads; ++i) {
        auto begin = i * numberPerThread;
        auto end = (1 + i) * numberPerThread;

        if (i == 0) {
            begin++;
        }

        if (i == this->maxThreads) {
            end = this->maxNumber;
        }

        futureResults[i] = std::async(std::launch::async, run_test, begin, end);
    }

    for (auto& future: futureResults) {
        result result = future.get();

        if (result.iterationMax > finalResult.iterationMax) {
            finalResult.iterationMax = result.iterationMax;
            finalResult.maxIndex = result.maxIndex;
        }
    }

    if (this->showTime) {
        time_point endingPoint = system_clock::now();

        double elapsedTime = duration(endingPoint - start).count();
        std::cout << "Elapsed time " << elapsedTime << " ms(" << elapsedTime / 1000 << " seconds)" << std::endl;
    }

    if (this->showResult) {
        std::cout << finalResult.maxIndex << ", " << finalResult.iterationMax << std::endl;
    }
}

clz_bench::result current_run::run_test(uint64_t begin, uint64_t end)
{
    {
        const std::lock_guard guard(mutex);
        std::cout << "Thread " << std::this_thread::get_id() << " is starting!" << std::endl;
    }

    uint32_t currentMax = 0U;
    uint64_t maxIndex = 0UL;

    for (uint64_t i = begin; i <= end; ++i) {
        if (i % 1000000UL == 0) {
            const std::lock_guard guard(mutex);
            std::cout << "i = " << i << std::endl;
        }

        uint32_t iterationsForI = iterate(i);

        if (iterationsForI > currentMax) {
            currentMax = iterationsForI;
            maxIndex = i;
        }
    }

    return {maxIndex, currentMax};
}

clz_bench::current_run clz_bench::identify_run()
{
    std::cout << "What type of test do you wish to do?" << std::endl;
    std::cout << "(Either SINGLECORE or MULTICORE!): ";

    std::string typeArg;
    std::cin >> typeArg;

    clz_bench::run_type type = typeArg == "MULTICORE" ? run_type::MULTICORE : run_type::SINGLECORE;

    bool showTime;
    std::cout << "Should the time the test took be shown?" << std::endl;
    std::cout << "(Either 0 or 1!): ";
    std::cin >> showTime;

    bool showResult;
    std::cout << "Should the results of the test be shown?" << std::endl;
    std::cout << "(Either 0 or 1!): ";
    std::cin >> showResult;

    uint32_t maxThreads = 0;
    if (type == run_type::MULTICORE) {
        std::cout << "Input the max amount of threads you wish to be used at a time: ";
        std::cin >> maxThreads;
    }

    uint64_t maxNumber = 1000000000UL;
    std::cout << "Input the max number that you want the test to run at: " << std::endl;
    std::cin >> maxNumber;

    return {type, showTime, showResult, maxThreads, maxNumber};
}