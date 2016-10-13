#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


struct bitfile {
	FILE *fh;
	unsigned char buffer;
	int fh_eof;
	int index;
};

/* return a pointer to a bitfile, depending on the given
 * mode. This behaves exactly as fopen(filename, mode) does,
 * for modes of w and r.
 * */
struct bitfile *bfopen(const char *filename, const char *mode);

/* close the given bitfile, writing out the buffer */
int bfclose(struct bitfile *this);

/* write a single bit to the bitfile and advance
 * the write pointer, just like fputc */
int bfputb(const int bit, struct bitfile *this);

/* read a single bit from the bitfile and advance
 * the read pointer, just like fgetc.
 * If we have reached the end of the file, EOF is
 * returned, again, just like fgetc.
 * */
int bfgetb(struct bitfile *this);
