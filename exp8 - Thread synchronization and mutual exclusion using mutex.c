//  Thread synchronization and mutual exclusion using mutex. Application to 
// demonstrate: Reader Writer problem with reader priority.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 2
#define MAX_READS 10     // Maximum number of reads
#define MAX_WRITES 5     // Maximum number of writes

int read_count = 0, data = 0;
int reads_done = 0, writes_done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reader_lock = PTHREAD_COND_INITIALIZER;
pthread_cond_t writer_lock = PTHREAD_COND_INITIALIZER;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (reads_done < MAX_READS) {
        pthread_mutex_lock(&mutex);
        while (read_count == -1) pthread_cond_wait(&reader_lock, &mutex);
        read_count++;
        printf("Reader %d reads: %d\n", id, data);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) pthread_cond_signal(&writer_lock);
        pthread_mutex_unlock(&mutex);

        reads_done++;
        sleep(rand() % 2);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (writes_done < MAX_WRITES) {
        pthread_mutex_lock(&mutex);
        while (read_count > 0 || read_count == -1) pthread_cond_wait(&writer_lock, &mutex);
        read_count = -1;
        data++;
        printf("Writer %d writes: %d\n", id, data);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2);

        pthread_mutex_lock(&mutex);
        read_count = 0;
        pthread_cond_broadcast(&reader_lock);
        pthread_mutex_unlock(&mutex);

        writes_done++;
        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    printf("By Onkar - T1905308657\n");

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_READERS; i++) pthread_join(readers[i], NULL);
    for (int i = 0; i < MAX_WRITERS; i++) pthread_join(writers[i], NULL);

    // Clean up and destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&reader_lock);
    pthread_cond_destroy(&writer_lock);

    return 0;
}


// OUTPUT
// By Onkar - T1905308657
// Reader 1 reads: 0
// Reader 2 reads: 0
// Reader 3 reads: 0
// Writer 1 writes: 1
// Reader 4 reads: 1
// Writer 2 writes: 2
// Reader 5 reads: 2
// ...
