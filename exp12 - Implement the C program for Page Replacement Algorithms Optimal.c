// Implement the C program for Page Replacement Algorithms: Optimal for frame size 
// as minimum three.

#include <stdio.h>

#define FRAME_SIZE 3

// Function to find the optimal page replacement index
int findOptimalPage(int frames[], int n, int pages[], int currentIndex) {
    int farthest = -1, indexToReplace = -1;

    for (int i = 0; i < FRAME_SIZE; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        if (j == n) return i;  // If the page is not found in future, replace it
    }
    return indexToReplace;
}

void pageReplacement(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1, -1, -1}; // Initialize frames to -1 (empty)
    int pageFaults = 0;

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

        // If the page is not found, we have a page fault
        if (!found) {
            pageFaults++;
            int replaceIndex = -1;
            // If there is space in memory, insert the page
            for (int j = 0; j < FRAME_SIZE; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty space, use the optimal page replacement strategy
            if (replaceIndex == -1) {
                replaceIndex = findOptimalPage(frames, n, pages, i + 1);
            }

            frames[replaceIndex] = page;  // Replace the page
        }

        // Print current state of frames
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
// Frames: 0 2 3 
// Frames: 4 2 3 

// Total Page Faults: 6
