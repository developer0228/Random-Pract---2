// Implement the C program forDeadlock Avoidance Algorithm: Bankers Algorithm

#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

int available[R], max[P][R], allocated[P][R], need[P][R];
int finish[P] = {0};  // To track finished processes

// Function to check if a process can be safely executed
bool isSafe() {
    int work[R];
    for (int i = 0; i < R; i++) work[i] = available[i];  // Available resources

    while (1) {
        int i;
        bool progressMade = false;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canProceed = 1;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = 0;
                        break;
                    }
                }
                if (canProceed) {
                    for (int j = 0; j < R; j++) work[j] += allocated[i][j]; // Allocate resources to process
                    finish[i] = 1;
                    progressMade = true;
                    break;
                }
            }
        }
        if (!progressMade) break;  // No progress can be made, exit loop
    }

    for (int i = 0; i < P; i++) if (!finish[i]) return false;  // If any process is not finished
    return true;  // System is in a safe state
}

int main() {
    // Input print statement
    printf("By Onkar - T1905308657\n");

    // Initializing resources
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++) scanf("%d", &available[i]);

    // Initializing max matrix (maximum demand of each process)
    printf("Enter maximum resources for each process: \n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j];  // Initially need = max demand
        }
    }

    // Initializing allocated matrix (resources already allocated to each process)
    printf("Enter allocated resources for each process: \n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocated[i][j]);
            need[i][j] -= allocated[i][j];  // Adjust need matrix after allocation
        }
    }

    // Checking for a safe sequence
    if (isSafe()) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}


// OUTPUT
// By Onkar - T1905308657
// Enter available resources: 3 2 2
// Enter maximum resources for each process: 
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter allocated resources for each process: 
// 2 1 1
// 1 1 1
// 2 0 1
// 1 1 1
// 1 1 1
// System is in a safe state.
