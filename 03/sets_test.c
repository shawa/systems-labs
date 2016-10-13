#include "sets.c"
#include <assert.h>

void test_swap()
{
	int numbers[] = {0, 1, 2, 3, 4, 5};
	swap(numbers, 1, 5);
	assert(numbers[1] == 5 && numbers[5] == 1);
}

int isSorted(int *array, int length)
{
	int i;
	for (i = 0; i < length-1; i++){
		if (array[i] > array[i+1]) {
			return 0;
		}
	}

	return 1;
}

void int_set_dump(struct int_set *this)
{
	int i;
	fprintf(stderr, "Max: %d, Cur: %d\n",
	        this->max_elements, this->current_elements);

	for (i = 0; i < this->current_elements; i++) {
		fprintf(stderr, "%d ", this->array[i]);
	}

	fprintf(stderr, "\n");
}

void test_insertionSort()
{
	int length = 6;
	int numbers[] = {0, 3, 1, 5, 2, 4};
	assert(!isSorted(numbers, 6));

	insertionSort(numbers, 6);
	assert(isSorted(numbers, 6));
}

void test_binarySearch()
{
	int numbers[] = {0, 1, 2, 3, 4, 5};

	int i, len;
	for (len = 1; len <= 6; len++)
	for (i = 0; i < len; i++) {
		assert(binarySearch(numbers, numbers[i], 0, len) == i);
	}


}

void test_int_set_new()
{
	struct int_set *this  = int_set_new();

}

void test_int_set_lookup()
{
	struct int_set *this = int_set_new();

	int_set_add(this, 19);
	assert(int_set_lookup(this, 19));
}

void test_int_set_add()
{
	struct int_set *this  = int_set_new();

	int i;
	for (i = 128; i > 0; i--) {
		int_set_add(this, i);
	}
	assert(this->current_elements == 128);
	int_set_add(this, 100);

	assert(isSorted(this->array, this->current_elements));
}

void test_int_set_remove() {
	struct int_set *this = int_set_new();

	int i;
	for (i = 1; i <= 10; i++) {
		int_set_add(this, i);
	}

	for (i = 1; i < 10; i++) {
		int_set_remove(this, i);
	}
	int_set_dump(this);

}

void test_int_set_union()
{
	struct int_set *dest = int_set_new();
	struct int_set *src1 = int_set_new();

	int i;
	for (i = 1; i <= 10; i++) {
		int_set_add(src1, i);
	}
	struct int_set *src2 = int_set_new();
	for (i = 11; i <= 20; i++) {
		int_set_add(src2, i);
	}

	int_set_union(dest, src1, src2);
	int_set_dump(dest);
}


void test_int_set_intersection()
{
	struct int_set *dest = int_set_new();
	struct int_set *src1 = int_set_new();

	int i;
	for (i = 1; i <= 10; i++) {
		int_set_add(src1, i);
	}
	struct int_set *src2 = int_set_new();
	for (i = 5; i <= 15; i++) {
		int_set_add(src2, i);
	}

	int_set_intersection(dest, src1, src2);
	int_set_dump(dest);
}


void lab_test()
{
	int num1[] = {1, 1, 2, 2};
	int num2[] = {2, 2, 3, 3};

	struct int_set *onion = int_set_new();
	struct int_set *intersect = int_set_new();
	struct int_set *src1 = int_set_new();
	struct int_set *src2 = int_set_new();

	int i;
	for (i = 0; i < 4; i++){
		int_set_add(src1, num1[i]);
	}
	int_set_dump(src1);

	for (i = 0; i < 4; i++){
		int_set_add(src2, num2[i]);
	}
	int_set_dump(src2);

	int_set_union(onion, src1, src2);
	int_set_dump(onion);

	int_set_intersection(intersect, src1, src2);
	int_set_dump(intersect);

}

int main(void)
{
//	test_swap();
//	test_insertionSort();
//	test_binarySearch();
//	test_int_set_new();
//	test_int_set_lookup();
//	test_int_set_add();
//	test_int_set_remove();
//	test_int_set_union();
//	test_int_set_intersection();

	lab_test();
	return 0;
}
