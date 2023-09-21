# OSP_Assignment2
Operating System Principles Assignment 2

Datafile:
seeding with random seed of 3961769648780


To help you with this we have provided a PCB (process control block) class that contains information 
about an individual process and its progress. The following is a recommended design for your 
program:
• A launcher/driver .cpp that parses command line arguments.
• A simulator class that runs the simulation.
• A loader class to load data from the input file.
• A PCB class. You can modify it as needed.

Your programs are expected to produce the following output on the screen:
1. For each process: Process ID, burst time, turnaround time, waiting time, and response time.
2. For all processes: Average turnaround time, average waiting time, and average response time.

Response time is the amount of time it takes for the CPU to respond to a request made by a process. It is the duration between the arrival of a process and the first time it runs.

The time elapsed between the arrival of a process and its completion is known as turnaround time.