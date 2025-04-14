#include <iostream>
#include "system.h"
#include "auth.h"
#include "process.h"
#include "scheduler.h"
#include "page_table.h"
#include "vm_manager.h"
#include "vm_config.h"
#include <vector>
#include <iomanip>
using namespace std;

// Function to demonstrate the original process management
void demoOrigProc() {
    cout << "\n--- Original Process Management Demo ---\n";

    // Create two processes (parameters: pid, arrival_time, burst_time, priority, memory_required)
    Process p1(1, 0, 100, 1, 512);
    Process p2(2, 5, 150, 2, 1024);

    // Display initial states (should be NEW)
    cout << "Process " << p1.getPid() << " initial state: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " initial state: " << stateToString(p2.getState()) << "\n\n";

    // Update state to READY
    p1.setState(ProcessState::READY);
    p2.setState(ProcessState::READY);
    cout << "Process " << p1.getPid() << " state updated to: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";

    // Transition process 1 to RUNNING and simulate execution
    p1.setState(ProcessState::RUNNING);
    cout << "Process " << p1.getPid() << " state updated to: " << stateToString(p1.getState()) << "\n";
    p1.decrementRemainingTime(50);
    cout << "Process " << p1.getPid() << " remaining time after 50 time units: " << p1.getRemainingTime() << "\n";
    p1.decrementRemainingTime(50);
    cout << "Process " << p1.getPid() << " remaining time after another 50 time units: " << p1.getRemainingTime() << "\n";
    cout << "Process " << p1.getPid() << " final state: " << stateToString(p1.getState()) << "\n\n";

    // Process 2: set waiting time, transition to RUNNING, and simulate complete execution
    p2.setWaitingTime(10);
    cout << "Process " << p2.getPid() << " waiting time set to: " << p2.getWaitingTime() << "\n";
    p2.setState(ProcessState::RUNNING);
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";
    p2.decrementRemainingTime(150);
    cout << "Process " << p2.getPid() << " remaining time after execution: " << p2.getRemainingTime() << "\n";
    p2.setTurnaroundTime(p2.getWaitingTime() + p2.getBurstTime());
    cout << "Process " << p2.getPid() << " turnaround time: " << p2.getTurnaroundTime() << "\n";
    cout << "Process " << p2.getPid() << " final state: " << stateToString(p2.getState()) << "\n";
}

// Function to create test processes for scheduling algorithms
vector<Process> createTestProcs() {
    vector<Process> procs;
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

    cout << "\nProcess Information:\n";
    cout << "PID\tArr\tBurst\tPri\tMem\n";
    for (const auto& p : procs) {
        cout << p.getPid() << "\t" << p.getArrivalTime() << "\t"
            << p.getBurstTime() << "\t" << p.getPriority() << "\t"
            << p.getMemoryRequired() << " KB\n";
    }

    Scheduler fcfs(procs, SchedAlg::FCFS);
    Scheduler sjf_np(procs, SchedAlg::SJF_NP);
    Scheduler sjf_p(procs, SchedAlg::SJF_P);

    SchedResult fcfs_res = fcfs.run();
    SchedResult sjf_np_res = sjf_np.run();
    SchedResult sjf_p_res = sjf_p.run();

    Scheduler::printSchedResult(fcfs_res, SchedAlg::FCFS);
    Scheduler::printGantt(fcfs_res);
    Scheduler::printSchedResult(sjf_np_res, SchedAlg::SJF_NP);
    Scheduler::printGantt(sjf_np_res);
    Scheduler::printSchedResult(sjf_p_res, SchedAlg::SJF_P);
    Scheduler::printGantt(sjf_p_res);

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
    // Boot up the OS simulator
    bootUp();

    // Authenticate the user (username: "admin", password: "password123")
    if (!authenticateUser()) {
        cout << "Access denied. Shutting down.\n";
        return 1;
    }
    cout << "Access granted. Starting OS...\n";

    // Demonstrate original process management
    demoOrigProc();

    // Demonstrate process scheduling algorithms
    demoSchedAlgs();

    // Virtual Memory Simulation Test
    cout << "\n--- Virtual Memory Simulation Test ---\n";
    PageTable pageTable;
    VirtualMemoryManager vmManager(&pageTable);

    // Test with a sample virtual address (e.g., 8192 = page 2, offset 0)
    size_t virtualAddress = 8192;
    size_t physicalAddress;
    if (vmManager.translateAddress(virtualAddress, physicalAddress)) {
        cout << "Virtual address " << virtualAddress << " translated to physical address " << physicalAddress << "\n";
    }
    else {
        cout << "Failed to translate virtual address " << virtualAddress << "\n";
    }

    return 0;
}
