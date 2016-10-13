#include <stdio.h>
#include <string.h>
#include <ctype.h>


/*
 * Define an enumerable of all possible states
 * (symbols of our grammar)
 *
 * */
typedef enum {
	START,
	LOCAL,
	LOCAL_DELIM,
	AT,
	DOMAIN,
	DOMAIN_DELIM,
	FAIL,
	SUCCESS
} STATE;



/*
 * Compare a string against all of a list of terminators
 *
 * -------------------------------------------------------------
 * string:          string to compare
 * terminators:     list of terminator strings
 * num_terminators: number of terminators
 *
 * returns:       - 1 iff string matches one or more terminators
 * 	          - 0 otherwise
 *
 * */
int isterminator(char *string, char **terminators, int num_terminators)
{
	int result = 0;
	int i;
	for (i = 0; i < num_terminators; i++) {
		// `|=` => result == 1 if any terminator matches
		result |= (strcmp(string, terminators[i]) == 0);
	}
	return result;
}

/*
 * Lexically analyse a string, validating it against our given CFG
 *
 * - A simple state machine is implemented, whose transitions represent
 *   the consumption of a character by the parser. `symbol` refers to
 *   the next state of the machine. A non-FAIL transition
 *   represents a valid symbol following the current one
 * - The function only returns 1 if the SUCCESS state is reached,
 *   which is only possible if all rules of the grammar are met
 * - Moreover, we jump to FAIL as soon as an invalid token in the
 *   context of particular state is detected; ensuring we only evaluate
 *   a whole address if it is valid
 *
 * --------------------------------------------------------
 * address:         string to validate
 * terminators:     a list of acceptable terminators (TLDs)
 * num_terminators: number of terminators
 *
 * returns:       - 1 iff string is a valid email address
 *                - 0 otherwise
 *
 * */

int isValidEmailAddress (char *address, char **terminators, int num_terminators)
{
	char character;
	char *error_message;
	STATE symbol = START;

	while(1) {
		character = *address;
		switch (symbol) {
			case START:
				if (isalpha(character)) {
					symbol = LOCAL;
				} else {
					error_message = "local part, leading alphabetic identifier";
					symbol = FAIL;
				}
				break;
			case LOCAL:
				//keep consuming characters until a delimiter is reached
				if (isalnum(character)) {
					symbol = LOCAL;
				} else if (character == '@') {
					symbol = AT;
				} else if (character == '.') {
					symbol = LOCAL_DELIM;
				} else {
					error_message = "local part, alphanumeric identifier, '@' or '.'";
					symbol = FAIL;
				}
				break;
			case LOCAL_DELIM:
				if (isalpha(character)) {
					symbol = LOCAL;
				} else {
					error_message = "local part, alphabetic identifier after '.'";
					symbol = FAIL;
				}
				break;
			case AT:
				if (isalpha(character)) {
					symbol = DOMAIN;
				} else {
					error_message = "domain part, alphabetic identifier after '@'";
					symbol = FAIL;
				}
				break;
			case DOMAIN:
				if (isalnum(character)) {
					symbol = DOMAIN;
				} else if (character == '.') {
					symbol = DOMAIN_DELIM;
				} else {
					error_message = "domain part, valid terminator";
					symbol = FAIL;
				}
				break;
			case DOMAIN_DELIM:
				        /* All terminators are alphabetic, so we check if the rest of
					 * the string is a terminator first */
				if (isterminator(address, terminators, num_terminators)) {
					symbol = SUCCESS;
				} else if (isalpha(character)) {
					symbol = DOMAIN;
				} else {
					error_message = "domain part, alphanumeric identifier or valid terminator";
					symbol = FAIL;
				}
				break;
			case FAIL:
				printf("Error in %s expected\n", error_message);
				return 0;
				break;
			case SUCCESS:
				return 1;
				break;
		}
		address++;
	}
}


/*
 * format and print the validity of a given address against given terminators
 *
 * address:         address to validate
 * terminators:     valid terminators
 * num_terminators: number of terminators
 *
 * returns: 1 if string is a valid email address, 0 otherwise
 * */
int  print_validity(char *address, char **terminators, int num_terminators)
{
	printf("%s\n", address);
	int isvalid = isValidEmailAddress(address, terminators, num_terminators);
	printf("=> %s\n\n", (isvalid? "Valid" : "Invalid"));
	return isvalid;
}


/*
 * print program usage and demonstration
 *
 * progname:        argv[0]
 * terminators:     valid terminators
 * num_terminators: number of terminators
 * */
void usage(char *progname, char **terminators, int num_terminators)
{
	printf("validate email addresses against given grammar \n"
	       "usage: %s <address1> [[address2] ...]\n"
	       "\nsample evaluation:\n\n",
	       progname);

	char *addresses[] = {
		"shawa1@tcd.ie",
		"santa.claus@north.pole.com",
		"joe.soap@inf.ed.ac.uk",
		"fail@1mail.ie",
		"1example.name@email.net",
		"malformed.4ddr3ss@numbers.com",
		"alice.@mail.com",
		"bob@.mail.com",
		"terrible@net",
	};
	int num_addresses = 9;

	int i;
	for (i = 0; i < num_addresses; i++) {
		print_validity(addresses[i], terminators, num_terminators);
	}

}


/*
 * Unless given addresses from the command line, run usage()
 *
 * */
int main(const int argc, char **argv)
{
	char *terminators[] = {
		"com",
		"net",
		"edu",
		"ie",
		"uk"
	};

	int num_terminators = 5;
	if (argc > 1){
		int i;
		for (i = 1; i < argc; i++){
			//by Unix convention, we return 1 iff something has gone wrong
			//thus a valid email address should have a return code of 0
			return !(print_validity(argv[i], terminators, num_terminators));
		}
	} else	{
		usage(argv[0], terminators, num_terminators);
	}
	return 0;
}
