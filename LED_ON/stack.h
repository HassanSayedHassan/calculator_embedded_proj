#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

// change this to your item
typedef char item;
// ex:
// typedef unsigned int item;

typedef struct stack* Stack;

// dynamic locate memory
// call free when done
Stack stack_create(int);

// util for debug
void stack_println(Stack);

// should call stack_is_full before push
bool stack_push(Stack, item);

// should call stack_is_empty before pop
// pop return 0 on empty
item stack_pop(Stack);
item stack_top(Stack s);
bool stack_is_full(Stack);
bool stack_is_empty(Stack);
void stack_make_empty(Stack);
int stack_len(Stack);

#endif