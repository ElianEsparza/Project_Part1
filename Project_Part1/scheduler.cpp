#include "scheduler.h"

Scheduler::Scheduler(const std::vector<Process>& procs, SchedAlg alg)
    : procs(procs), alg(alg) {
}

SchedResult Scheduler::run() {
    switch (alg) {
    case SchedAlg::FCFS:
        return runFCFS();
    case SchedAlg::SJF_NP:
        return runSJF_NP();
    case SchedAlg::SJF_P:
        return runSJF_P();
    default:
        // Default to FCFS if algorithm is not recognized
        return runFCFS();
    }
}

SchedResult Scheduler::runFCFS() {
    SchedResult result;
    result.proc_results.resize(procs.size());

    // Create a copy of processes to work with
    std::vector<Process> pq = procs;

    // Sort processes by arrival time
    std::sort(pq.begin(), pq.end(),
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    int cur_time = 0;
    double tot_turn = 0;
    double tot_wait = 0;

    for (size_t i = 0; i < pq.size(); i++) {
        Process& p = pq[i];

        // If current time is less than arrival time, CPU is idle
        if (cur_time < p.getArrivalTime()) {
            cur_time = p.getArrivalTime();
        }

        // Set process to RUNNING state
        p.setState(ProcessState::RUNNING);

        // Add to Gantt chart
        result.gantt.push_back(std::make_pair(p.getPid(), cur_time));

        // Process execution
        p.decrementRemainingTime(p.getBurstTime());

        // Calculate completion time
        int comp_time = cur_time + p.getBurstTime();

        // Calculate turnaround time (completion time - arrival time)
        int turn_time = comp_time - p.getArrivalTime();

        // Calculate waiting time (turnaround time - burst time)
        int wait_time = turn_time - p.getBurstTime();

        // Update process state to TERMINATED
        p.setState(ProcessState::TERMINATED);

        // Store results
        ProcResult& pr = result.proc_results[i];
        pr.pid = p.getPid();
        pr.arr_time = p.getArrivalTime();
        pr.burst = p.getBurstTime();
        pr.comp_time = comp_time;
        pr.turn_time = turn_time;
        pr.wait_time = wait_time;

        // Update current time
        cur_time = comp_time;

        // Accumulate for averages
        tot_turn += turn_time;
        tot_wait += wait_time;
    }

    // Calculate averages
    result.avg_turn_time = tot_turn / procs.size();
    result.avg_wait_time = tot_wait / procs.size();

    return result;
}

SchedResult Scheduler::runSJF_NP() {
    SchedResult result;
    result.proc_results.resize(procs.size());

    // Create a copy of processes to work with
    std::vector<Process> pq = procs;

    // Sort processes by arrival time initially
    std::sort(pq.begin(), pq.end(),
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    int cur_time = 0;
    double tot_turn = 0;
    double tot_wait = 0;

    // Keep track of which processes have been executed
    std::vector<bool> done(pq.size(), false);

    // Continue until all processes are executed
    for (size_t i = 0; i < pq.size(); i++) {
        // Find the process with shortest burst time among the arrived processes
        int shortest_idx = -1;
        int shortest_burst = INT_MAX;

        for (size_t j = 0; j < pq.size(); j++) {
            if (!done[j] && pq[j].getArrivalTime() <= cur_time &&
                pq[j].getBurstTime() < shortest_burst) {
                shortest_idx = j;
                shortest_burst = pq[j].getBurstTime();
            }
        }

        // If no process has arrived yet, advance time to the next arrival
        if (shortest_idx == -1) {
            int next_arr = INT_MAX;
            int next_idx = -1;

            for (size_t j = 0; j < pq.size(); j++) {
                if (!done[j] && pq[j].getArrivalTime() < next_arr) {
                    next_arr = pq[j].getArrivalTime();
                    next_idx = j;
                }
            }

            cur_time = next_arr;
            shortest_idx = next_idx;
        }

        // Mark the process as executed
        done[shortest_idx] = true;

        Process& p = pq[shortest_idx];

        // Set process to RUNNING state
        p.setState(ProcessState::RUNNING);

        // Add to Gantt chart
        result.gantt.push_back(std::make_pair(p.getPid(), cur_time));

        // Process execution
        p.decrementRemainingTime(p.getBurstTime());

        // Calculate completion time
        int comp_time = cur_time + p.getBurstTime();

        // Calculate turnaround time (completion time - arrival time)
        int turn_time = comp_time - p.getArrivalTime();

        // Calculate waiting time (turnaround time - burst time)
        int wait_time = turn_time - p.getBurstTime();

        // Update process state to TERMINATED
        p.setState(ProcessState::TERMINATED);

        // Store results
        ProcResult pr;
        pr.pid = p.getPid();
        pr.arr_time = p.getArrivalTime();
        pr.burst = p.getBurstTime();
        pr.comp_time = comp_time;
        pr.turn_time = turn_time;
        pr.wait_time = wait_time;

        result.proc_results[i] = pr;

        // Update current time
        cur_time = comp_time;

        // Accumulate for averages
        tot_turn += turn_time;
        tot_wait += wait_time;
    }

    // Calculate averages
    result.avg_turn_time = tot_turn / procs.size();
    result.avg_wait_time = tot_wait / procs.size();

    return result;
}

SchedResult Scheduler::runSJF_P() {
    SchedResult result;
    result.proc_results.resize(procs.size());

    // Create a copy of processes to work with
    std::vector<Process> pq = procs;

    // Sort processes by arrival time initially
    std::sort(pq.begin(), pq.end(),
        [](const Process& a, const Process& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });

    int n = pq.size();

    // Arrays to store process information
    std::vector<int> rem_time(n);
    std::vector<int> comp_time(n, 0);
    std::vector<bool> done(n, false);

    // Initialize burst remaining times
    for (int i = 0; i < n; i++) {
        rem_time[i] = pq[i].getBurstTime();
    }

    int cur_time = 0;
    int done_procs = 0;
    int prev_proc = -1;

    // Continue until all processes are completed
    while (done_procs < n) {
        // Find process with minimum remaining time among arrived processes
        int shortest_idx = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && pq[i].getArrivalTime() <= cur_time &&
                rem_time[i] < shortest_burst) {
                shortest_idx = i;
                shortest_burst = rem_time[i];
            }
        }

        // If no process is found, advance time
        if (shortest_idx == -1) {
            cur_time++;
            continue;
        }

        // If process changed, update Gantt chart
        if (prev_proc != shortest_idx) {
            result.gantt.push_back(std::make_pair(pq[shortest_idx].getPid(), cur_time));
            prev_proc = shortest_idx;
        }

        // Reduce remaining time of selected process
        rem_time[shortest_idx]--;
        cur_time++;

        // If process is completed
        if (rem_time[shortest_idx] == 0) {
            done_procs++;
            done[shortest_idx] = true;

            // Calculate completion time
            comp_time[shortest_idx] = cur_time;

            // Calculate turnaround time (completion time - arrival time)
            int turn_time = comp_time[shortest_idx] - pq[shortest_idx].getArrivalTime();

            // Calculate waiting time (turnaround time - burst time)
            int wait_time = turn_time - pq[shortest_idx].getBurstTime();

            // Store results
            ProcResult pr;
            pr.pid = pq[shortest_idx].getPid();
            pr.arr_time = pq[shortest_idx].getArrivalTime();
            pr.burst = pq[shortest_idx].getBurstTime();
            pr.comp_time = comp_time[shortest_idx];
            pr.turn_time = turn_time;
            pr.wait_time = wait_time;

            // Find the correct position in result.proc_results based on pid
            for (size_t i = 0; i < result.proc_results.size(); i++) {
                if (result.proc_results[i].pid == 0) {  // Empty slot
                    result.proc_results[i] = pr;
                    break;
                }
            }
        }
    }

    // Calculate averages
    double tot_turn = 0;
    double tot_wait = 0;

    for (const auto& pr : result.proc_results) {
        tot_turn += pr.turn_time;
        tot_wait += pr.wait_time;
    }

    result.avg_turn_time = tot_turn / n;
    result.avg_wait_time = tot_wait / n;

    return result;
}

std::string Scheduler::algToString(SchedAlg alg) {
    switch (alg) {
    case SchedAlg::FCFS:
        return "First-Come, First-Served (FCFS)";
    case SchedAlg::SJF_NP:
        return "Shortest Job First (SJF) - Non-preemptive";
    case SchedAlg::SJF_P:
        return "Shortest Job First (SJF) - Preemptive";
    default:
        return "Unknown Algorithm";
    }
}

void Scheduler::printSchedResult(const SchedResult& result, SchedAlg alg) {
    std::cout << "\n=== " << algToString(alg) << " Scheduling Results ===\n";
    std::cout << "PID\tArr\tBurst\tComp\tTurn\tWait\n";

    for (const auto& pr : result.proc_results) {
        std::cout << pr.pid << "\t"
            << pr.arr_time << "\t"
            << pr.burst << "\t"
            << pr.comp_time << "\t"
            << pr.turn_time << "\t"
            << pr.wait_time << "\n";
    }

    std::cout << "\nAvg Turnaround Time: " << result.avg_turn_time << "\n";
    std::cout << "Avg Waiting Time: " << result.avg_wait_time << "\n";
}

void Scheduler::printGantt(const SchedResult& result) {
    std::cout << "\n=== Gantt Chart ===\n";

    // Print top border
    std::cout << " ";
    for (size_t i = 0; i < result.gantt.size(); i++) {
        std::cout << "--------";
    }
    std::cout << "\n";

    // Print process IDs
    std::cout << "|";
    for (const auto& entry : result.gantt) {
        std::cout << "   P" << entry.first << "   |";
    }
    std::cout << "\n";

    // Print bottom border
    std::cout << " ";
    for (size_t i = 0; i < result.gantt.size(); i++) {
        std::cout << "--------";
    }
    std::cout << "\n";

    // Print timeline
    std::cout << result.gantt[0].second;
    for (const auto& entry : result.gantt) {
        std::cout << "        " << entry.second;
    }
    std::cout << "\n";
}
