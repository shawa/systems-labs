all: main

main: main.c
	gcc -std=c89 -o main.o main.c stack.c

test: test_stack.c
	gcc -std=c89 -o test_stack.o test_stack.c

debug: main.c stack.c test_stack.c
	gcc -g -std=c89 -o main.o main.c stack.c
	gcc -g -std=c89 -o test_stack.o test_stack.c

clean:
	rm -rf ./*.o ./*.dSYM
