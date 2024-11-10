//  Implement the C program for Disk Scheduling Algorithms: SSTF considering the 
// initial head position moving away from the spindle

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sstf(int requests[], int n, int initial) {
    int completed[MAX_REQUESTS] = {0}; // Track completed requests
    int current = initial, total_seek = 0;

    for (int i = 0; i < n; i++) {
        int min_distance = __INT_MAX__, index = -1;

        // Find the closest request
        for (int j = 0; j < n; j++) {
            if (!completed[j]) {
                int distance = abs(requests[j] - current);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }

        // Move to the closest request
        if (index != -1) {
            total_seek += min_distance;
            current = requests[index];
            completed[index] = 1; // Mark as completed
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

    sstf(requests, n, initial);

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
// Served request: 50, Current head position: 50
// Served request: 30, Current head position: 30
// Total seek time: 130
// By Onkar - T1905308657