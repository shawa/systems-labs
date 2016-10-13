# CS2015 Lab 7 : Huffman Coding, Tree Data Structures and Unions
> Thursday 27th November 2014

Huffman coding can be used to remap the encoding of characters so that
the frequent characters require fewer bits than less frequent
characters. Typically, the frequencies are based on looking at some
sample text files to get some estimate of the relative commonness of
different characters.

The basic approach of Huffman coding is as follows:

* List all possible characters with their frequencies
* Locate the characters with the smallest frequencies
* Replace these with a pseudo character pair representing them both,
  whose frequency is the sum of the individual frequencies
* Repeat until the list contains only one member

This process builds a tree-like structure of nested pairs, with real
characters at the leaves. To find the encoding of a character,
traverse the tree from the root to that character and record 0 for a
left branch and 1 for a right branch.

Write a C program that reads in a file of text and computes Huffman
codes for all the characters based on the frequencies of the
characters. You should write out to the screen each of the characters
and the corresponding encodings. One common problem is that some
characters may not appear in the sample file at all; these should be
assigned a frequency of 1, to make sure that they get some sort of
sensible encoding.

In your solution you should build a linked tree structure representing
the Huffman tree. You nodes of the tree should come in two varieties:
1. simple nodes representing a single character and
2. compound nodes representing a pair of (possibly compound) characters

In C there is no inheritance mechanism that allows you to have different
types of nodes in the same data structure. You should instead use
a single node structure type, and this node should internally use
a C union type.

The following code reads in the contents of a file character by
character.

```.{c}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char ** argv)
{
  unsigned char c;
  File * file;

  if ( argc != 2 ) {
    fprintf(stderr, "Useage: huffman <filename>\n");
    exit(1);        // exit with error code
  }

  file = fopen(argv[1], "r");
  assert( file != NULL );
  c = fgetc(file);
  while( !feof() ) {
    printf("%c", c);
    c = fgetc(file);
  }
  fclose(file);

  return 0;
}
```

Your program should take a command line parameters as follows:

```
./huffman <filename>
```

The command line parameter should be the name of a file that is
used to train the Huffman coder, and should be used to compute the
frequencies of each character. These frequencies should be used to
compute the mapping from characters to Huffman codes, and you should
write a table of the mappings to the standard output.

For testing the code we will be using the [following file](https://www.cs.tcd.ie/David.Gregg/cs2014/labs/modern-prometheus.unix.txt)

This lab will be marked, and will count towards your end of year mark.
You should submit your lab via the Blackboard system by Wednesday 3rd
December, and demonstrate your code on Thursday 4th. You must
demonstrate the same code that you submit. All work should be your
own.
