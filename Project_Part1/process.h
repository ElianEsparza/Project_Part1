#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
private:
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    ProcessState state;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int memory_required;
    std::vector<std::string> io_operations;

public:
    Process(int pid, int arrival_time, int burst_time, int priority, int memory_required,
        const std::vector<std::string>& io_operations = {});


    int getPid() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    ProcessState getState() const;
    int getRemainingTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getMemoryRequired() const;
    std::vector<std::string> getIoOperations() const;


    void setState(ProcessState newState);
    void setWaitingTime(int waiting_time);
    void setTurnaroundTime(int turnaround_time);


    void decrementRemainingTime(int time);
};

std::string stateToString(ProcessState state);

#endif 
