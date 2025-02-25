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

### Updated Compilation and Running Instructions

To compile the complete project (Parts 1 & 2), use:
```bash
g++ -std=c++17 main.cpp auth.cpp system.cpp process.cpp -o os_simulator

