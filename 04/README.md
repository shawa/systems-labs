CS2014 Lab 4 : Bit Vector Sets

Thursday 23rd October

Write an abstract data type (ADT) to represent sets of items, where
the class of items that the set is chosen from is relatively
small. You should use bit vectors to represent the class. A bit vector
is an array of some (usually unsigned) integer type. Each bit in each
integer is used to represent the presence or absence of one item from
the class of items that can belong to the set.

Your ADT, called bitset should support the following methods:
// create a new, empty bit vector set of 'size' items
struct bitset * biset_new(int size);

// check to see if an item is in the set
// returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
int bitset_lookup(struct bitset * this, int item);

// add an item, with number 'item' to the set
// (returns 0 if item is out of bounds, 1 otherwise)
// has no effect if the item is already in the set
int bitset_add(struct bitset * this, int item);

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(struct bitset * this, int item);

// place the union of src1 and src2 into dest
void bitset_union(struct bitset * dest, struct bitset * src1,
		  struct bitset * src2);

// place the intersection of src1 and src2 into dest
void bitset_intersect(struct bitset * dest, struct bitset * src1,
                  struct bitset * src2);

Once you have constructed your ADT, write a small test program that
reads in two lines of text from the user. You program should write out
(1) the set of characters appearing in the first line; (2) the set of
characters appearing in the second line; (3) the union of sets (1) and
(2); (4) the intersection of sets (1) and (2).

(Hint: recall that in C a character is simply a one-byte integer, and
a string is simply an array of characters. If you cast each character
to an unsigned character, you are guaranteed to have a number in the
range 0 to 255.)

Note that you must create and use a bitset ADT in your program if you
want the marks for this lab.

This lab will be marked, and will count towards your end of year mark.
You should submit your project through Blackboard by 11.59PM on
Wednesday 29th October. To be marked, you must demonstrate and answer
questions on your project at your regular lab session on Thursday 30th
October. You must demonstrate the same code that you submit. All work
should be your own.
