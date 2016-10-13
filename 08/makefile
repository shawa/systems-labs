CFLAGS = -std=c99 -Wall
CCOMP = gcc

huff_codec: huff_codec.c
	$(CCOMP) $(CFLAGS) -g -o huff_codec.o huff_codec.c bitfile.c huffman_tree.c

link:
	ln -s huff_codec.o huffcode
	ln -s huff_codec.o huffdecode

test_bitfile: test_bitfile.c
	$(CCOMP) $(CFLAGS) -g -o test_bitfile.o test_bitfile.c

test_bit_array: test_bit_array.c
	$(CCOMP) $(CFLAGS) -g -o test_bit_array.o test_bit_array.c


bitfile.o: bitfile.c
	$(CCOMP) $(CFLAGS) -o bitfile.o bitfile.c

clean:
	rm -rf *.o *.html *.pdf *.dSYM *.bf
