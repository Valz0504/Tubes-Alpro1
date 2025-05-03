#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 10

typedef struct {
    int data[MAX_QUEUE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q, int value);

#endif