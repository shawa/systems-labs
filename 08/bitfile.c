#include "bitfile.h"

/* Bitfile operation definitions. We try to match stdio as
 * much as possible in terms of interface, for fopen, fclose,
 * fgetc, fputc etc.
 * */

const int BYTE_MAX_INDEX = 7;
static void bit_array_put(unsigned char *this, int i, int val)
{
	unsigned char mask = (0x80 >> i);
	if (val)
		*this |= mask;
	 else
		*this &= ~mask;

}

/* the inline actually speeds this up quite a bit (~3x),
 * according to rudimentary benchmarks*/
static inline int bit_array_get(unsigned char this, int i)
{
	/* shift the array to the right until the
	 * entry we are interested in is at the 'end'
	 * e.g.:
	 *
	 * i = 2, so shift (7-2 -> 5) entries right
	 *
	 *      |-5--|
	 *  [00i0 0010] >> 5 ---> [0000 000i]
	 ***/
	this >>= (7-i);

	/*
	 *  Then AND with 1 to 'extract' its value:
	 *   0000 0001 &
	 *   0000 000i
	 *
	 * = i & 1
	 * = 1 if i == 1,
	 *   otherwise 0
	 *
	 ***/
	return this & 0x01;
}


/* Allocate a new bitfile structure, and open a new
 * file handle to write to/read from. If we're opening
 * a new file to write, initialise the buffer to 0x00, other-
 * wise, assign it byte read from the file handle*/
struct bitfile *bfopen(const char *filename, const char *mode)
{
	struct bitfile *result = malloc(sizeof(struct bitfile));
	assert(result != NULL);
	result->fh = fopen(filename, mode);

	if (strcmp(mode, "w") == 0) {
		result->buffer = 0x00;
		result->fh_eof = 1;
	} else if (strcmp(mode, "r") == 0) {
		result->buffer = fgetc(result->fh);
		result->fh_eof = 0;
	} else {
		free(result);
		fprintf(stderr, "Bad mode: %s", mode);
		return NULL;
	}

	/* we start at -1 to indicate the file has
	 * not yet been read from or written to */
	result->index = -1;
	return result;
}


/* bitfile closing, as well as structure freeing i
 * first flush the buffer out to the file handle,
 * then free the structure */
int bfclose(struct bitfile *this)
{
	fputc(this->buffer, this->fh);
	int result = fclose(this->fh);
	free(this);
	return result;
}



/* write a single bit to the bitfile. We maintain
 * an internal bit array, as defined by the two
 * function above. Once we reach the end of the bit
 * array, write out the buffer to the file */
int bfputb(const int bit, struct bitfile *this)
{
	if (this->index == BYTE_MAX_INDEX) {
		fputc(this->buffer, this->fh);
		this->fh_eof = 0;
		this->buffer = 0x00;
		this->index = 0;
	 } else {
		this->index += 1;
	 }

	bit_array_put(&(this->buffer), this->index, bit);

	return bit;
}


/* behaves symetrically to bfputb; except we
 * replace the buffer with a file read from the
 * bitfile's file handle when we reach the end.
 *
 * For the moment, consecutive reading and writing
 * from the same bitfile object is undefined.*/
int bfgetb(struct bitfile *this)
{
	if (this->index == BYTE_MAX_INDEX) {
		this->buffer = fgetc(this->fh);
		if (feof(this->fh)) return EOF;
		this->index = 0;
	} else {
		this->index += 1;
	}


	int result = bit_array_get(this->buffer, this->index);
	return result;
}
