#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct stack {
    int top;
    int size;
    item *data_array;
};

Stack stack_create(int size) {
    Stack s = malloc(sizeof(struct stack));
    if(s == NULL) {
        return NULL;
    }

    // create data array
    s->data_array = malloc(sizeof(int) * size);
    if(s->data_array == NULL) {
        return NULL;
    }

    s->top = 0;
    s->size = size;
    return s;
}

void stack_println(Stack s) {
    for(int i = 0; i < s->top; i++) {
        printf("%c \n", s->data_array[i]);
    }

    printf("\n");
}

bool stack_is_full(Stack s) {
    return s->top == s->size;
}

bool stack_is_empty(Stack s) {
    return s->top == 0;
}

bool stack_push(Stack s, item data) {
    if(stack_is_full(s)) {
        return false;
    }

    s->data_array[s->top++] = data;
    return true;
}

item stack_pop(Stack s) {
    if(stack_is_empty(s)) {
        return 0;
    }

    return s->data_array[--s->top];
}
item stack_top(Stack s) {
    if(stack_is_empty(s)) {
        return 0;
    }

    return s->data_array[s->top];
}
void stack_make_empty(Stack s) {
    s->top = 0;
    return;
}

int stack_len(Stack s) {
    return s->top;
}