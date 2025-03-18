#pragma once
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>

enum class SchedAlg {
    FCFS,
    SJF_NP,
    SJF_P
};

struct ProcResult {
    int pid;
    int arr_time;
    int burst;
    int comp_time;
    int turn_time;
    int wait_time;
};

struct SchedResult {
    std::vector<ProcResult> proc_results;
    double avg_turn_time;
    double avg_wait_time;
    std::vector<std::pair<int, int>> gantt; // pair of <pid, time>
};

class Scheduler {
private:
    std::vector<Process> procs;
    SchedAlg alg;

public:
    Scheduler(const std::vector<Process>& procs, SchedAlg alg);

    // Run the selected scheduling algorithm
    SchedResult run();

    // Individual scheduling algorithms
    SchedResult runFCFS();
    SchedResult runSJF_NP();
    SchedResult runSJF_P();

    // Helper methods
    static std::string algToString(SchedAlg alg);
    static void printSchedResult(const SchedResult& result, SchedAlg alg);
    static void printGantt(const SchedResult& result);
};

#endif // SCHEDULER_H

