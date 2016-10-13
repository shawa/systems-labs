#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "bitfile.c"
const char *TEST_WRITE_FILE = "test_out.bf";

void test_bitfile_new(void)
{
	struct bitfile *bf = bfopen(TEST_WRITE_FILE, "w");
	assert(bf->fh != NULL);
	assert(bf->buffer == 0x00);
	assert(bf->index == -1);

}

/* Grandmother, what unrolled loops you have! */
void test_bfputb(void)
{
	struct bitfile *bf = bfopen(TEST_WRITE_FILE, "w");
	assert(bf->index == -1);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b10000000);
	assert(bf->index == 0);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11000000);
	assert(bf->index == 1);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11100000);
	assert(bf->index == 2);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11110000);
	assert(bf->index == 3);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11111000);
	assert(bf->index == 4);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11111100);
	assert(bf->index == 5);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11111110);
	assert(bf->index == 6);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b11111111);
	assert(bf->index == 7);

	assert(bfputb(1, bf) == 1);
	assert(bf->buffer == 0b10000000);
	assert(bf->index == 0);

	assert(bfputb(1, bf) == 1);
	assert(bfputb(0, bf) == 0);
	assert(bfputb(1, bf) == 1);

	unsigned char file_byte = 0;
	file_byte = fgetc(bf->fh);
	assert(file_byte == 0xff);

	bfclose(bf);

}


void test_bfgetb()
{
	struct bitfile *bf = bfopen(TEST_WRITE_FILE, "r");
	assert(feof(bf->fh) == 0);

	int vals[16] = {1,1,1,1, 1,1,1,1, 1,1,0,1, 0,0,0,0};
	int val = 0;
	for (int i = 0; i < 16; i++) {
		val = bfgetb(bf);
		assert(val != -1);
		assert(val == vals[i]);
	}
	assert(bfgetb(bf) == -1);
}

int main(void)
{
	test_bitfile_new();
	test_bfputb();
	test_bfgetb();
}
