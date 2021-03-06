CS2014 Lab 1 : Simple sorting

Thursday 25th September 2014

Log on to a Unix machine that you have access to. In LG12 most of the
machines run Linux and can be used directly. If you're not using a
Unix-like system, a good machine to use is macneill.scss.tcd.ie.
	ssh -X myusername@macneill.scss.tcd.ie

You can see a list of your files with:
        ls
Create a directory for cs2014 lab work:
        mkdir cs2014
Now switch to that directory:
        cd cs2014
Create a directory for your first lab:
        mkdir lab1
Now switch to that directory
        cd lab1

Download the following files to that directory.

http://www.cs.tcd.ie/David.Gregg/cs2014/labs/sorts.c
http://www.cs.tcd.ie/David.Gregg/cs2014/labs/numbers.txt

Open the C program using your favorite editor, such as pico, nano, vim or emacs
        nano sorts.c

To compile your program type one of the following:
        clang -o sorts sorts.c
        gcc -o sorts sorts.c
        cc -o sorts sorts.c

These are various C compilers. The standard C compiler on Unix systems
is called cc. Gcc is the GNU C compiler. On most Linux systems, the
gcc compiler is the standard compiler, so cc is just another name for
gcc. Clang is a relatively new C compiler. Its error messages are
usually much easier to understand than the error messages in
gcc. Typically gcc is installed on almost any Unix system, whereas
clang is rarer. However, clang is becoming increasingly popular
because its error messages are so much better than gcc's.

To run your program type:
        ./sorts

The file 'sorts.c' contains a simple program to read in some numbers
from a text file, sort them into increasing order, and write them to
the screen. The file 'numbers.txt' contains some numbers to sort.

The existing sorts.c program uses the "funny" sort algorithm to sort
the numbers. In addition there are prototypes, but no code for bubble
sort, selection sort and insertion sort. Write the code for these
sorts, and test it out in this program. For selection sort, you can
use the existing findMin function (if you want).

Next modify each sorting function so that it returns the number of
times that the inner loop of the sort is executed. Modify the main()
function so that it sorts the same original array with each sorting
algorithm, and writes out the number of iterations used by each
algorithm.

The purpose of this lab is purely to get familiar with Unix-like
systems, the C compiler, and the C syntax. There is no need to submit
any work for marking.