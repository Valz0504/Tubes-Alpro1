#include <stdio.h>
#include "../header/stack.h"
#include "../header/coloring.h"

void initStack(Stack *s) {
    s->length = 0;
    s->top = -1;
}

void push(Stack *s, int value) {
    if (s->top < MAX_STACK - 1) {
        s->length += 1;
        s->top++;
        s->data[s->top] = value;
    } else {
        printf(RED "Perut penuh!\n" RESET);
    }
}

void pop(Stack *s, int *value) {
    if (s->top >= 0) {
        *value = s->data[s->top];
        s->top--;
        s->length--;
    } else {
        printf(RED "Perut kosong!\n" RESET);
    }
}

void emptyStack(Stack *s) {
    while (s->length > 0) {
        int value;
        pop(s, &value);
        s->length--;
    }
}
