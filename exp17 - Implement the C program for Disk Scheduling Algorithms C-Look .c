// Implement the C program for Disk Scheduling Algorithms: C-Look considering the 
// initial head position moving away from the spindle.

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void clook(int requests[], int n, int initial) {
    int total_seek = 0, current = initial;
    int completed[MAX_REQUESTS] = {0}; // Track completed requests

    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Serve requests in C-LOOK manner
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            total_seek += abs(current - requests[i]);
            current = requests[i];
            printf("Served request: %d, Current head position: %d\n", current, current);
        }
    }

    // Jump to the first request after completing the last request
    if (current < requests[n - 1]) {
        total_seek += abs(current - requests[0]);
        current = requests[0];
        printf("Served request: %d, Current head position: %d\n", current, current);
    }

    // Serve remaining requests
    for (int i = 0; i < n; i++) {
        if (requests[i] >= current) {
            total_seek += abs(current - requests[i]);
            current = requests[i];
            printf("Served request: %d, Current head position: %d\n", current, current);
        }
    }

    printf("Total seek time: %d\n", total_seek);
    printf("By Onkar - T1905308657\n");
}

int main() {
    int requests[MAX_REQUESTS], n, initial;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial);

    clook(requests, n, initial);

    return 0;
}



// OUTPUT 

// Enter the number of requests: 5
// Enter the requests:
// 100
// 180
// 30
// 50
// 200
// Enter the initial head position: 70


// Served request: 100, Current head position: 100
// Served request: 180, Current head position: 180
// Served request: 200, Current head position: 200
// Served request: 30, Current head position: 30
// Served request: 50, Current head position: 50
// Total seek time: 130
// By Onkar - T1905308657