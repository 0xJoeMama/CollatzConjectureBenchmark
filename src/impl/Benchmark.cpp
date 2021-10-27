//
// Created by JoeMama on 26/09/2021.
//

#include "../include/Benchmark.hpp"

#include <chrono>
#include <vector>
#include <future>
#include <iostream>
#include <thread>

typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
typedef std::chrono::duration<double, std::milli> Duration;

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

void CurrentRun::runSinglecore() const
{
    TimePoint startingPoint = std::chrono::system_clock::now();

    Result result = runTest(1, this->maxNumber);

    if (this->showTime) {
        TimePoint endingPoint = std::chrono::system_clock::now();

        double elapsedTime = Duration(endingPoint - startingPoint).count();
        std::cout << "Elapsed time " << elapsedTime << " ms(" << elapsedTime / 1000 << " seconds)" << std::endl;
    }

    if (this->showResult) {
        std::cout << result.maxIndex << ", " << result.iterationMax << std::endl;
    }
}

void CurrentRun::runMulticore() const
{
    uint64_t currentMaxIterations = 0UL;
    uint64_t currentMaxNumber = 0UL;

    std::vector<std::future<Result>> futureResults(this->maxThreads);

    const uint64_t numberPerThread = maxNumber / maxThreads;

    TimePoint start = std::chrono::system_clock::now();
    for (uint32_t i = 0; i < this->maxThreads; ++i) {
        auto begin = i * numberPerThread;
        auto end = (1 + i) * numberPerThread;

        if (i == 0) {
            begin++;
        }

        if (i == this->maxThreads) {
            end = this->maxNumber;
        }

        futureResults[i] = std::async(std::launch::async, runTest, begin, end);
    }

    for (auto& future: futureResults) {
        Result result = future.get();

        if (result.iterationMax > currentMaxIterations) {
            currentMaxIterations = result.iterationMax;
        }

        if (result.maxIndex > currentMaxNumber) {
            currentMaxNumber = result.maxIndex;
        }
    }

    Result finalResult = {currentMaxNumber, currentMaxIterations};

    if (this->showTime) {
        TimePoint endingPoint = std::chrono::system_clock::now();

        double elapsedTime = Duration(endingPoint - start).count();
        std::cout << "Elapsed time " << elapsedTime << " ms(" << elapsedTime / 1000 << " seconds)" << std::endl;
    }

    if (this->showResult) {
        std::cout << finalResult.maxIndex << ", " << finalResult.iterationMax << std::endl;
    }
}

Result CurrentRun::runTest(uint64_t begin, uint64_t end)
{
    mutex.lock();
    std::cout << "Thread " << std::this_thread::get_id() << " is starting!" << std::endl;
    mutex.unlock();

    uint32_t currentMax = 0U;
    uint64_t maxIndex = 0UL;

    for (uint64_t i = begin; i <= end; ++i) {
        if (i % 1000000UL == 0) {
            mutex.lock();
            std::cout << "i = " << i << std::endl;
            mutex.unlock();
        }

        uint32_t iterationsForI = iterate(i);

        if (iterationsForI > currentMax) {
            currentMax = iterationsForI;
            maxIndex = i;
        }
    }

    return {maxIndex, currentMax};
}

CurrentRun identifyRun()
{
    RunType type;

    std::cout << "What type of test do you wish to do?" << std::endl;
    std::cout << "(Either SINGLECORE or MULTICORE!): ";

    std::string typeArg;
    std::cin >> typeArg;

    if (typeArg == "MULTICORE") {
        type = MULTICORE;
    } else {
        type = SINGLECORE;
    }

    bool showTime;
    std::cout << "Should the time the test took be shown?" << std::endl;
    std::cout << "(Either 0 or 1!): ";
    std::cin >> showTime;

    bool showResult;
    std::cout << "Should the results of the test be shown?" << std::endl;
    std::cout << "(Either 0 or 1!): ";
    std::cin >> showResult;

    uint32_t maxThreads = 0;
    if (type == MULTICORE) {
        std::cout << "Input the max amount of threads you wish to be used at a time: ";
        std::cin >> maxThreads;
    }

    uint64_t maxNumber = 1000000000UL;
    std::cout << "Input the max number that you want the test to run at: " << std::endl;
    std::cin >> maxNumber;

    return {type, showTime, showResult, maxThreads, maxNumber};
}