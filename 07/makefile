CFLAGS = -std=c99 -Wall
CCOMP = gcc

main: main.c huffman_tree.c
	$(CCOMP) $(CFLAGS) -o main.o huffman_tree.c main.c

huffman_tree.o: huffman_tree.c
	$(CCOMP) $(CFLAGS) -o huffman_tree.o huffman_tree.c

test_huffman_tree: test_huffman_tree.c
	$(CCOMP) $(CFLAGS) -g -o test_huffman_tree.o test_huffman_tree.c

debug: huffman_tree.c test_huffman_tree.c
	$(CCOMP) $(CFLAGS) -g -o huffman_tree.o huffman_tree.c
	$(CCOMP) $(CFLAGS) -g -o test_huffman_tree.o test_huffman_tree.c

clean:
	rm -rf *.o *.html *.pdf *.dSYM
