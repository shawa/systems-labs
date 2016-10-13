#include "stack.h"
#include <assert.h>

/* we use size_t throughout by convention, and as it is
 * guaranteed by the specification to hold any array index.
 * we don't ever have stacks of 'negative' size anyway, so
 * an int doesn't quite make sense */
const size_t DEFAULT_SIZE = 16;

/* returns a pointer to a new, empty stack */
struct stack *stack_new(void) {
	struct stack* new = malloc(sizeof(struct stack));
	assert(new != NULL);
	new->array_size = DEFAULT_SIZE;
	new->array = malloc(sizeof(double) * new->array_size);
	assert(new->array != NULL);
	new->head = new->array;

	return new;
}

/* returns 1 if 'this' is an empty stack */
int stack_isEmpty(struct stack* this)
{
	return this->head == this->array;
}


/* reallocates the block of memory pointed to by this->array,
 * if the stack 'shouldShrink', it is halved, otherwise,
 * it is doubled
 *
 * the static declaration is to (somewhat) ensure it is only ever
 * called by functions defined within *this* source file; not programs
 * #including stack.h. In any case, at least the reader
 * knows that this isn't meant to be exposed to the client
 * */
static void stack_resize(struct stack *this, int shouldShrink)
{
	size_t newsize = shouldShrink? this->array_size/2 : this->array_size*2;
	double* new_array = malloc(sizeof(double) * newsize);
	assert(new_array != NULL);


	/* the upper bound for the number of accessible items
	 * from the 'old' array to the newly allocated one
	 * is the smaller of the two arrays. If we are shrinking
	 * the array, this is the new size. Otherwise,
	 * this is the original size */
	int length = (int)(shouldShrink? newsize : this->array_size);

	int i;
	for (i = 0; i < length; i++){
		new_array[i] = this->array[i];
	}

	/* the top of the stack is now the base of the new
	 * stack, offset by how far up from the base the head
	 * of the old stack used to be */
	this->head = new_array + (this->head - this->array);

	/* making sure to pick up after ourselves */
	free(this->array);

	this->array = new_array;
	this->array_size  = newsize;
}

/* A helper to determine if we need to resize the array given its
 * current state. If pushin an item would exceed the bounds of the
 * array, the size of the stack's array is doubled.
 *
 * If popping causes there to be fewer items than one quarter of the allocated
 * capacity of the array, it is array is halved.
 * This is an optimisation; to avoid the scenario of successive
 * push-pop operations on the 'cusp of resizing' constantly scaling the array. */
static int shouldResize(struct stack *this){
	size_t size = (size_t)(this->head - this->array);
	if (size == this->array_size) {
		return 1;
	} else if (size < this->array_size/4) {
		return -1;
	} else {
		return 0;
	}
}

/* pushes an item to the top of the stack, resizing if necessary */
void stack_push(struct stack *this, double item)
{
	if (shouldResize(this) == 1) {
		stack_resize(this, 0);
	}

	*(this->head) = item;
	(this->head)++;
}

/* pops an item off the top, resizing if necessary.
 *
 * If the stack is empty, it is unmodified, and NaN is returned. */
double stack_pop(struct stack *this)
{
	if (stack_isEmpty(this)){
		return NAN;
	}

	if (shouldResize(this) == -1) {
		stack_resize(this, 1);
	}

	(this->head)--;
	return *(this->head);
}

