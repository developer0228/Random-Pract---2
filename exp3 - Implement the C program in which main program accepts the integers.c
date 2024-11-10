
// Implement the C program in which main program accepts the integers to be sorted. 
// Main program uses the FORK system call to create a new process called a child 
// process. Parent process sorts the integers using sorting algorithm and waits for child 
// process using WAIT system call to sort the integers using any sorting algorithm. Also 
// demonstrate zombie and orphan states

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Sorting functions
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Function to print array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("By Onkar - T1905308657\n");

    // Accept the number of integers
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        printf("Child process sorting using Selection Sort:\n");
        selection_sort(arr, n);
        print_array(arr, n);
        printf("Child process exiting\n");
        // Simulate orphan process state (Parent exits before Child)
        exit(0);  // If we exit here, it could become orphan if parent exits early
    } else { // Parent process
        printf("Parent process sorting using Bubble Sort:\n");
        bubble_sort(arr, n);
        print_array(arr, n);

        // Wait for the child process to finish (demonstrate zombie state)
        wait(NULL);  // This waits for the child process to finish, avoiding zombie state
        printf("Parent process exiting\n");
        // If wait() was missing, child would remain in zombie state after it terminates
    }

    return 0;
}


// OUTPUT:
// By Onkar - T1905308657
// Enter the number of integers: 5
// Enter the integers: 5 2 9 1 5
// Parent process sorting using Bubble Sort:
// 1 2 5 5 9 
// Child process sorting using Selection Sort:
// 1 2 5 5 9 
// Child process exiting
// Parent process exiting
