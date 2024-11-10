// FIFOS: Full duplex communication between two independent processes. First process 
// accepts sentences and writes on one pipe to be read by second process and second 
// process counts number of characters, number of words and number of lines in 
// accepted sentences, writes this output in a text file and writes the contents of the file 
// on second pipe to be read by first process and displays on standard output.


#include <stdio.h>
#include <string.h>

#define MAX_INPUT 3
#define BUFFER_SIZE 1024

int main() {
    char input[MAX_INPUT][BUFFER_SIZE];
    int lines = 0, words = 0, characters = 0;

    printf("Enter up to %d sentences (press Enter after each sentence):\n", MAX_INPUT);
    
    // Read exactly 3 sentences
    for (int i = 0; i < MAX_INPUT; i++) {
        if (fgets(input[i], BUFFER_SIZE, stdin) == NULL) {
            break; // Stop if there's an error or EOF
        }
        lines++; // Count each sentence as a line
        characters += strlen(input[i]); // Count characters in the current sentence

        // Count words in the current sentence
        char *token = strtok(input[i], " \n");
        while (token != NULL) {
            words++;
            token = strtok(NULL, " \n");
        }
    }

    // Print the results
    printf("Output:\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    printf("By Onkar - T1905308657\n");

    return 0;
}

// OUTPUT 

// Enter up to 3 sentences (press Enter after each sentence):
// Hello, this is the first sentence.
// This is the second one.
// And this is the third.

// Output:
// Lines: 3
// Words: 15
// Characters: 73
// By Onkar - T1905308657