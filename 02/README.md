CS2014 Lab 2 : Identifying Email Addresses

Thursday 9th October

Sometimes you want to identify whether or not a given string is
a valid email address. The actual rules for identifying email
addresses are quite complicated, but for the purposes of this
lab we will use a simpler definition.

An email address consist of one of more identifiers, separated by full
stops, followed by the @ symbol, followed by one or more identifiers
separated by full stops, followed by a full stop, followed by a
terminator string, followed by the end of the string.

If we were to write a grammar for an email address, it would look
something like:
EMAIL_ADDRESS   --> IDENTFIER_LIST @ IDENTIFIER_LIST . TERMINATOR '\0'
IDENTIFIER_LIST --> IDENTIFIER . IDENTIFIER_LIST
IDENTIFIER_LIST --> IDENTIFIER
TERMINATOR      --> IDENTIFIER
IDENTIFIER      --> ALPHA REMAINDER
REMAINDER       --> ALPHANUM REMAINDER
REMAINDER       --> <empty string>
ALPHANUM        --> ALPHA
ALPHANUM        --> NUM
ALPHA           --> [a-zA-Z]
NUM             --> [0-9]

Your job is to write a function that detects whether or not a given
string is a valid email address, according to these rules. Your
function should have the following prototype:

int isValidEmailAddress(char * address, char ** terminators,
                        int num_terminators)

A terminator is a final string such as "com" or "net" that ends an
email address. The set of all valid terminators is stored in the
parameter array "terminators". The length of this array of terminators
is stored in the parameter "num_terminators".

Note that the "terminators" parameter is a pointer to a pointer to a
character. The "terminators" parameter points to an array of pointers
to characters. Each element of this array points to an array of
characters, that is a string.

To identify alphabetic and numeric characters you can use the standard
C functions isalpha(char) and isdigit(char) respectively.

You should test your function using code looking something like:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_validity(char * address, char** terminators,
                    int length)
{
  printf("The string %s is ", address);
  if (!isValidEmailAddress(address, terminators, length) {
    printf("not ");
  }
  printf("a valid email address\n");
}


int main()
{
  const int length = 5;
  char * terminators[length];
  char * address1, * address2;

  terminators[0] = "com";
  terminators[1] = "net";
  terminators[2] = "edu";
  terminators[3] = "ie";
  terminators[4] = "tv";

  address1 = "santa.claus@north.pole.com";
  address2 = "I.am@fish";

  print_validity(address1, terminators, length);
  print_validity(address2, terminators, length);

  return 0;
}

This lab will be marked, and will count towards your end of year mark.
You should submit your project work not later than 23.58 on Wednesday
15th October 2014 using the Blackboard system. To be marked, you must
demonstrate and answer questions on your project at your regular lab
session on Thursday 16th October. You must demonstrate the same code
that you submit. All work should be your own.
