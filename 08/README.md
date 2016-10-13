# Notes:


The 'clearly documented' end of file documentation is located in both header files:
`huffman_tree.h`, and `bitfile.h`.

Files prefixed with `test_` are little unit tests and may be ignored.

Program passes through valgrind with no leaks for both coding

```
==28100== Command: ./huffcode resources/modern-prometheus.unix.txt resources/ulysses.txt test_out.bf
==28100== 
==28100== 
==28100== HEAP SUMMARY:
==28100==     in use at exit: 0 bytes in 0 blocks
==28100==   total heap usage: 775 allocs, 775 frees, 37,847 bytes allocated
==28100== 
==28100== All heap blocks were freed -- no leaks are possible
==28100== 
==28100== For counts of detected and suppressed errors, rerun with: -v
==28100== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)
```

and decoding:
```
==28235== Command: ./huffdecode resources/modern-prometheus.unix.txt test_out.bf reconstruct.txt
==28235== 
==28235== 
==28235== HEAP SUMMARY:
==28235==     in use at exit: 0 bytes in 0 blocks
==28235==   total heap usage: 775 allocs, 775 frees, 37,847 bytes allocated
==28235== 
==28235== All heap blocks were freed -- no leaks are possible
==28235== 
==28235== For counts of detected and suppressed errors, rerun with: -v
==28235== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

```

***

# CS2015 Lab 8 : Huffman Coder/Decoder and Files

Thursday 4th December 2014

A coder/decoder (codec) is a piece of software that can encode
or decode a stream of data. The goal of this lab is to construct
a codec that can compress plain text files using Huffman coding,
and decode compressed files back to plain text.

In lab 7 you constructed a program that computes Huffman codes for
each of the 256 characters based on the frequency of each character in
a given "training" file. In the current lab you will extend this
program to a Huffman codec using the codes computed from your code in
lab 7.

It should be possible to invoke your program in two ways:
```
huffcode <training filename> <input filename> <output filename>
```
```
huffdecode <training filename> <input filename> <output filename>
```

The training file is used to provide character frequency information
that can be used to build the Huffman tree. When your program is
invoked with the name "huffcode" the input file is a plain text file,
and the program should output an encoded file. When your program is
invoked with the name "huffdecode" the input file is a Huffman coded
file, and the program should output the corresponding plain text file.

Note that Huffman encoding involves taking a character set with
fixed-length codes (the C character set) and generating a file
where different characters have different lengths. It will therefore
be necessary to pack individual bits into bytes, and the boundary
of any character in the Huffman coded file will only coincide with
a byte boundary by chance.

In order to deal with this problem, construct an abstract datatype
that represents a file that allows a single bit to be read from or
written to the file. The C programming language does not allow reads
or writes of less than one byte, and therefore you will need to create
a buffer that temporarily stores individual bits that will have
recently been read from the C file but not yet used, or recently
written to the abstract data type file, but have not yet been flushed
to the C file.

Note that when Huffman encoding, you need some way to indicate the
end of the file. There are several different ways that this can be
done, and you should clearly document your solution.

For testing the code we will be using the following file:
https://www.cs.tcd.ie/David.Gregg/cs2014/labs/modern-prometheus.unix.txt

This lab will be marked, and will count towards your end of year mark.
You should submit your lab via the Blackboard system by TUESDAY 16th
December. You will need to demonstrate your submitted code at a session
that hasn't yet been confirmed, but will probably be Thursday 18th.
For those who will not be around that week, it is possible to submit the
code early, and demonstrate at the regular lab on Thursday 11th.
