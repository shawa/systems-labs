#include <stdio.h>
#include <string.h>
#include "stack.h"

/*
 * Determine if a given token is one of our
 * possible operators
 *
 * Returns 1 if a match is found, 0 otherwise
 * */
int isOperator(const char *token)
{
	char *operators[] = { "+", "-", "X", "/" };
	int num_operators = 4;
	int result = 0;
	int i;

	/* strcmp is marginally more costly, but it allows easy variable-
	 * length operators, as well as eliminating the hassle in
	 * parsing unary negatives:
	 * eg	3 -5 X ==> -15, as expected
	 * */
	for(i = 0; i < num_operators; i++)
		result |= (strcmp(operators[i], token) == 0);

	return result;
}

/*
 * Returns the result of applying the operation which corresponds
 * to the given 'operator' to 'a' and 'b'
 * */
double apply(double a, double b, char operator)
{
	switch (operator) {
		case '+': return a + b;
		case '-': return a - b;
		case 'X': return a * b;
		case '/': return a / b;
		default:  return 0;
	}

}


/*
 * 'The brains of the operation'
 * If the given rpn expression is complete and valid, its result is returned
 * If there are too many trailing operators, NaN is returned
 * Results are otherwise undefined.
 * */
double rpn_evaluate(int num_tokens, const char *tokens[])
{
	struct stack *values = stack_new();

	int i;
	for (i = 0; i < num_tokens; i++){
		if (isOperator(tokens[i])) {
			double a = stack_pop(values);
			double b = stack_pop(values);
			char operator = *tokens[i];
			/* pushing and popping reverses the order of the values;
			 * for non-commutative operators like - and /, this has
			 * unexpected results if not corrected, hence we 'reverse' b and a
			 * in the apply() call */
			stack_push(values, apply(b, a, operator));
		} else {
			stack_push(values, strtod(tokens[i], NULL));
		}
	}

	return stack_pop(values);
}


void usage(const char* progname)
{
	char *docstring =
		"reverse-polish notation calculator \n"
		"usage: %s <well-formed rpn expression> \n";

	printf(docstring, progname);
}


int main(int argc, const char *argv[])
{
	if (argc == 1) {
		usage(argv[0]);
	} else {
		double result = rpn_evaluate(argc - 1, argv + 1);
		if (isnan(result)) {
			printf("invalid expression \n");
			return 1;
		} else {
			printf("%g\n", result);
			return 0;
		}
	}
}
