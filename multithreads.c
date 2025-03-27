#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

typedef struct {
    int *arr;
    int start;
    int end;
    long long partial_sum;
} ThreadData;

void *compute_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->partial_sum = 0;

    for (int i = data->start; i < data->end; i++) {
        data->partial_sum += data->arr[i];
    }

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of elements (greater than 1000): ");
    scanf("%d", &n);

    if (n <= 1000) {
        printf("Please enter a value greater than 1000.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize array with random values
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Random numbers between 0 and 99
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    int segment_size = n / NUM_THREADS;  // Changed variable name from chunk_size to segment_size

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = arr;
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * segment_size;
        pthread_create(&threads[i], NULL, compute_sum, &thread_data[i]);
    }

    // Wait for all threads to complete
    long long total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    printf("Total Sum: %lld\n", total_sum);

    free(arr);
    return 0;
}
