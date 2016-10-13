#include <assert.h>
#include <stdio.h>
#include "bit_vector_sets.c"

/* unit tests for our bit vector sets. The reasoning is that if we can pass all
 * these tests, I don't have to waste time debugging both the demo program AND
 * the ADT itself at the same time.
 */

void test_bitset_new()
{
	/* ensure we surpass a word length to test array allocation functionality */
	int size = 128;
	struct bitset *this = bitset_new(size);

	assert(this->universe_size == size);
	assert(this->array != NULL);
	struct bitset *that = bitset_new(size);
	free(this);
}

void test_bitset_interface()
{
	int size = 128;
	struct bitset *this = bitset_new(size);

	/* individually add and lookup elemnt in universe of length 128 */
	int i = 0;
	for (i = 0; i <= size; i++) {
		bitset_add(this, i);
		bitset_lookup(this, i);
	}

	/* now we do the same, and remove each element */
	for (i = 0; i < 128; i++) {
		bitset_remove(this, i);
		assert(!bitset_lookup(this, i));
	}

	/* out of bound insertion and removal */
	assert(!bitset_add(this, -1));
	assert(!bitset_add(this, 128));
	assert(!bitset_remove(this, -1));
	assert(!bitset_remove(this, 128));

	free(this);
}

void test_bitset_operations()
{
	/* we consider some operations on integers in the closed interval [0, 20] */
	int i = 0;
	int size = 128;

	/* all odd numbers */
	struct bitset *A = bitset_new(size);
	int A_num_elems = 10;
	int A_elems[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
	for (i = 0; i < A_num_elems; i++)
		bitset_add(A, A_elems[i]);

	/* all multiples of 5 */
	struct bitset *B = bitset_new(size);
	int B_elems[] = {0, 5, 10, 15, 20};
	int B_num_elems = 5;
	for (i = 0; i < B_num_elems; i++)
		bitset_add(B, B_elems[i]);

	struct bitset *C = bitset_new(size);

	/* C <- A 'union' B */
	bitset_union(C, A, B);
	/* assert that if i is in C, it is in either A or B */
	for(i = 0; i < size; i++) {
		assert((bitset_lookup(A, i) || bitset_lookup(B, i)) == bitset_lookup(C, i));
	}

	/* C <- A 'intersection' B */
	bitset_intersect(C, A, B);
	/* assert that if i is in C, i is in A and i is in B */
	for(i = 0; i < size; i++)
		assert((bitset_lookup(A, i) && bitset_lookup(B, i)) == bitset_lookup(C, i));
}

int main()
{
	test_bitset_new();
	test_bitset_interface();
	test_bitset_operations();
	printf("Passed all tests, joy!\n");
}
