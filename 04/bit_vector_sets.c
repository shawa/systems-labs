#include <stdlib.h>

const int LENGTH_OF_WORD = sizeof(unsigned);

struct bitset {
	int universe_size;
	int num_words;
	unsigned *array;
};

struct bitset * bitset_new(int size)
{
	struct bitset *this = malloc(sizeof(struct bitset));
	this->universe_size = size;

	this->num_words = (size % LENGTH_OF_WORD == 0)? size/LENGTH_OF_WORD : size/LENGTH_OF_WORD + 1;
	this->array = malloc(LENGTH_OF_WORD * this->num_words);

	int i;
	for (i = 0; i < this->num_words; i++)
		this->array[i] = 0;

	return this;
}


/* given an 'item', compute the index of:
 * - the word where that item is located
 * - the bit in that word, corresponding to that item
 */
void calculate_indices(int item, int *word_index, int *bit_index)
{
	*(word_index) = item / LENGTH_OF_WORD;
	*(bit_index)  = item % LENGTH_OF_WORD;
}


/* check to see if an item is in the set
 * returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
 */
int bitset_lookup(struct bitset * this, int item)
{
	if (item > this->universe_size || item < 0) {
		return -1;
	} else {
		int word_index = 0;
		int bit_index  = 0;
		calculate_indices(item, &word_index, &bit_index);
		unsigned word = this->array[word_index];

		word >>= bit_index;

		return ((word & 1) != 0);
	}
}

/* add an item, with number 'item' to the set
 * (returns 0 if item is out of bounds, 1 otherwise)
 * has no effect if the item is already in the set
 */
int bitset_add(struct bitset * this, int item)
{
	if (item >= this->universe_size || item < 0) {
		return 0;
	} else {
		int word_index = 0;
		int bit_index  = 0;
		calculate_indices(item, &word_index, &bit_index);

		this->array[word_index] |= (1 << bit_index);
		return 1;
	}

}

/* remove an item with number 'item' from the set
 * (returns 0 if item is out of bounds, 1 otherwise)
 */
int bitset_remove(struct bitset * this, int item)
{
	if (item >= this->universe_size || item < 0) {
		return 0;
	} else {
		int word_index = 0;
		int bit_index = 0;
		calculate_indices(item, &word_index, &bit_index);

		this->array[word_index] &= ~(1 << bit_index);
		return 1;
	}
}


/* place the union of src1 and src2 into dest
 */
void bitset_union(struct bitset * dest, struct bitset * src1,
                  struct bitset * src2)
{
	int i;
	for (i = 0; i < dest->num_words; i++)
		dest->array[i] = src1->array[i] | src2->array[i];
}

/* place the intersection of src1 and src2 into dest
 */
void bitset_intersect(struct bitset * dest, struct bitset * src1,
                      struct bitset * src2)
{
	int i;
	for (i = 0; i < dest->num_words; i++)
		dest->array[i] = src1->array[i] & src2->array[i];
}


