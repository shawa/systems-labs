#include <stdlib.h>
#include <stdio.h>

#define INITIAL_MAX 16
#define MAX(a,b) ((a > b)? a : b)

struct int_set {
	int max_elements;
	int current_elements;
	int *array;
};


void swap(int *array, int a, int b)
{
	int tmp;
	tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void insertionSort(int *array, int length)
{
	int i, j;
	for (i = 0; i < length; i++) {
		j = i;
		while(array[j-1] > array[j] && j > 0) {
			swap(array, j, j-1);
			j--;
		}
	}
}

int binarySearch(int *array, int item, int lo, int hi)
{
	int mid;
	while (lo <= hi) {
		mid = (lo + hi) / 2;

		if (item > array[mid]) {
			lo = mid + 1;
		} else if (item < array[mid]) {
			hi = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;

}


struct int_set *int_set_new()
{
	struct int_set *new_set = malloc(sizeof(struct int_set));

	new_set->max_elements = INITIAL_MAX;
	new_set->current_elements = 0;
	new_set->array = malloc(sizeof(int) * 16);

	return new_set;
}


void int_set_resize(struct int_set *this, int shouldShrink)
{
	int new_size = shouldShrink? this->max_elements / 2  //half the size
	                           : this->max_elements * 2; //double the size

	this->array = realloc(this->array, sizeof(int) * new_size);
	this->max_elements = new_size;
}


int int_set_lookup(struct int_set *this, int key)
{
	if (binarySearch(this->array, key, 0, this->current_elements) != -1) {
		return 1;
	} else {
		return 0;
	}
}

int int_set_add(struct int_set * this, int item)
{
	if (int_set_lookup(this, item)) {
		return 0;
	} else {

		if (this->current_elements + 1 > this->max_elements) {
			int_set_resize(this, 0);
		}


		this->array[this->current_elements] = item;
		this->current_elements++;
		insertionSort(this->array, this->current_elements);
		return 1;
	}
}


void drop_item(int *this, int index, int length)
{
	swap(this, index, length-1);
}

int int_set_remove(struct int_set *this, int item)
{
	if (!int_set_lookup(this, item)) {
		return 0;
	} else {
		int index = binarySearch(this->array, item, 0, this->current_elements);
		drop_item(this->array, index, this->current_elements);
		this->current_elements--;

		int free_slots = this->max_elements - this->current_elements;
		if (this->current_elements < free_slots &&
		    this->current_elements > INITIAL_MAX) {
			int_set_resize(this, 1);
		}

		return 1;
	}
}

void int_set_union(struct int_set * dest, struct int_set * src1,
                   struct int_set * src2)
{
		struct int_set *srcs[] = {src1, src2};

		int i, j;
		for (i = 0; i < 2; i++) {
				for (j = 0; j < srcs[i]->current_elements; j++) {
						int_set_add(dest, srcs[i]->array[j]);
				}
		}
}

void int_set_intersection(struct int_set * dest, struct int_set * src1,
                          struct int_set * src2)
{
		int i, item;
		for (i = 0; i < src1->current_elements; i++) {
				item = src1->array[i];
				if (int_set_lookup(src2, item))
						int_set_add(dest, item);

		}

}
