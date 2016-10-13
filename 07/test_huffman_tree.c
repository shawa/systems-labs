#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "huffman_tree.c"
const int char_universe_size = 256;

void test_huff_symbol_new(void)
{
	struct huff_symbol *left = huff_symbol_new(leaf, 3, 'x');
	assert(left != NULL);
	struct huff_symbol *right = huff_symbol_new(leaf, 10, 'o');
	assert(right != NULL);

	struct huff_symbol *parent = huff_symbol_new(node, left, right);
	assert(parent != NULL);
	assert(parent->data.children.left == left);
	assert(parent->data.children.right == right);
	assert(parent->frequency == left->frequency + right->frequency);

	free(parent);
	free(right);
	free(left);
}

void test_symbol_list_new(void)
{
	int *character_count = malloc(sizeof(int) * char_universe_size);
	for (int i = 'A'; i < 'z'; i++) {
		character_count[i] = i/3;
	}

	struct huff_symbol **symbol_list = symbol_list_new(character_count);

	for (int character = 0; character < char_universe_size; character++) {
		assert(symbol_list[character]->data.character == character);
		int expected_frequency = character_count[character] > 0? character_count[character] : 1;
		assert(symbol_list[character]->frequency == expected_frequency);
	}

	free(symbol_list);
}

void test_symbol_list_min(void)
{
	int character_count[] = {5, 3, 1, 7, 9};

	struct huff_symbol **symbol_list = symbol_list_new(character_count);
	assert(symbol_list_min(symbol_list) == 2);

	symbol_list[2] = NULL;
	assert(symbol_list_min(symbol_list) == 1);

	//nullify all but the 3th element of the list
	for (int i = 0; i < 5; i++) {
		if (i != 3)
			symbol_list[i] = NULL;
	}
	int x = symbol_list_min(symbol_list);
	assert(x == 3);

	symbol_list[3] = NULL;

	assert(symbol_list_min(symbol_list) == -1);

}

void test_merge_least_two(void) {
	int *char_count = NULL;
	struct huff_symbol **symbol_list = symbol_list_new(char_count);

	merge_least_two(symbol_list);
	assert(symbol_list[0] == NULL);

	merge_least_two(symbol_list);
	assert(symbol_list[1] == NULL);
}

void test_build_huffman_tree(void) {
	int *char_count = malloc(sizeof(int) * ALPHABET_SIZE);
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (i < 0x1f) {
			char_count[i] = 0;
		} else {
		char_count[i] = rand() % 65536;
		}
	}

	struct huff_symbol **symbol_list = symbol_list_new(char_count);
	struct huff_symbol *head;
	head = build_huffman_tree(symbol_list);
	assert(head != NULL);

	huff_tree_print(head);
}

int main(void){
//	test_huff_symbol_new();
//	test_symbol_list_new();
//	test_symbol_list_min();
//	test_merge_least_two();

	srand(time(NULL));
	test_build_huffman_tree();
	return 0;
}
