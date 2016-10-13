CS2014 Lab 3 : Simple Sets with Arrays

Thursday 16th October

It's common to want to store sets of items. One simple way to do this
is to keep an array of the items in the set. In this lab you will
build an abstract datatype (ADT) to store sets in this way.

The basic building block of the ADT will be the structure that acts as
the main ADT object. The type of this structure should be something
like:
struct int_set {
       int * array;
       int max_elements;
       int current_elements;
};

Your ADT should support the following methods:
// create a new, empty set
struct int_set * int_set_new();

// check to see if an item is in the set
// returns 1 for true, 0 for false
int int_set_lookup(struct int_set * this, int item);

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
int int_set_add(struct int_set * this, int item);

// remove an item with number 'item' from the set
// has no effect if the items is not in the set
int int_set_remove(struct int_set * this, int item);

// place the union of src1 and src2 into dest
void int_set_union(struct int_set * dest, struct int_set * src1,
                  struct int_set * src2);

// place the intersection of src1 and src2 into dest
void int_set_intersect(struct int_set * dest, struct int_set * src1,
                       struct int_set * src2);

Your set should be capable of dealing with any number of items. So if
the array you are using to store the items in the set becomes full,
you should create a new large array, copy the items from the old array
to the new, and free the old array.

At any time there will probably be some free slots in the internal
array used to store the items in the set, but your implementation
should limit the total amount of free slots. At any time the number
of free slots should not exceed the maximum of the following two values:
(a) Half the number of items in the set
(b) 16

If at any time your array has more than the allowed number of free
slots you should allocate a new, smaller array, copy the contents of
the existing array to the smaller one, and then free the original
array.

Note that to create a new, empty set, your code might look something
like:
// create a new, empty set
struct int_set * new_int_set()
{
	// create set
	struct int_set * new_set = malloc(sizeof(struct int_set));
	// populate fields
	new_set->array = malloc(sizeof(int) * MIN_SIZE);
	new_set->max_elements = MIN_SIZE;
	new_set->current_elements = 0;

	return new_set;
}

This lab will be marked, and will count towards your end of year mark.
You should submit your project work on Wednesday 22nd October 2014
using the Blackboard system. To be marked, you must demonstrate and
answer questions on your project at your regular lab session on
Thursday 23rd October. You must demonstrate the same code that you
submit. All work should be your own.
