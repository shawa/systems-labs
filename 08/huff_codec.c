#include "huffman_tree.h"

/* the number of possible characters which fit into a char */
const int CHARACTER_UNIVERSE = 256;

/* from a given file, count the frequency of every character
 * appearing within the range [0, char_universe_size], and
 * return an array of ints char_count, where char_count[c]
 * is the frequency of a given character c*/
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
	char *docstring;
	if (strcmp(progname, "./huffcode") == 0) {

		docstring =
			"%s. compress a file according to given training file\n"
			"usage: %s <training file> <input> <output>\n";

	} else if (strcmp(progname, "./huffdecode") == 0) {
		docstring =
			"%s. decompress a file according to given training file\n"
			"usage: %s <training file> <input> <output>\n";

	} else {
		docstring =
			"%s. huffman codec \n"
			"'%s': invalid mode, link and call program as\n"
			"either ./huffcode or ./huffdecode \n";
	}

	printf(docstring, progname, progname);
}

int main(int argc, char *argv[])
{
	if (argc != 4) {
		usage(argv[0]);
		exit(0);
	}

	char *mode = argv[0];
	char *training_file_name = argv[1];
	char *input_file_name = argv[2];
	char *output_file_name = argv[3];


	FILE *training_file = training_file = fopen(training_file_name, "r");
	assert(training_file != NULL);
	int *char_count = character_frequencies(training_file, CHARACTER_UNIVERSE);
	fclose(training_file);

	struct huff_symbol *huffman_tree = huff_tree_new(char_count);
	free(char_count);

	int **symbols = huff_tree_symbols(huffman_tree);
	assert(symbols != NULL);

	if (strcmp(mode, "./huffcode") == 0) {
		struct bitfile *outfile = bfopen(output_file_name, "w");
		FILE *infile = fopen(input_file_name, "r");
		huff_compress(symbols, outfile, infile);
		fclose(infile);
		bfclose(outfile);
	} else if (strcmp(mode, "./huffdecode") == 0) {
		FILE *outfile = fopen(output_file_name, "w");
		assert(outfile != NULL);
		struct bitfile *infile = bfopen(input_file_name, "r");
		assert(infile != NULL);
		huff_decompress(huffman_tree, infile, outfile);
		bfclose(infile);
		fclose(outfile);
	} else {
		usage(argv[0]);
	}

	huff_tree_free(huffman_tree);
	for (int i = 0; i < CHARACTER_UNIVERSE; i++) {
		free(symbols[i]);
	}
	free(symbols);

	return 0;
}
