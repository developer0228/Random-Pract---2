// Implement the C program for CPU Scheduling Algorithms: Shortest Job First 
// (Preemptive ) with different arrival time.

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Process structure to hold details of each process
typedef struct {
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
} Process;

// Comparison function to sort by arrival time
int compare_arrival(const void *a, const void *b) {
    return ((Process*)a)->arrival_time - ((Process*)b)->arrival_time;
}

int main() {
    int n, current_time = 0, completed = 0;
    Process p[MAX];
    
    printf("By Onkar - T1905308657\n");
    
    // Input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input details for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    // Sort processes by arrival time
    qsort(p, n, sizeof(Process), compare_arrival);

    // Preemptive SJF scheduling
    while (completed < n) {
        int idx = -1, min_burst = 999999;
        
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_burst) {
                min_burst = p[i].remaining_time;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        // Execute the selected process for 1 unit of time
        p[idx].remaining_time--;
        current_time++;

        // If the process has finished
        if (p[idx].remaining_time == 0) {
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            completed++;
        }
    }

    // Output the result
    printf("\nID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    float avg_waiting = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time, 
            p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
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
// Enter arrival and burst time for process 1: 0 5
// Enter arrival and burst time for process 2: 2 3
// Enter arrival and burst time for process 3: 4 2
// Enter arrival and burst time for process 4: 6 1

// ID  Arrival  Burst   Completion   Turnaround   Waiting
// 1    0        5       12           12           7
// 2    2        3       9            7            4
// 3    4        2       7            3            1
// 4    6        1       8            2            1

// Average Waiting Time: 3.25
// Average Turnaround Time: 6.00
