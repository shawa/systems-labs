#include "hashtable.h"

void usage(char *progname)
{
	char *docstring =
		"hashtable sample client\n"
		"inserts given elements into hashtable and prints visualisation\n"
		"of resulting data structutre \n"
		"usage: %s <entry 1 [entry 2 [...]...]>";

	printf(docstring, progname);
}

int main(int argc, char **argv){
	if (argc == 1) {
		usage(argv[1]);
		return 0;
	}

	struct hashtable *spurious = hashtable_new(8);
	int i;
	for (i = 1; i < argc; i++) {
		hashtable_insert(spurious, argv[i]);
	}

	printf("Resultant hashtable:\n\n");
	hashtable_print(spurious);
	printf("\n");

	printf("Inserting \"fish\"\n");
	hashtable_insert(spurious, "fish");

	printf("Removing \"porridge\"\n");
	hashtable_drop(spurious, "porridge");

	printf("Final resultant hashtable\n");
	hashtable_print(spurious);

	hashtable_free(spurious);
	return 0;
}
