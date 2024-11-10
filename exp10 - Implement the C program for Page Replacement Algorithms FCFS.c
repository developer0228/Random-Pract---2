// Implement the C program for Page Replacement Algorithms: FCFS for frame size as 
// minimum three.

#include <stdio.h>

#define FRAME_SIZE 3

void pageReplacement(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1, -1, -1}; // Frame initialized to -1 (empty)
    int pageFaults = 0, index = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in one of the frames
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not found, replace the oldest page (FCFS)
        if (!found) {
            frames[index] = page;
            index = (index + 1) % FRAME_SIZE;  // Circular increment for frame index
            pageFaults++;
        }

        // Print the current state of frames
        printf("Frames: ");
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("X ");  // X indicates empty space
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4};  // Example page reference string
    int n = sizeof(pages) / sizeof(pages[0]);

    // Print the required statement
    printf("By Onkar - T1905308657\n");

    pageReplacement(pages, n);
    return 0;
}



// OUTPUT
// By Onkar - T1905308657
// Frames: 7 X X 
// Frames: 7 0 X 
// Frames: 7 0 1 
// Frames: 2 0 1 
// Frames: 2 0 1 
// Frames: 2 0 3 
// Frames: 2 0 3 
// Frames: 4 0 3 

// Total Page Faults: 6
