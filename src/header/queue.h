#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"

typedef struct Node{
    int info;
    struct Node* next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q, int *value);
boolean isEmpty(Queue q);

#endif