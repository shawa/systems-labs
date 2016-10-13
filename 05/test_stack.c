#include "stack.c"
#include <stdio.h>
#include <assert.h>

/*
 * (Incomplete) unit tests for our stack ADT
 * */
void test_stack_new()
{
	struct stack *this = stack_new();
	assert(sizeof(*this) == sizeof(struct stack));
	assert(this->array != NULL);
	assert(this->array_size == DEFAULT_SIZE);
}


void test_stack_resize()
{
	struct stack *this = stack_new();

	stack_resize(this, 1);
	assert(this->array_size == DEFAULT_SIZE / 2);
	assert(this->array != NULL);

	stack_resize(this, 0);
	assert(this->array_size = DEFAULT_SIZE * 2);
	assert(this->array != NULL);
	free(this);
}


void test_stack_push_pop()
{
	struct stack *this = stack_new();

	int i;
	for (i = 0; i < 35; i++){
		stack_push(this, (double)i);
	}

	double value;
	for (i = 0; i < 35; i++) {
		value = stack_pop(this);
	}

	/* popping off an empty stack should yeild NaN */
	assert(isnan(stack_pop(this)));
}




void test_stack_isEmpty()
{
	struct stack* this = stack_new();
	assert(stack_isEmpty(this));

	stack_push(this, 0.2);
	assert(!stack_isEmpty(this));
}

int main(void)
{
	test_stack_new();
	test_stack_resize();
	test_stack_push_pop();
	test_stack_isEmpty();
}
