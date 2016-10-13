#include "hashtable.h"

const int PRIME_MODULUS = 37;
const int DEFAULT_HASHTABLE_SIZE = 16;


/* Compute and return the hash of a given string, according
 * to the algorithm provided in the problem specification
 *
 * this should only be accessible by implementations of the
 * hashtable, and not clients, hence we declare it as static
 * so that it can only be referenced by scopes within this
 * file
 * */
static unsigned hash_string(char *str)
{
	unsigned hash = 0;
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		hash = (hash * PRIME_MODULUS) + str[i];
	}
	return hash;
}


struct node {
	char *data;
	struct node *next;
};


/* Allocate and return a new node of a linked list
 * */
static struct node *node_new(char *data, struct node *next)
{
	struct node *this = malloc(sizeof(struct node));
	assert(this != NULL);
	this->data = data;
	this->next = next;

	return this;
}

/* Insert 'data' into the linked list. If the data is already
 * present, return, having done nothing to it.
 * */
void hashtable_insert(struct hashtable *this, char* data)
{
	if (hashtable_lookup(this, data)) return;

	size_t index = (size_t)(this->hash_function(data) % this->size);

	struct node *old_head = this->table[index];
	this->table[index] = node_new(data, old_head);
}


/* Locate an element in the hash table. If the 'delete' flag is set,
 * the item will also be removed. We can then define two simple functions
 * to expose as methods for lookup and delete*/
static int hashtable_locate(struct hashtable *this, char* data, int delete)
{
	size_t index = (size_t)(this->hash_function(data) % this->size);
	struct node *current, *previous;

	current = previous = NULL;


	current = this->table[index];
	if (current != NULL) {
		do {
			/* if the element has been located */
			if (strcmp(current->data, data) == 0) {
				if (delete) {
					if (previous == NULL) {
						this->table[index] = current->next;
						} else {
							previous->next = current->next;
						}

						free(current);
						current = NULL;
				}
				return 1;
			}
			previous = current;
			current = current->next;
		} while (current != NULL);
	}

	return 0;

}

/* Wrapper around the locate function. This and drop have essentially
 * the same logic, so we need only implement lookup and then
 * derive behavior from that.
 * */
int hashtable_lookup(struct hashtable *this, char *data)
{
	return hashtable_locate(this, data, 0);
}

void hashtable_drop(struct hashtable *this, char *data)
{
	hashtable_locate(this, data, 1);
}


/* Print out all of the entries in this to console
 * */
void hashtable_print(struct hashtable *this)
{
	size_t i;
	struct node *cur = NULL;
	for (i = 0; i < this->size; i++){
	cur = this->table[i];

	printf("%2lu:", i );
	if (cur == NULL) {
		printf("<empty>");
	} else {
		do {
			printf("%s ", cur->data);
			cur = cur->next;
		} while (cur != NULL);
	}
	printf("\n");
	}
}


/* Required by the freeing function of the hashtable
 * A recursive function, which will traverse the linked list
 * until the end, then, following the return chain,
 * free the memory that each 'next' member points to
 *
 * Using recursion is a simple way to avoid having to maintain
 * a load of 'prvious' pointers, or worse still, making
 * each bin a doubly-linked list
 * *
 * We need to modify the head pointer itself, so we ask
 * for a pointer to that pointer. */
static void kill_linked_list(struct node **head_ptr)
{
	/* if the reference pointer points to a NULL pointer */
	if (*head_ptr == NULL) {
		return;
	/* if the next member of the pointer pointed to by the given
	 * 'head_ptr' pointer
	 * points to null*/
	} else if ((*head_ptr)->next == NULL){
		free(*head_ptr);
		*head_ptr = NULL;
		return;
	} else {
		/* call this function on a pointer pointing to the
		 * next member, which is pointed to by the pointer pointed to
		 * by head_ptr.
		 * */
		kill_linked_list(&((*head_ptr)->next));
		free(*head_ptr);
		*head_ptr = NULL;
	}
}

/* Hashtable, we do this
 * in reverse order to how it was allocated:
 *
 * - free all of the nodes of each linked list
 * - free the memory allocated for all of the pointers to the
 *   heads of the linked list
 * - free the hashtable itself
 * */
void hashtable_free(struct hashtable *this)
{
	size_t i;
	for (i = 0; i < this->size; i++) {
		kill_linked_list(&(this->table[i]));
		kill_linked_list(&(this->table[i]));
	}

	free(this->table);
	free(this);
}

/* Hashtable constructor
 * For fun/ease of experimentation, each hashtable's hash
 * function is referenced as a function pointer, and calls to
 * lookup and add reference *this* hash function. This level of
 * indirection means that insertion and lookup is dependent only
 * on a proper implementation of this interface, and so client
 * code by someone who is a better programmer than I can supply a
 * better hash function to suit their needs.
 * */
struct hashtable *hashtable_new(size_t size)
{

	struct hashtable *this = malloc(sizeof(struct hashtable));
	assert(this != NULL);
	this->table = malloc(sizeof(struct node*) * size);
	assert(this->table != NULL);
	this->size = size;

	this->hash_function = hash_string;

	size_t i;
	for (i = 0; i < this->size; i++) {
		this->table[i] = NULL;
	}

	return this;
}


