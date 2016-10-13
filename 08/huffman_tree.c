#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "huffman_tree.h"

/* The number of permutations of bits in a byte
 * 2^8 = 256
 * */
static const int BYTE_PERMUTATIONS = 256;

static const signed char EOT = 0x04;

/* A bit cheeky; this can work on arbitrarily sized alphabets, all we need to know is the
 * size of the character data stored in the leaf nodes. The client can then just modify the
 * header file to use a different member type in the structure definition without having
 * to figure out all the tricky maths.
 *
 * So, we cast the NULL pointer to
 * a struct huff_symbol pointer, then grab the size of the data.character entry.
 * Sizeof never actually evaluates its argument, so we can dereference NULL without worry.
 * */    //but that only seems to work with clang :(
#if defined(__clang__)
static const int ALPHABET_SIZE = sizeof(((struct huff_symbol *)NULL)->data.character) * BYTE_PERMUTATIONS;
#else
static const int ALPHABET_SIZE = 256;
#endif


/* Huffman Tree 'symbol' constructor. A symbol can be one of:
 * leaf: Contains a single char and a frequency
 * node: Contains pointers to left and right children, followed by
 *       cumulative frequency
 *
 * The constructor is variadic; if given 'kind' is leaf, we expect a char
 * literal. If kind is node, we expect two struct huff_symbol* pointers.
 *
 * Returns a pointer to a newly allocated struct huff_symbol.
 * */
static struct huff_symbol *huff_symbol_new(huff_symbol_kind kind, ...)
{
	struct huff_symbol *this = malloc(sizeof(struct huff_symbol));
	this->kind = kind;


	va_list args; va_start(args, kind);
	switch(kind){
		case leaf: {
			int frequency = va_arg(args, int);
			unsigned char  character = (unsigned char)va_arg(args, int);

			this->data.character = character;
			this->frequency = frequency;
			va_end(args);
		} break;
		case node: {
			struct huff_symbol *left = va_arg(args, struct huff_symbol*);
			struct huff_symbol *right = va_arg(args, struct huff_symbol*);

			this->data.children.left = left;
			this->data.children.right = right;
			this->frequency = (this->data.children.left->frequency +
			                   this->data.children.right->frequency);
			va_end(args);
		} break;
	};
	return this;
}

/* From a given array, construct a new array of pointers to huff_symbols.
 * If 'i' is a particular char, character_count[i] is the frequency of that character.
 * If character_count[i] is 0, we give its corresponding symbol a frequency
 * of 1, per the problem spec 'to make sure that they get some sort of sensible encoding'
 * */
static struct huff_symbol **symbol_list_new(int character_count[])
{
	struct huff_symbol** symbol_list = malloc(sizeof(struct huff_symbol*) * ALPHABET_SIZE);

	for (int frequency, i = 0; i < ALPHABET_SIZE; i++) {
		frequency = (character_count[i] > 0? character_count[i] : 1);
		symbol_list[i] = huff_symbol_new(leaf, frequency, (char)i);
	}
	return symbol_list;
}

/* For a given array of pointers to huff_symbols, find the index of the nth minimal
 * element.
 * */
static int symbol_list_min(struct huff_symbol **symbol_list)
{
	int i, min;
	min = -1;
	//set min to the index of the first non-NULL entry in the array
	for (i = 0; i < ALPHABET_SIZE; i++) {
		if (symbol_list[i] != NULL) {
			min = i;
			break;
		}
	}

	if (min == -1) return min;

	for (i = min; i < ALPHABET_SIZE; i++) {
		if (symbol_list[i] == NULL) continue;

		if (symbol_list[i]->frequency < symbol_list[min]->frequency) {
			min = i;
		}
	}

	/* It might have been a list of NULLs, in which case min would never have
	 * been altered. Return a sentinel -1 instead
	 * With short circuiting we only have to check the min-th symbol for NULLity
	 * in the zero case. Comparison to zero is also pretty cheap, so that's nice.
	 */
	return min;
}

/* Merge the two least frequent elements of the given symbol list. This function
 * is not pure.
 * The algorithm:
 *  - We find the index of the least frequent symbol and create a reference to it.
 *  - Set the symbol list's entry at that index to NULL.
 *
 *  - Again find the least frequent element (we ignore NULL in our search, so this will
 *    in effect find the second least frequent element of the list passed to the function
 *    and store a reference).
 *  - Create a new node type symbol with references to the two found elements of the
 *    symbol list.
 * */
static struct huff_symbol *merge_least_two(struct huff_symbol **this) {
	int min = symbol_list_min(this);
	struct huff_symbol *minimal_symbol = this[min];
	this[min] = NULL;

	int next_min = symbol_list_min(this);
	struct huff_symbol *next_minimal_symbol = this[next_min];

	struct huff_symbol *merged = huff_symbol_new(node, minimal_symbol, next_minimal_symbol);
	this[next_min] = merged;

	return this[next_min];
}

/* Given any character frequency table, with max number of characters n, it is
 * a constant that we need n-1  merges. That is, any tree of n nodes has
 * n-1 edges
 *
 * Proof!(by induction):
 *   Let P(n) := (with n symbols, it takes n-1 merges to get a complete huffman tree)
 *   	 P(1) => 0 merges, as we already have a complete tree.
 *
 *   	 Assume P(n) for induction step.
 *   	   Then for a tree of n nodes we will have
 *   	   carried out n-1 merges. We add another node, so, having merged the previous
 *   	   n nodes n-1 times, we merge one more; giving n merges for n+1 nodes.
 *   	   Thus P(n+1) => n merges for n+1 symbols.
 *   	 As P(n+1) is true given P(n), we conclude P(n) => P(n+1).
 *
 * 	 Therefore by induction P(1) => P(2) => ...
 * 	   => P(n)
 *	[black square]
 * */
static struct huff_symbol *build_huffman_tree(struct huff_symbol **symbol_list)
{
	struct huff_symbol *head;
	for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
		head = merge_least_two(symbol_list);
	}
	return head;
}

/* The constructor we expose. The client only has a list of frequencies, and the size of their
 * alphabet. We build a symbol list from these frequencies, merge them into the huffman tree,
 * then return the head/root (these words are synonymous, in CS, yet complete opposites in
 * real life, huh.) of the tree.
 * */
struct huff_symbol *huff_tree_new(int *character_frequencies)
{
	struct huff_symbol **symbol_list = symbol_list_new(character_frequencies);
	struct huff_symbol *result = build_huffman_tree(symbol_list);
	free(symbol_list);
	return result;
}

/* The recursive worker for the tree printing. We enter the left and right nodes of the
 * current node on the tree. If we reach a leaf, then we print out the character stored
 * at that leaf, then the path it took to get there. This can easily be modified to
 * write out to a suitable file or table.
 * */
static void huff_traverse_print(struct huff_symbol *cur_node, int *path, int depth,
		                int** output_table)
{
	switch (cur_node->kind) {
		case node: {
			path[depth] = 0;
			huff_traverse_print(cur_node->data.children.left, path, depth+1, output_table);

			path[depth] = 1;
			huff_traverse_print(cur_node->data.children.right, path, depth+1, output_table);
		} break;
		case leaf: {
			unsigned char character = cur_node->data.character;
			char *fmt_string;

			if (output_table != NULL) {
				output_table[character] = malloc(sizeof(int) * (depth + 1));
				output_table[character][0] = depth;
				for (int i = 0; i < depth; i++) {
					output_table[character][i+1] = path[i];
				}
			} else {
				/* if the character is printable, print it, otherwise
				 * print its hexadecimal value
				 **/
				if (character >= '!' && character <= '~') {
					fmt_string = "   %c %d ";
				} else {
					fmt_string = "0x%02x %d ";
				}


				printf(fmt_string, cur_node->data.character, cur_node->frequency);
				for(int i = 0; i < depth; i++) {
					printf("%d", path[i]);
				}
				printf("\n");
			}
		} break;
	}
}

/* The print routine exposed to the client. Again, the client shouldn't know anything
 * about how it needs to keep track of the current depth, or that we need to have an
 * array of ints keeping track of the path history.
 * */
void huff_tree_print(struct huff_symbol *head)
{
	/* Given an alphabet of size n, the worst case depth of the
	 * tree is n-1. I can't really justify this, save for that
	 * a really bad tree is just a linked list, which, if n
	 * nodes long, has n-1 pointers in it.
	 * */
	int *path = malloc(sizeof(int) * ALPHABET_SIZE - 1);
	huff_traverse_print(head, path, 0, NULL);
	free(path);
}


static int write_huff_char(int **symbol_table, struct bitfile *output_file, unsigned char c)
{
	int result = 0;
	for (int j = 1; j < symbol_table[c][0] + 1; j++){
		result = bfputb(symbol_table[c][j], output_file);
		if (result == EOF) goto error;
	}
	return 0;

error:
	bfclose(output_file);
	return EOF;
}

int huff_compress(int **huff_symbols, struct bitfile *outfile, FILE *infile)
{
	int result = 0;
	char character = '\0';
	while( (character = fgetc(infile)) != EOF){
		result = write_huff_char(huff_symbols, outfile, character);
		if (result == EOF) goto error;
	}

	result = write_huff_char(huff_symbols, outfile, EOT);
	if (result == EOF) goto error;
	return 0;
error:
	fclose(infile);
	bfclose(outfile);
	return EOF;

}




/* For a given huffman symbol, return the symbol indicated by the given direction.
 * Recall 0 is the left child, 1 the right. If the node is a leaf, return NULL,
 * as leaves have no children.
 * */
static struct huff_symbol *huff_traverse_lookup(struct huff_symbol *cur_node, int direction)
{
	switch (cur_node->kind) {
		case node: {
			struct huff_symbol *next = direction == 0 ?
			       			    cur_node->data.children.left :
						    cur_node->data.children.right;

			return next;
		} break;
		case leaf: {
			return NULL;
		} break;
		default: return NULL;
	}

}

/* A sadly monolithic decoding routine. For a given huffman tree, an input
 * bitfile, consume direction bits from the bitfile while traversing the
 * tree. If we hit a leaf, write that leaf's character data to the output
 * file and return to the head of the tree.
 * */
int huff_decompress(struct huff_symbol *head, struct bitfile *infile, FILE *outfile)
{
	int direction = -1;
	struct huff_symbol *next = head;
	int result = 0;

	do {
		direction = bfgetb(infile);
		next = huff_traverse_lookup(next, direction);

		switch (next->kind) {
			case node: continue; break;
			case leaf: {
				if (next->data.character == EOT) return 0;

				result = fputc(next->data.character, outfile);
				if (result == EOF) return 1;

				next = head;
			} break;
		}

	} while (direction != -1);

	return 0;
}

/* Recurse down the whole tree. The call stack maintains links to all the previous
 * nodes that have been traversed. Only when the next deeper function calls do we free
 * the reference. When we reach a leaf we return, freeing everything above.
 * this is similar to kill_linked_list we saw before.
 * */
static void huff_traverse_free(struct huff_symbol *cur_node)
{
	switch (cur_node->kind) {
		case node: {
			huff_traverse_free(cur_node->data.children.left);
			free(cur_node->data.children.left);
			huff_traverse_free(cur_node->data.children.right);
			free(cur_node->data.children.right);
		} break;
		case leaf: {
			return;
		} break;
	}
}

/* Frees the whole tree; the recursive function doesn't free the head, and it's
 * best to separate recursive workers from client-facing code.
 * */
void huff_tree_free(struct huff_symbol *head)
{
	huff_traverse_free(head);
	free(head);
}

int **huff_tree_symbols(struct huff_symbol *head)
{
	/* Given an alphabet of size n, the worst case depth of the
	 * tree is n-1. I can't really justify this, save for that
	 * a really bad tree is just a linked list, which, if n
	 * nodes long, has n-1 pointers in it.
	 * */
	int *path = malloc(sizeof(int) * ALPHABET_SIZE - 1);
	int **result = malloc(sizeof(int*) * ALPHABET_SIZE);
	memset(result, 0, sizeof(int*) * ALPHABET_SIZE);
	huff_traverse_print(head, path, 0, result);
	free(path);
	return result;
}
