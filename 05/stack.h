#include <stdlib.h>
#include <math.h>

/* some versions of clib don't seem to have NAN defined in math.h */
#ifndef NAN
#define NAN (0.0/0.0)
#endif

struct stack {
	size_t array_size;
	double *head;
	double *array;
};

/* return a new, empty stack */
struct stack *stack_new(void);

/* push 'item' onto the top of the stack */
void stack_push(struct stack *this, double item);

/* pop the most recently added item off the stack and returns it
 * if the stack it empty, return NaN */
double        stack_pop(struct stack *this);

/* returns 0 if the stack is empty, or 1 otherwise */
int           stack_isEmpty(struct stack* this);

