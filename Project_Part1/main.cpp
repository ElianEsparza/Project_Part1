#include <iostream>
#include "system.h"
#include "auth.h"
#include "process.h"
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

int main() {
    bootUp();

    if (authenticateUser()) {
        cout << "Access granted. Starting OS...\n";
    }
    else {
        cout << "Access denied. Shutting down.\n";
        return 1;
    }

    cout << "\n--- Process Scheduling Test ---\n";

    // Parameters: pid, arrival_time, burst_time, priority, memory_required
    Process p1(1, 0, 100, 1, 512);
    Process p2(2, 5, 150, 2, 1024);

    //initial state (should be NEW).
    cout << "Process " << p1.getPid() << " initial state: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " initial state: " << stateToString(p2.getState()) << "\n\n";

    this_thread::sleep_for(chrono::milliseconds(40));
    // Update to READY.
    p1.setState(ProcessState::READY);
    p2.setState(ProcessState::READY);
    cout << "Process " << p1.getPid() << " state updated to: " << stateToString(p1.getState()) << "\n";
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";

    this_thread::sleep_for(chrono::milliseconds(40));
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

    this_thread::sleep_for(chrono::milliseconds(60));
    // process 2
    // set wait time
    p2.setWaitingTime(10);
    cout << "Process " << p2.getPid() << " waiting time set to: " << p2.getWaitingTime() << "\n";

    // p2 to RUNNING.
    p2.setState(ProcessState::RUNNING);
    cout << "Process " << p2.getPid() << " state updated to: " << stateToString(p2.getState()) << "\n\n";

    this_thread::sleep_for(chrono::milliseconds(40));
    // run Process 2 in one go.
    p2.decrementRemainingTime(150);
    cout << "Process " << p2.getPid() << " remaining time after execution: "
        << p2.getRemainingTime() << "\n";

    // Set turnaround time as an example (waiting time + burst time).
    p2.setTurnaroundTime(p2.getWaitingTime() + p2.getBurstTime());
    cout << "Process " << p2.getPid() << " turnaround time: " << p2.getTurnaroundTime() << "\n";
    cout << "Process " << p2.getPid() << " final state: " << stateToString(p2.getState()) << "\n";


    return 0;
}
