# Project Part 1 - Building a Basic Operating System

## Team Members
- Elian Esparza
- Jair Aguirre

## Project Overview
This project is the first part of a multi-part assignment to design and implement a simplified operating system simulator using C++. In this phase, we establish the project foundation by:
- Setting up a GitHub repository for collaborative development.
- Creating a basic program structure.
- Simulating the boot-up process.
- Implementing a simple authentication function (using hardcoded credentials).

## Features
- **Boot-Up Process:**  
  The program simulates an OS boot sequence by displaying startup messages with timed delays.
- **Authentication Function:**  
  The program prompts the user to enter a username and password. It then verifies the input against the hardcoded credentials (username: `admin`, password: `password123`) and displays a success or failure message.

## Setup and Running Instructions

### Prerequisites
- A C++ compiler that supports C++17.
- Git (for cloning the repository).

### Steps
1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd <repository_directory>
   
## Part 2: Process Representation

In Part 2, we extend our OS simulator by adding a `Process` class that represents an operating system process. This class is essential for simulating process scheduling and management in our simulator.

### Process Class Overview

The `Process` class encapsulates key attributes of an OS process:
- **Process ID (pid):** A unique identifier for each process.
- **Arrival Time:** The time when the process enters the system.
- **Burst Time:** The total CPU time required for the process to complete.
- **Priority:** The importance of the process relative to others.
- **State:** The current state of the process, represented by an `enum class ProcessState` with values:
  - `NEW`: Process is newly created.
  - `READY`: Process is ready to execute.
  - `RUNNING`: Process is currently executing.
  - `WAITING`: Process is waiting for an event (e.g., I/O).
  - `TERMINATED`: Process has completed execution.
- **Remaining Time:** The amount of CPU time left for the process to finish.
- **Waiting Time:** The total time the process spends waiting in the ready queue.
- **Turnaround Time:** The overall time from process arrival to its completion.
- **Memory Required:** The memory needed by the process.
- **I/O Operations:** (Optional) A list of I/O operations the process will perform.

### Key Methods

- **Constructor:**  
  Initializes all the process attributes. It sets the initial state to `NEW`, assigns the burst time to remaining time, and defaults I/O operations to an empty list if none are provided.
- **Setters and Getters:**  
  Allow controlled access and updates to process attributes.
- **State Update and Execution Simulation:**  
  A method to decrement the remaining execution time. When the remaining time reaches zero, the process state is updated to `TERMINATED`.

### Why This Matters

Implementing the `Process` class lays the foundation for future enhancements in our OS simulator, such as:
- Implementing different scheduling algorithms (e.g., round-robin, priority-based).
- Managing process state transitions.
- Incorporating memory management and I/O handling.

## Part 3: Process Scheduling Simulation – FCFS and SJF

In Part 3, we implement process scheduling algorithms to simulate how an operating system allocates CPU time to different processes. We focus on two fundamental scheduling algorithms: First-Come, First-Served (FCFS) and Shortest Job First (SJF) in both preemptive and non-preemptive variants.

### Scheduling Algorithms Implemented

1. **First-Come, First-Served (FCFS)**
   - The simplest scheduling algorithm that executes processes in the order they arrive
   - Non-preemptive by nature
   - Easy to implement but can lead to the "convoy effect" where short processes wait behind long ones

2. **Shortest Job First (SJF) - Non-preemptive**
   - Selects the process with the shortest burst time among all ready processes
   - Once a process starts executing, it runs to completion without interruption
   - Optimal for minimizing average waiting time when all processes are available simultaneously

3. **Shortest Job First (SJF) - Preemptive (also known as Shortest Remaining Time First)**
   - Similar to non-preemptive SJF, but allows interruption when a new process with shorter burst time arrives
   - The currently running process is preempted if a newly arrived process has a shorter remaining time
   - Provides better response times for short processes

### Key Components

- **Scheduler Class**: Manages the scheduling algorithms and process execution
- **Process Results**: Tracks performance metrics for each process
- **Scheduling Results**: Aggregates metrics across all processes for a given algorithm
- **Gantt Chart Visualization**: Displays the execution timeline for better understanding

### Performance Metrics

For each scheduling algorithm, we calculate and compare:
- **Completion Time**: When each process finishes execution
- **Turnaround Time**: Total time from arrival to completion (Completion Time - Arrival Time)
- **Waiting Time**: Time spent waiting in the ready queue (Turnaround Time - Burst Time)
- **Average Turnaround Time**: Mean turnaround time across all processes
- **Average Waiting Time**: Mean waiting time across all processes

### Implementation Details

The implementation uses a modular approach with the following structure:
- `SchedAlg` enum class: Defines the supported scheduling algorithms
- `ProcResult` struct: Stores individual process metrics
- `SchedResult` struct: Aggregates results and statistics
- `Scheduler` class: Implements the core scheduling logic

### Significance in OS Design

Process scheduling is a fundamental aspect of operating system design that directly impacts:
- System throughput
- CPU utilization
- Process response times
- Overall system efficiency

By implementing and comparing different scheduling algorithms, we gain insights into their strengths, weaknesses, and appropriate use cases in real operating systems.

### Updated Compilation and Running Instructions

To compile the complete project (Parts 1, 2 & 3), use:
```bash
g++ -std=c++17 main.cpp auth.cpp system.cpp process.cpp scheduler.cpp -o os_simulator
