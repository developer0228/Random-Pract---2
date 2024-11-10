//  Inter-process Communication using Shared Memory using System V. Application to 
// demonstrate: Client and Server Programs in which server process creates a shared 
// memory segment and writes the message to the shared memory segment. Client 
// process reads the message from the shared memory segment and displays it to the 
// screen.

// Make: nano server.c
// gcc -o server server.c
// ./server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;
    key_t key = 1234; // Shared memory key

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to shared memory
    const char *message = "Hello from the server!";
    strncpy(shm_ptr, message, SHM_SIZE);

    // Detach from shared memory
    shmdt(shm_ptr);
    printf("Server: Message written to shared memory.\n");
    printf("By Onkar - T1905308657\n");

    return 0;
}

// ----------------------------------------------------------------


// Make: nano client.c
// gcc -o client client.c
// ./client

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shm_ptr;
    key_t key = 1234; // Shared memory key

    // Get the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory segment
    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory
    printf("Client: Message read from shared memory: %s\n", shm_ptr);

    // Detach from shared memory
    shmdt(shm_ptr);
    printf("By Onkar - T1905308657\n");

    return 0;
}



// OUTPUT

// Server: Message written to shared memory.
// By Onkar - T1905308657

// Client: Message read from shared memory: Hello from the server!
// By Onkar - T1905308657
