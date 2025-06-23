#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#define barrier() asm ("mfence")

#define N_COUNTER 4
#define MILLI 1000
#define N 2  // Number of processes (0: producer, 1: consumer)

int queue[N_COUNTER];  // shared buffer
int wptr = 0, rptr = 0;

int choosing[N];
int number[N];

int counter = 0;  // just to check if buffer content is being processed

// Bakery algorithm: lock & unlock
void bakery_lock(int i) {
    barrier();
    choosing[i] = 1;
    int max = 0;
    for (int j = 0; j < N; j++) {
        if (number[j] > max)
            max = number[j];
    }
    number[i] = max + 1;
    choosing[i] = 0;

    for (int j = 0; j < N; j++) {
        while (choosing[j]) {}
        while (number[j] != 0 && 
              (number[j] < number[i] || 
              (number[j] == number[i] && j < i))) {}
    }
    barrier();
}

void bakery_unlock(int i) {
    barrier();
    number[i] = 0;
    barrier();
}

void mywrite(int n, int pid) {
    while ((wptr + 1) % N_COUNTER == rptr) {
        // Busy wait: buffer full
    }

    bakery_lock(pid);
    queue[wptr] = n;
    wptr = (wptr + 1) % N_COUNTER;
    bakery_unlock(pid);
}

int myread(int pid) {
    while (wptr == rptr) {
        // Busy wait: buffer empty
    }

    bakery_lock(pid);
    int val = queue[rptr];
    rptr = (rptr + 1) % N_COUNTER;
    bakery_unlock(pid);
    return val;
}

void* producer(void* arg) {
    int pid = 0;
    for (int i = 0; i < 10; i++) {
        mywrite(i, pid);
        printf("producer : wrote %d\n", i);
        int m = rand() % 10;
        usleep(MILLI * m * 10);
    }
    return NULL;
}

void* consumer(void* arg) {
    int pid = 1;
    for (int i = 0; i < 10; i++) {
        int n = myread(pid);
        printf("\tconsumer : read %d\n", n);
        int m = rand() % 10;
        usleep(MILLI * m * 10);
    }
    return NULL;
}

int main() {
    pthread_t t[2];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        choosing[i] = 0;
        number[i] = 0;
    }

    pthread_create(&t[0], NULL, producer, NULL);
    pthread_create(&t[1], NULL, consumer, NULL);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);

    return 0;
}
