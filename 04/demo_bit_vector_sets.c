#include "bit_vector_sets.c"
#include <string.h>
#include <limits.h>
#include <stdio.h>

#ifndef LINE_MAX
#define LINE_MAX 128
#endif

/*ANSI escape codes */
/* declares the start of text to be coloured blue */
#define KBLU "\x1B[34m"
/* declares the start of text to be uncoloured */
#define KNRM "\x1B[0m"

const int ASCII_8_BIT_LIMIT = 255;

/* strips trailing newline character from 'string' */
void chomp(char *string)
{
	int index = strlen(string) - 1;
	if (string[index] == '\n')
		string[index] = '\0';
}


/* return a bitset built from an input string */
struct bitset *to_set(char *string)
{
	struct bitset *char_set = bitset_new(ASCII_8_BIT_LIMIT);
	while(*string != '\0') {
		bitset_add(char_set, (unsigned char)*string);
		string++;
	}

	return char_set;
}

/* return a string of all the elements in 'this',
 * interpreted as unsigned characters
 *
 * if the set is empty, return the empty string
 */
char *to_string(struct bitset *this)
{
	char *string = malloc(sizeof(unsigned char)*this->universe_size + 1);
	int i, num_items;
	for(i = 0, num_items = 0; i < this->universe_size; i++) {
		if(bitset_lookup(this, i)) {
			string[num_items] = (char)i;
			num_items++;
		}
	}

	if (num_items == 0) {
		return "";
	} else {
		string = realloc(string, sizeof(unsigned char) * num_items);
		return string;
	}
}


/* read in two lines, then print:
 * - the set of all characters in line 1
 * - the set of all characters in line 2
 * - the union of line 1 and line 2
 * - the intersection of line 1 and line 2
 */
int main()
{
	printf("enter two lines, each terminated by the enter key\n");
	char buffer[LINE_MAX];

	fgets(buffer, LINE_MAX, stdin);
	chomp(buffer);
	struct bitset *line_1 = to_set(buffer);

	fgets(buffer, LINE_MAX, stdin);
	chomp(buffer);
	struct bitset *line_2 = to_set(buffer);

	struct bitset *line_union = bitset_new(ASCII_8_BIT_LIMIT);
	bitset_union(line_union, line_1, line_2);

	struct bitset *line_intersect = bitset_new(ASCII_8_BIT_LIMIT);
	bitset_intersect(line_intersect, line_1, line_2);

	printf("\n   line 1 = " KBLU "{" KNRM "%s" KBLU "}" KNRM "\n"
	       "   line 2 = " KBLU "{" KNRM "%s" KBLU "}" KNRM "\n"
	       "    union = " KBLU "{" KNRM "%s" KBLU "}" KNRM "\n"
	       "intersect = " KBLU "{" KNRM "%s" KBLU "}" KNRM "\n",
	       to_string(line_1),
	       to_string(line_2),
	       to_string(line_union),
	       to_string(line_intersect));
}
