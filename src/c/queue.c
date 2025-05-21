#include <stdio.h>
#include <stdlib.h>
#include "../header/queue.h"

void initQueue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

// masih bisa diubah
void enqueue(Queue *q, int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = NULL;

    if (q->head == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void dequeue(Queue *q, int *value) {
    if (q->head == NULL) {
        printf("Antrian kosong!\n\n");
        return;
    }

    Node *temp = q->head;
    *value = temp->info;

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
}
int countQueue(Queue q){
    int count = 0;
    Node *A = q.head;
    while(A != NULL){
        count++;
        A = A->next;
    }
    return count;
}

boolean isEmpty(Queue q) {
    return (q.head == NULL && q.tail == NULL);
}