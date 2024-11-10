// Implement the C program for CPU Scheduling Algorithms: Round Robin with 
// different arrival time.


#include <stdio.h>

#define MAX 10

// Process structure to hold details of each process
typedef struct {
    int id, arrival_time, burst_time, remaining_time, waiting_time, turnaround_time;
} Process;

int main() {
    int n, quantum, time = 0, completed = 0;
    Process p[MAX];

    printf("By Onkar - T1905308657\n");

    // Input number of processes and time quantum
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    // Round Robin Scheduling
    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0) {
                executed = 1;

                // Run the process for the time quantum
                int run_time = p[i].remaining_time < quantum ? p[i].remaining_time : quantum;
                p[i].remaining_time -= run_time;
                time += run_time;

                // If process finishes
                if (p[i].remaining_time == 0) {
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    completed++;
                }
            }
        }

        // If no process is executed, advance time
        if (!executed) {
            time++;
        }
    }

    // Print results
    printf("\nID Arrival Burst Turnaround Waiting\n");
    float avg_waiting = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        printf("%d   %d      %d     %d        %d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].waiting_time);
        avg_waiting += p[i].waiting_time;
        avg_turnaround += p[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);

    return 0;
}


// OUTPUT
// By Onkar - T1905308657
// Enter number of processes: 4
// Enter time quantum: 2
// Enter arrival and burst time for process 1: 0 4
// Enter arrival and burst time for process 2: 2 6
// Enter arrival and burst time for process 3: 4 3
// Enter arrival and burst time for process 4: 6 5

// ID Arrival Burst Turnaround Waiting
// 1   0      4     10        6
// 2   2      6     16        10
// 3   4      3     10        7
// 4   6      5     20        14

// Average Waiting Time: 9.25
// Average Turnaround Time: 13.00
