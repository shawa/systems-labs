all: main

main: main.c
	gcc -Wall -std=c89 -o main.o main.c hashtable.c

test: test_hashtable.c
	gcc -Wall -std=c89 -o test_hashtable.o test_hashtable.c

debug: main.c hashtable.c test_hashtable.c
	gcc -Wall -g -std=c89 -o main.o main.c hashtable.c
	gcc -Wall -g -std=c89 -o test_hashtable.o test_hashtable.c

clean:
	rm -rf ./*.o ./*.dSYM
