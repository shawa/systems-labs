# CS2014 Lab 6 : Hash Tables

> Thursday 13th November

Hash tables are one of the most important and commonly used data
structures. Insertion, deletion and retrieval from a hash table are
average-case constant time (i.e. `O(1)`) operations. There are simple
versions of hash tables that are easy to implement (although some more
sophisticated versions can be complicated). In contrast, balanced
binary trees are difficult to implement, and have worse average case
performance.

Implement a hash table abstract data type in C. Each hash table object
will be able to hold a set of strings. You should use chaining for
collision resolution in your hash table. That is, each element of the
hash table should be a linked list, and where a collision occurs, just
add a new element to the list at that point in the hash table. Your
abstract data type should look something like:

```{.c}
struct node {
  char * data;
  node * next;
};

struct hashtable {
  int size;
  node ** table;
};

// construct a new hash table with size elements
struct hashtable * hashtable_new(int size);

// free the memory for all parts of the hashtable
void hashtable_free(struct hashtable * this);

// insert string into the hash table, no effect if it's already there
void insert(struct hashtable * this, char * item);

// remove string from the hash table, no effect if not in table
void remove(struct hashtable * this, char * item);

// return 1 if string is already in table, 0 otherwise
int lookup(struct hashtable * this, char * item);

// print out each entry in the hash table and the values
// stored at that entry
void print(struct hashtable * this);       
```
There are lots of different ways that you can compute a hash
value for a string. For simplicity, the best thing is to use
the following simple function:
```{.c}
unsigned hash_string(char * str)
{
  unsigned hash = 0;
  for ( int i = 0; str[i] != '\0'; i++ ) {
    hash = hash * 37 + str[i];
  }
  return hash;
}
```

Write a small C program that tests your abstract data type. Your
program should take several strings as command line parameters to your
program (that is you should access them through `argc` and `argv`).  You
program should then add the string "fish" to the your hash table and
remove the string "porridge" if it is in the table. Your program
should write out the contents of your hash table entry by entry. For
example, the output might look something like:

```
0: <empty>
1: I
2: <empty>
3: am
4: a fish
5: <empty>
6: <empty>
7: glub
8: <empty>
```

Hashing and hash tables are a fascinating topic and there is a great
deal more that can be learned about this. This lab is a basic
introduction.

This lab will be marked, and will count towards your end of year mark.
You should submit your project work on Wednesday 19th November 2013
using the Blackboard system. To be marked, you must demonstrate and
answer questions on your project at your regular lab session on
Thursday 20th November. You must demonstrate the same code that you
submit. All work should be your own.

