// Implement the C program for Disk Scheduling Algorithms: SCAN considering the 
// initial head position moving away from the spindle.

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void scan(int requests[], int n, int initial, int direction) {
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

    // Move in the specified direction
    if (direction == 1) { // Moving towards higher numbers
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current) {
                total_seek += abs(current - requests[i]);
                current = requests[i];
                completed[i] = 1;
                printf("Served request: %d, Current head position: %d\n", current, current);
            }
        }
        // Move to the end and then back to the lowest request
        total_seek += abs(current - requests[n - 1]);
        current = requests[n - 1];

        // Serve remaining requests in reverse
        for (int i = n - 1; i >= 0; i--) {
            if (!completed[i]) {
                total_seek += abs(current - requests[i]);
                current = requests[i];
                printf("Served request: %d, Current head position: %d\n", current, current);
            }
        }
    }

    printf("Total seek time: %d\n", total_seek);
    printf("By Onkar - T1905308657\n");
}

int main() {
    int requests[MAX_REQUESTS], n, initial, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial);
    printf("Enter direction (1 for up, -1 for down): ");
    scanf("%d", &direction);

    scan(requests, n, initial, direction);

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
// Enter direction (1 for up, -1 for down): 1

// Served request: 100, Current head position: 100
// Served request: 180, Current head position: 180
// Served request: 200, Current head position: 200
// Served request: 50, Current head position: 50
// Served request: 30, Current head position: 30
// Total seek time: 130
// By Onkar - T1905308657