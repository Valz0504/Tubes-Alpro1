#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100

typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

void initStack(Stack *s);
void push(Stack *s, int value);
void pop(Stack *s, int *value);

#endif

