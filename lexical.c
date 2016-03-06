#include <stdio.h>
#include <ctype.h>


int nextChar;
int nextCharType;
char lexeme[100];
int lexLength;
int token;
int nextToken;
FILE *file_reader, *fopen();



#define ALPHA		0
#define DIGIT		1
#define OTHER		99

#define INT			10
#define VAR			11
#define FLOAT		12
#define ASSIGN_OP	20
#define ADD_OP		21
#define SUB_OP		22
#define MULT_OP		23
#define DIV_OP		24
#define LEFT_PAREN	25
#define	RIGHT_PAREN	26
#define END_OP		27
#define DECIMAL		28




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
			nextToken = END_OP;
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
			while (nextCharType == DIGITgit  || DECIMAL) {
				addChar();
				getChar();
			}
			nextToken = DIGIT;
			break;

		/*case DECIMAL:
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
			printf("Syntax error");		// add some more shit here to tell the plebs where they went wrong and stuff
	}

	printf("Next token is: %d	Next lexeme is: %s\n", nextToken, lexeme);

	return nextToken;
}

int main(int argc, char *argv[]) {
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
				lex();
			} while(nextChar != EOF);
		}
	}
	else {
		printf("Not enough arguments; ./lexical [program_name] [debug]\n");
	}
}