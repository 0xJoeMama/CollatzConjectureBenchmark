//
// Created by JoeMama on 26/09/2021.
//

#pragma once

#include <cstdint>

struct Result
{
    uint64_t maxIndex;
    uint64_t iterationMax;
};

enum RunType
{
    SINGLECORE,
    MULTICORE
};

struct CurrentRun
{
    const RunType type;
    const bool showTime;
    const bool showResult;
    const uint32_t maxThreads;
    const uint64_t maxNumber;

    void runSinglecore() const;

    void runMulticore() const;

private:
    static Result runTest(uint64_t begin, uint64_t end);
};

CurrentRun identifyRun();
