#include "process.h"

// Constructor implementation
Process::Process(int pid, int arrival_time, int burst_time, int priority, int memory_required,
    const std::vector<std::string>& io_operations)
    : pid(pid),
    arrival_time(arrival_time),
    burst_time(burst_time),
    priority(priority),
    state(ProcessState::NEW),
    remaining_time(burst_time),
    waiting_time(0),
    turnaround_time(0),
    memory_required(memory_required),
    io_operations(io_operations)
{
}

// Getters
int Process::getPid() const {
    return pid;
}

int Process::getArrivalTime() const {
    return arrival_time;
}

int Process::getBurstTime() const {
    return burst_time;
}

int Process::getPriority() const {
    return priority;
}

ProcessState Process::getState() const {
    return state;
}

std::string stateToString(ProcessState state) {
    switch (state) {
    case ProcessState::NEW:        return "NEW";
    case ProcessState::READY:      return "READY";
    case ProcessState::RUNNING:    return "RUNNING";
    case ProcessState::WAITING:    return "WAITING";
    case ProcessState::TERMINATED: return "TERMINATED";
    default:                       return "UNKNOWN";
    }
}

int Process::getRemainingTime() const {
    return remaining_time;
}

int Process::getWaitingTime() const {
    return waiting_time;
}

int Process::getTurnaroundTime() const {
    return turnaround_time;
}

int Process::getMemoryRequired() const {
    return memory_required;
}

std::vector<std::string> Process::getIoOperations() const {
    return io_operations;
}

// Setters
void Process::setState(ProcessState newState) {
    state = newState;
}

void Process::setWaitingTime(int wt) {
    waiting_time = wt;
}

void Process::setTurnaroundTime(int tt) {
    turnaround_time = tt;
}


void Process::decrementRemainingTime(int time) {
    if (time < 0)
        return;
    remaining_time -= time;
    if (remaining_time < 0)
        remaining_time = 0;

    if (remaining_time == 0) {
        state = ProcessState::TERMINATED;
    }
}
