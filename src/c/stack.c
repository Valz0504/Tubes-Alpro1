#include <stdio.h>
#include "../header/stack.h"

void initStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, int value) {
    if (s->top < MAX_STACK - 1) {
        s->top++;
        s->data[s->top] = value;
    } else {
        printf("Stack penuh!\n");
    }
}

void pop(Stack *s, int *value) {
    if (s->top >= 0) {
        *value = s->data[s->top];
        s->top--;
    } else {
        printf("Stack kosong!\n");
    }
}
