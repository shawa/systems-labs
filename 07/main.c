#include "huffman_tree.h"

/* the number of possible characters which fit into a char */
const int CHARACTER_UNIVERSE = 256;
int *character_frequencies(FILE *fh, int char_universe_size)
{
	unsigned char c;
	int *char_count = malloc(sizeof(int) * char_universe_size);
	memset(char_count, 0, sizeof(int) * char_universe_size);

	do {
		c = fgetc(fh);
		char_count[c] += 1;
	} while(!feof(fh));

	return char_count;
}


static void usage(char* progname)
{
	char *docstring =
		"%s. print huffman tree for file\n"
		"usage: %s < <file name>\n"
		"       %s <file name>";

	printf(docstring, progname, progname, progname);
}

/* Read in the given filename, build a character count out of it,
 * build a huffman tree out of _that_, then print it out.
 *
 * Of course we make sure to free everything.
 * */
int main(int argc, char *argv[])
{
	FILE *source_file;
	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			usage(argv[0]);
			exit(0);
		} else {
			char *filename = argv[1];
			source_file = fopen(filename, "r");
			assert(source_file != NULL);
		}
	} else {
		source_file = stdin;
	}

	int *char_count = character_frequencies(source_file, CHARACTER_UNIVERSE);
	fclose(source_file);

	struct huff_symbol *huffman_tree = huff_tree_new(char_count);
	free(char_count);

	huff_tree_print(huffman_tree);
	huff_tree_free(huffman_tree);

	return 0;
}
