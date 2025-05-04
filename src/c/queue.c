#include "header/queue.h"
#include <stdio.h>

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// masih bisa diubah
void enqueue(Queue *q, int value) {
    if ((q->rear + 1) % MAX_QUEUE == q->front) {
        printf("Queue penuh!\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;
    }

    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->data[q->rear] = value;
}

void dequeue(Queue *q, int *value) {
    if (q->front == -1) {
        printf("Queue kosong!\n");
        return;
    }

    *value = q->data[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE;
    }
}