#include <stdio.h>
#include <ctype.h>


int nextChar;
int nextCharType;
char lexeme[100];
int lexLength;
int token;
int nextToken;
int hasDecimal = 0;
FILE *file_reader, *fopen();


/*	
	Make a switch or use an associative array to pack this into a coherent 
	data structure that will allow us to unpack the names from it when we 
	print out and start to use the debug flag
*/

/* Char types */
#define ALPHA				0
#define DIGIT				1
#define DECIMAL				2
#define OTHER				99


/* Types */
#define INT					10
#define VAR					11
#define FLOAT				12
#define CHAR				13
#define STRING				14


/* Operators */
#define ASSIGN_OP			20
#define ADD_OP				21
#define SUB_OP				22
#define MULT_OP				23
#define DIV_OP				24
#define ADD_ASSIGN_OP		28
#define SUB_ASSIGN_OP		29
#define MULT_ASSIGN_OP		30
#define DIV_ASSIGN_OP		31
#define DOT_ADD_OP			32
#define DOT_MULT_OP			33
#define DOT_SUB_OP			34
#define DOT_DIV_OP			35


/* Grouping symbols */
#define LEFT_PAREN			25
#define	RIGHT_PAREN			26


/* End statement */
#define END_STATEMENT		27 



int dummyFunc() {
	return ('=' == 1);		// experimenting with this, will throw a warning for now
}


void getChar() {
	if((nextChar = getc(file_reader)) != EOF) {
		if(isalpha(nextChar)) {
			nextCharType = ALPHA;
		}
		else if(isdigit(nextChar)) {
			nextCharType = DIGIT;
		}
		else if(nextChar == '.') {
			nextCharType = DECIMAL;
		}
		else {
			nextCharType = OTHER;
		}
	}
	else {
		nextCharType = EOF;
	}
}

void addChar() {
	if (lexLength <= 98) {
		lexeme[lexLength++] = nextChar;
		lexeme[lexLength] = 0;
	}
	else {
		printf("Error: Maximum of 1000 chars per lexeme!\n");
	}
}

int lookupTable(char unkownChar) {
	switch(unkownChar) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;

		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;

		case '+':
			addChar();
			nextToken = ADD_OP;
			break;

		case '-':
			addChar();
			nextToken = SUB_OP;
			break;

		case '*':
			addChar();
			nextToken = MULT_OP;
			break;

		case '/':
			addChar();
			nextToken = DIV_OP;
			break;

		case ';':
			addChar();
			nextToken = END_STATEMENT;
			break;

		case '=':
			addChar();
			nextToken = ASSIGN_OP;
			break;

		default:
			addChar();
			nextToken = EOF;
			break;
	}

	return nextToken;
}

int lex() {
	lexLength = 0;
	
	while(isspace(nextChar)) {
		getChar();
	}

	switch(nextCharType) {
		case ALPHA:
			addChar();
			getChar();
			while(nextCharType == ALPHA || nextCharType == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = VAR;
			break;

		case DIGIT:
			addChar();
			getChar();
			while (nextCharType == DIGIT || nextCharType == DECIMAL) {
				if(nextCharType == DECIMAL) {
					if(hasDecimal == 1) {
						return -2;
					}
					nextToken = FLOAT;
					hasDecimal = 1;
				}
				else {
					if(hasDecimal == 1)
						nextToken = FLOAT;
					else
						nextToken = INT;
				}
				addChar();
				getChar();
			}
			hasDecimal = 0;
			break;

		/*case DECIMAL:		// Don't think we need this, but I'll leave it anyways for now
			addChar();
			getChar();
			while(nextCharType == DIGIT) {
				addChar();
				getChar();
			}

			nextToken = FLOAT;
			break;*/

		case OTHER:
			lookupTable(nextChar);
			getChar();
			break;

		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = '\0';
			break;

		default:
			printf("Syntax error");		// add some more shit here to tell the plebs w
										// here they went wrong and stuff
	}

	printf("Next token is: %d	Next lexeme is: %s\n", nextToken, lexeme);

	return nextToken;
}

int main(int argc, char *argv[]) {

	//int me = dummyFunc;

	//printf("%d\n\n\n\n", me);


	if(argc > 2) {
		if((file_reader = fopen(argv[1], "r")) == NULL) {
			printf("Program \"%s\" does not exist\n", argv[1]);
		}
		else {
			getChar();
			//while(nextChar != EOF) {
			//	lex();
			//}
			do {
				int error = lex();
				if(error == -2) {
					printf("Syntax error: More than one decimal in float constant\n");
					return -2;		// this should change, figure out a way to continue parsing 
									// and then collect all errors at the end and display those 
									// at the end
				}
			} while(nextChar != EOF);

			printf("\nParsing completed: no errors\n");
		}
	}
	else {
		printf("Not enough arguments; ./lexical [program_name] [debug]\n");
	}
}