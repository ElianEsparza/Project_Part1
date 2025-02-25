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
In Part 2, we extend our OS simulator by adding a `Process` class that represents an operating system process. This class includes attributes such as:
- **Process ID (pid)**
- **Arrival Time**
- **Burst Time**
- **Priority**
- **State** (using an enum: NEW, READY, RUNNING, WAITING, TERMINATED)
- **Remaining Time**
- **Waiting Time**
- **Turnaround Time**
- **Memory Required**
- **I/O Operations** (optional)

The `Process` class also provides methods to update its state and decrement its remaining execution time, forming the basis for process scheduling and state transitions.
