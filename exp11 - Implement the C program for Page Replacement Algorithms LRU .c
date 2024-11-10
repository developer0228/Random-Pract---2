// Implement the C program for Page Replacement Algorithms: LRU for frame size as 
// minimum three.

#include <stdio.h>

#define FRAME_SIZE 3

void pageReplacement(int pages[], int n) {
    int frames[FRAME_SIZE] = {-1, -1, -1};  // Frame initialized to -1 (empty)
    int pageFaults = 0;

    // Iterate over the page reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0, lruIndex = -1;

        // Check if the page is already in one of the frames
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                found = 1;  // Page is already in memory, no fault
                break;
            }
        }

        // If the page is not found, we have a page fault
        if (!found) {
            pageFaults++;
            // Find the least recently used page (LRU)
            for (int j = 0; j < FRAME_SIZE; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;  // Place the new page in an empty slot
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // All frames are full, so replace the LRU page (the first slot)
                for (int j = 0; j < FRAME_SIZE - 1; j++) {
                    frames[j] = frames[j + 1];  // Shift pages left
                }
                frames[FRAME_SIZE - 1] = page;  // Insert the new page in the last frame
            }
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


// output
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
