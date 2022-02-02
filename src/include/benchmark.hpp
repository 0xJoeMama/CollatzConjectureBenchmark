//
// Created by JoeMama on 26/09/2021.
//

#pragma once

#include <cstdint>

namespace clz_bench
{
    struct result
    {
        uint64_t maxIndex;
        uint64_t iterationMax;
    };

    enum run_type
    {
        SINGLECORE,
        MULTICORE
    };

    struct current_run
    {
        const run_type type;
        const bool showTime;
        const bool showResult;
        const uint32_t maxThreads;
        const uint64_t maxNumber;

        void run_singlecore() const;

        void run_multicore() const;

    private:
        static result run_test(uint64_t begin, uint64_t end);
    };

    current_run identify_run();

}