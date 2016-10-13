# CS2014 Lab 5 : Command line parameters

Thursday 30th October

The goal of this project is to develop a calculator for expressions in
reverse Polish notation. Your program shoud take in an expression in
reverse Polish notation as a set of parameters and write out the value
of that expression.

For example, if your program is called mycalc you might write:
	mycalc 7 8 3 X 28 + +
The output should be:
	59

The operators that you calculator should support are plus (+),
minus (-), multiply (X) and divide (/). It is very important that you
do not use * for multiply.

When writing your program, you should build a stack abstract data type
(ADT), which can store double precision floating point numbers. Your
stack ADT should provide functions to implement at least the following
operation: push, pop, isempty. You should then use this stack ADT to
evaulate the expressions.

Note that you must create and use a stack ADT in your program if you
want the marks for this lab.

The algorithm for computing the value of an expression in reverse
Polish notation is simple:

```{.c}
for each token in the input string {
  if ( token is a number ) {
    push token onto the stack
  }
  else if ( token is an operator ) {
    pop the top two items off the stack
    apply the operator to the two items
    push the result onto the stack
  }
}
```
At the end of this computation, if you are dealing with a correctly-
formed expression, there should be exactly one number on the stack.
This is the result of the expression.

Note that you can assume that the expression that your program
receives is well formed. You do not have to do any complicated error
checking.

This lab will be marked, and will count towards your end of year mark.
You should submit your project through Blackboard by 11.59PM on
Wednesday 12th November. To be marked, you must demonstrate and answer
questions on your project at your regular lab session on Thursday 13th
November. You must demonstrate the same code that you submit. All work

