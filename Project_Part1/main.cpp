#include <iostream>
#include "system.h"
#include "auth.h"
#include "process.h"
#include "scheduler.h"
#include <vector>
#include <iomanip>
using namespace std;

// Function to demonstrate the original process management
void demoOrigProc() {
    cout << "\n--- Original Process Management Demo ---\n";

    // Parameters: pid, arrival_time, burst_time, priority, memory_required
    Process p1(1, 0, 100, 1, 512);
    Process p2(2, 5, 150, 2, 1024);

    //initial state (should be NEW).
    cout << "Process " << p1.getPid() << " initial state: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " initial state: " << stateToString(p2.getState()) << "\n\n";

    // Update to READY.
    p1.setState(ProcessState::READY);
    p2.setState(ProcessState::READY);
    cout << "Process " << p1.getPid() << " state updated to: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";

    //process 1
    //to RUNNING
    p1.setState(ProcessState::RUNNING);
    cout << "Process " << p1.getPid() << " state updated to: " << stateToString(p1.getState()) << "\n";

    // Run Process 1: decrement 50 time units etc
    p1.decrementRemainingTime(50);
    cout << "Process " << p1.getPid() << " remaining time after 50 time units: "
        << p1.getRemainingTime() << "\n";
    p1.decrementRemainingTime(50);
    cout << "Process " << p1.getPid() << " remaining time after another 50 time units: "
        << p1.getRemainingTime() << "\n";

    //by now p1 should already be TERMINATED.
    cout << "Process " << p1.getPid() << " final state: " << stateToString(p1.getState()) << "\n\n";

    // process 2
    // set wait time
    p2.setWaitingTime(10);
    cout << "Process " << p2.getPid() << " waiting time set to: " << p2.getWaitingTime() << "\n";

    // p2 to RUNNING.
    p2.setState(ProcessState::RUNNING);
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";

    // run Process 2 in one go.
    p2.decrementRemainingTime(150);
    cout << "Process " << p2.getPid() << " remaining time after execution: "
        << p2.getRemainingTime() << "\n";

    // Set turnaround time as an example (waiting time + burst time).
    p2.setTurnaroundTime(p2.getWaitingTime() + p2.getBurstTime());
    cout << "Process " << p2.getPid() << " turnaround time: " << p2.getTurnaroundTime() << "\n";
    cout << "Process " << p2.getPid() << " final state: " << stateToString(p2.getState()) << "\n";
}

// Function to create a set of test processes for scheduling algorithms
vector<Process> createTestProcs() {
    vector<Process> procs;

    // Parameters: pid, arrival_time, burst_time, priority, memory_required
    procs.push_back(Process(1, 0, 6, 1, 512));
    procs.push_back(Process(2, 1, 8, 2, 1024));
    procs.push_back(Process(3, 2, 7, 1, 512));
    procs.push_back(Process(4, 3, 3, 3, 2048));
    procs.push_back(Process(5, 4, 4, 2, 1024));

    return procs;
}

// Function to demonstrate scheduling algorithms
void demoSchedAlgs() {
    cout << "\n--- Process Scheduling Algorithms Demo ---\n";

    vector<Process> procs = createTestProcs();

    // Display process information
    cout << "\nProcess Information:\n";
    cout << "PID\tArr\tBurst\tPri\tMem\n";
    for (const auto& p : procs) {
        cout << p.getPid() << "\t"
            << p.getArrivalTime() << "\t"
            << p.getBurstTime() << "\t"
            << p.getPriority() << "\t"
            << p.getMemoryRequired() << " KB\n";
    }

    // Create schedulers for each algorithm
    Scheduler fcfs(procs, SchedAlg::FCFS);
    Scheduler sjf_np(procs, SchedAlg::SJF_NP);
    Scheduler sjf_p(procs, SchedAlg::SJF_P);

    // Run each algorithm
    SchedResult fcfs_res = fcfs.run();
    SchedResult sjf_np_res = sjf_np.run();
    SchedResult sjf_p_res = sjf_p.run();

    // Print results for each algorithm
    Scheduler::printSchedResult(fcfs_res, SchedAlg::FCFS);
    Scheduler::printGantt(fcfs_res);

    Scheduler::printSchedResult(sjf_np_res, SchedAlg::SJF_NP);
    Scheduler::printGantt(sjf_np_res);

    Scheduler::printSchedResult(sjf_p_res, SchedAlg::SJF_P);
    Scheduler::printGantt(sjf_p_res);

    // Compare algorithms
    cout << "\n=== Algorithm Comparison ===\n";
    cout << setw(40) << "Algorithm" << setw(25) << "Avg Turn Time" << setw(20) << "Avg Wait Time\n";
    cout << setw(40) << Scheduler::algToString(SchedAlg::FCFS)
        << setw(25) << fcfs_res.avg_turn_time
        << setw(20) << fcfs_res.avg_wait_time << "\n";
    cout << setw(40) << Scheduler::algToString(SchedAlg::SJF_NP)
        << setw(25) << sjf_np_res.avg_turn_time
        << setw(20) << sjf_np_res.avg_wait_time << "\n";
    cout << setw(40) << Scheduler::algToString(SchedAlg::SJF_P)
        << setw(25) << sjf_p_res.avg_turn_time
        << setw(20) << sjf_p_res.avg_wait_time << "\n";
}

int main() {
    bootUp();

    if (authenticateUser()) {
        cout << "Access granted. Starting OS...\n";
    }
    else {
        cout << "Access denied. Shutting down.\n";
        return 1;
    }

    // Demonstrate original process management
    demoOrigProc();

    // Demonstrate scheduling algorithms
    demoSchedAlgs();

    return 0;
}
