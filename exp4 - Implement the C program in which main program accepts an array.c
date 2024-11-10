
// Implement the C program in which main program accepts an array. Main program 
// uses the FORK system call to create a new process called a child process. Parent 
// process sorts an array and passes the sorted array to child process through the 
// command line arguments of EXECVE system call. The child process uses EXECVE 
// system call to load new program which display array in reverse order.
// =========================================================================`
// ########## Main Parent

//  Make File as nano main.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 100

// Bubble Sort Function
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

int main() {
    int n;
    printf("By Onkar - T1905308657\n");

    // Accept the number of integers
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Array size exceeds maximum limit.\n");
        return 1;
    }

    int arr[n];
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sorting the array in the parent process
    bubble_sort(arr, n);

    // Convert the sorted array to string arguments for execve
    char *args[n + 2];  // +2: one for program name, one for NULL terminator
    args[0] = "./reverse";  // Path to the child program (reverse.c)
    
    // Convert array integers to strings for command line arguments
    for (int i = 0; i < n; i++) {
        args[i + 1] = malloc(20 * sizeof(char));  // Allocate space for each argument
        sprintf(args[i + 1], "%d", arr[i]);  // Convert int to string
    }

    args[n + 1] = NULL;  // NULL terminator for execve arguments

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Executing the reverse program with execve
        if (execve(args[0], args, NULL) == -1) {
            perror("execve failed");
            exit(1);
        }
    } else {  // Parent process
        // Wait for the child to finish execution
        wait(NULL);
    }

    // Free allocated memory for arguments
    for (int i = 1; i <= n; i++) {
        free(args[i]);
    }

    return 0;
}


// ----------------------------------------------------------

// Reverser - Child Process

// Make File as nano reverse.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No array passed.\n");
        return 1;
    }

    printf("Array in reverse order: ");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}

// output
// By Onkar - T1905308657
// Enter the number of integers: 5
// Enter the integers: 9 2 5 1 8

// Array sorted in parent: 1 2 5 8 9
