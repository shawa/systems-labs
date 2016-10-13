#include <stdio.h>
#include <assert.h>
#include <string.h>

/* include the source file to get at static functions */
#include "hashtable.c"

#define TEST(name) printf("testing %s\n", name)
#define PASS printf("\t passed\n\n");

void test_hash_string(void)
{
	TEST("basic string hashing function");
	char *test = "For infrastructure technology, C will be hard to displace.";
	assert(hash_string(test) == (unsigned)2413027327);

	PASS;
}

void test_hashtable_new(void)
{
	TEST("hastable constructor");

	struct hashtable *this = hashtable_new(DEFAULT_HASHTABLE_SIZE);
	assert(this != NULL);
	assert(this->table != NULL);
	assert(this->size == DEFAULT_HASHTABLE_SIZE);
	assert(this->hash_function != NULL);

	hashtable_free(this);
	PASS;
}

void test_node_new(void)
{
	TEST("linked list node constructor");

	struct node *a, *b, *c, *cur;
	c = node_new("dolor", NULL);
	b = node_new("ipsum", c);
	a = node_new("lorem", b);

	char *datas[] = {"lorem", "ipsum", "dolor" };
	int i, cmp;
	for(cur = c, i = 0; cur->next != NULL; cur = cur->next, i++){
		cmp = strcmp(cur->data, datas[i]);
		assert(cmp == 0);
	}

	kill_linked_list(&a);
	PASS;
}

void test_hashtable_insert(void)
{
	TEST("insert item into hashtable");

	struct hashtable *this = hashtable_new(DEFAULT_HASHTABLE_SIZE);
	assert(this != NULL);

	/* we can break this particular hash  and choose a bin an index j of the table
	 * to insert an item by supplying a string of length 2 (including \0)
	 * whose first character is equivalent (in ASCII) to i modulo the size
	 * of the table. Neat.
	 * By adding on multiples of the table size (j) we can get different values
	 * in same bin. We can then use both this to test the linked lists with ease. */
	/* So, insert 10 items into every bin of the hashtable */


	char *words[151] = {
		"In", "our", "experience", "C", "has", "proven", "to", "be", "a",
		"pleasant", "expressive", "and", "versatile", "language", "for",
		"a", "wide", "variety", "of", "programs", "It", "is", "easy", "to",
		"learn", "and", "it", "wears", "well", "as", "ones", "experience",
		"with", "it", "grows", "We", "hope", "that", "this", "book", "will",
		"help", "you", "to", "use", "it", "well", "The", "thoughtful",
		"criticisms", "and", "suggestions", "of", "many", "friends", "and",
		"colleagues", "have", "added", "greatly", "to", "this", "book",
		"and", "to", "our", "pleasure", "in", "writing", "it", "In",
		"particular", "Mike", "Bianchi", "Jim", "Blue", "Stu", "Feldman",
		"Doug", "McIlroy", "Bill", "Roome", "Bob", "Rosin", "and", "Larry",
		"Rosler", "all", "read", "multiple", "volumes", "with", "care", "We",
		"are", "also", "indebted", "to", "Al", "Aho", "Steve", "Bourne",
		"Dan", "Dvorak", "Chuck", "Haley", "Debbie", "Haley", "Marion",
		"Harris", "Rick", "Holt", "Steve", "Johnson", "John", "Mashey", "Bob",
		"Mitze", "Ralph", "Muha", "Peter", "Nelson", "Elliot", "Pinson", "Bill",
		"Plauger", "Jerry", "Spivack", "Ken", "Thompson", "and", "Peter",
		"Weinberger", "for", "helpful", "comments", "at", "various", "stages",
		"and", "to", "Mile", "Lesk", "and", "Joe", "Ossanna", "for",
		"invaluable", "assistance", "with", "typesetting"
	};

	int i;
	for (i = 0; i < 151; i++){
		hashtable_insert(this, words[i]);
	}

	hashtable_free(this);
	PASS;
}


void test_hashtable_locate(void)
{
	TEST("locate item in hashtable, delete item from hashtable");
	struct hashtable *this = hashtable_new(DEFAULT_HASHTABLE_SIZE);

	char *words[6] = {
		"Stu", "Blue", "Jim", "various", "Spivack", "Marion"
	};



	int i;
	for (i = 0; i < 6; i++){
		hashtable_insert(this, words[i]);
	}

	for (i = 0; i < 6; i++){
		assert(hashtable_locate(this, words[i], 0));
	}
	printf("\n");

	hashtable_drop(this, "Jim");
	assert(!hashtable_lookup(this, "Jim"));
	hashtable_free(this);

	PASS;
}


void test_hashtable_free(void)
{
	TEST("free all allocted pointers of hashtable");
	struct hashtable *this = hashtable_new(DEFAULT_HASHTABLE_SIZE);

	char * words[48] = {
		"Peter", "Jerry", "read",
		"Elliot", "all", "it",
		"assistance", "comments", "Bianchi",
		"invaluable", "for", "and",
		"Stu", "Blue", "Jim",
		"Various", "Spivack", "Harris",
		"Marion", "Mike", "thoughtful",
		"Johnson", "Steve", "Debbie",
		"are", "We", "with",
		"at", "pleasure", "thisworkz",
		"Joe", "Ken", "expressive",
		"In", "in", "programs",
		"variety", "this", "typesetting",
		"Mitze", "ones", "typesettinh",
		"Larry", "grows", "learn",
		"Bob", "John", "Holt"
	};

	int i;
	for (i = 0; i < 48; i++){
		hashtable_insert(this, words[i]);
	}

	hashtable_free(this);
	PASS;
}

int main(void)
{
	test_hash_string();
	test_hashtable_new();
	test_node_new();
	test_hashtable_insert();
	test_hashtable_locate();
	test_hashtable_free();

	/* we'll only get to this line if all the previous
	 * assertions didn't fail */
	printf("Passed all tests!\n");
	return 0;
}

