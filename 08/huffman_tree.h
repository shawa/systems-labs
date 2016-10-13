#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bitfile.h"

typedef enum node_type {
		node, leaf
	} huff_symbol_kind;

struct huff_symbol {
	huff_symbol_kind kind;
	int frequency;
	union data {
		struct {
			struct huff_symbol *left;
			struct huff_symbol *right;
		} children;
		unsigned char character;
	} data;
};


/* construct a huffman tree from the given array of character
 * frequencies. returns a pointer to the root of the tree
 **/
struct huff_symbol *huff_tree_new(int *character_frequencies);
void huff_tree_free(struct huff_symbol *head);

/* Print the huffman table for the given huffman
 * tree
 **/
void huff_tree_print(struct huff_symbol *head);

/* Return an array of integer arrays 'symbols', where symbol[c]
 * is the huffman code for a particular character c.
 * Each symbols[i] is of the form:
 * 	{n, x, x, x, ... , x}
 * Where n is the length of the symbol for that particular
 * character, and x is either 1 or 0.
 * **/
int **huff_tree_symbols(struct huff_symbol *head);

/*
 * To signify the end of an encoding, the huffman code
 * for ASCII EOT, that is 0x04 is appended to every file.
 * On decoding, if the decoder reaches this EOT, it is
 * __not__ written to the output file, and the decoder
 * returns success.
 *
 * If an IO error occurs, the function returns 1 */

/* Inflate a huffman bitfile according to the given huffman
 * tree.
 * */
int huff_decompress(struct huff_symbol *huffman_tree, struct bitfile *infile, FILE *outfile);


int huff_compress(int **huff_symbols, struct bitfile *outfile, FILE *infile);
