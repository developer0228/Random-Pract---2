// Thread synchronization using counting semaphores. Application to demonstrate: 
// producer consumer problem with counting semaphores and mutex.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5      // Size of the shared buffer
#define MAX_ITEMS 10       // Maximum items to produce and consume

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;  // `in` points to the next empty slot for producer, `out` points to the next item for consumer

// Semaphores and mutex for synchronization
sem_t empty, full, mutex;  // Empty, Full and Mutex semaphores

// Shared counter to keep track of the number of items produced and consumed
int produced_count = 0, consumed_count = 0;

// Function for producer
void* producer(void* arg) {
    int item;
    while (produced_count < MAX_ITEMS) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Decrement the empty semaphore (wait for space in buffer)
        sem_wait(&mutex);  // Enter critical section (mutex)

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;  // Circular buffer logic

        produced_count++;  // Increment the produced item count
        printf("Producer produced: %d (Total produced: %d)\n", item, produced_count);

        sem_post(&mutex);  // Exit critical section (mutex)
        sem_post(&full);   // Increment the full semaphore (notify consumer)

        sleep(rand() % 2);  // Simulate time to produce an item
    }
    return NULL;
}

// Function for consumer
void* consumer(void* arg) {
    int item;
    while (consumed_count < MAX_ITEMS) {
        sem_wait(&full);  // Decrement the full semaphore (wait for an item in the buffer)
        sem_wait(&mutex); // Enter critical section (mutex)

        // Remove item from buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;  // Circular buffer logic

        consumed_count++;  // Increment the consumed item count
        printf("Consumer consumed: %d (Total consumed: %d)\n", item, consumed_count);

        sem_post(&mutex);  // Exit critical section (mutex)
        sem_post(&empty);  // Increment the empty semaphore (notify producer)

        sleep(rand() % 3);  // Simulate time to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    // Print the user-specific statement
    printf("By Onkar - T1905308657\n");

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // `empty` starts at BUFFER_SIZE (all slots are empty)
    sem_init(&full, 0, 0);             // `full` starts at 0 (no items to consume)
    sem_init(&mutex, 0, 1);            // `mutex` starts at 1 (mutex for mutual exclusion)

    // Create producer and consumer threads
    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    // Wait for both producer and consumer to finish
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}


// OUTPUT

// By Onkar - T1905308657
// Producer produced: 15 (Total produced: 1)
// Consumer consumed: 15 (Total consumed: 1)
// Producer produced: 38 (Total produced: 2)
// Consumer consumed: 38 (Total consumed: 2)
// Producer produced: 72 (Total produced: 3)
// Consumer consumed: 72 (Total consumed: 3)
// Producer produced: 93 (Total produced: 4)
// Consumer consumed: 93 (Total consumed: 4)
// ...
