
# Operating System Scheduling algorithms 

In the world of operating systems, there are some algorithms to schedule processes to enter the CPU. These algorithms are either non-preemptive or preemptive. Non-preemptive algorithms are designed so that once a process enters the running state, it cannot be preempted until it completes its allotted time, whereas the preemptive scheduling is based on priority where a scheduler may preempt a low priority running process anytime when a high priority process enters into a ready state.

### I have written a code contains four functions, each representing an algorithm which I'm going to talk about.

#### First-Come, First-Served (FCFS)
- Start jobs in the order they arrive.
- Run each job until completion.
- Non-Preemptive.
sample input:
```
Process Arrival  Processing 
        Time     Time
p1      0        3
p2      2        6
p3      4        4
p4      6        5
p5      8        2
```
sample output:
```
Process  Start  End  Turnaround  Delay
p1       0      3       3        0
p2       3      9       7        1
p3       9      13      9        5
p4       13     18      12       7
p5       18     20      12       10
```
#### Shortest Job First (SJF)
- Select the job with the shortest (expected) running time.
- Best approach to minimize waiting time.
- Non-Preemptive.
sample input:
```
Process Arrival  Processing 
        Time     Time
p1      0        3
p2      2        6
p3      4        4
p4      6        5
p5      8        2
```
sample output:
```
Process  Start  End  Turnaround  Delay
p1      0       3       3        0
p2      3       9       7        1
p3      11      15      11       7
p4      15      20      14       9
p5      9       11      3        1
```
#### Shortest Remaining Time (SRT)
- Preemptive version of the SJF algorithm.
- The processor is allocated to the job closest to completion but it can be preempted by a newer ready job with shorter time to completion.
sample input:
```
Process Arrival  Processing 
        Time     Time
p1      0        3
p2      2        6
p3      4        4
p4      6        5
p5      8        2
```
sample output:
```
Process  Start  End  Turnaround  Delay
p1      0       3       3        0
p2      3       15      13       7
p3      4       8       4        0
p4      15      20      14       9
p5      8       10      2        0
```
#### Round Robin (RR)
- Round Robin is the preemptive process scheduling algorithm.
- Each process is provided a fix time to execute, it is called a quantum.
- Once a process is executed for a given time period, it is preempted and other process executes for a given time period.
- Context switching is used to save states of preempted processes.
sample input:
```
Process Arrival  Processing 
        Time     Time
p1      0        3
p2      2        6
p3      4        4
p4      6        5
p5      8        2
and time quantum = 1
```
sample output:
```
Process  Start  End  Turnaround  Delay
p1      0      4        4        1
p2      2      18       16       10
p3      5      17       13       9
p4      7      20       14       9
p5      10     15       7        5
```

