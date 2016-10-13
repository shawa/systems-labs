#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


struct hashtable {
	size_t size;
	struct node **table;

	unsigned (*hash_function)(char*);
};

/* return a pointer to an empty hashtable using the default
 * hashing algorithm */
struct hashtable *hashtable_new(size_t size);

/* free all allocated memory to the hashtable
 * NB: Cannot free pointers to client-allocated
 * memory, clean up after yoursefl! */
void hashtable_free(struct hashtable *this);

/* insert an element into the given hashtable */
void hashtable_insert(struct hashtable *this, char *data);

/* find and remove the given element from the hashtable
 * if the item is not found, the hashtable is unchanged */
void hashtable_drop(struct hashtable *this, char *data);

/* returns 1 if the given element is present in the hashtable
 * 0 otherwise */
int hashtable_lookup(struct hashtable *this, char *data);

/* dump the contents of the given hashtable to console */
void hashtable_print(struct hashtable *this);


