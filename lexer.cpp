#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <vector>

char lexeme[100];

int nextChar			= 0;
int nextCharType		= 0;
int lexLength			= 0;
int token				= 0;
int nextToken			= 0;
int lookupError			= 0;

char **directString;
int directStringEnabled	= 0;
int directStringIndex 	= 0;
int directStringLength  = 0;

int hasDecimal 			= 0;
int hasLeftParen		= 0;
int hasLeftBracket		= 0;
int hasLeftQuote		= 0;
int hasLeftComma		= 0;

int statementEnded		= 0;

FILE *file_reader, *fopen();
FILE *file_writer, *fopen();

typedef std::vector<int>	int_v;
typedef std::vector<char*>	str_v;

extern int parse(int_v, str_v);
/*	
	Make a switch or use an associative array to pack this into a coherent 
	data structure that will allow us to unpack the names from it when we 
	print out and start to use the debug flag
*/

/* Char types */
#define ALPHA				0
#define DIGIT				1
#define DECIMAL				2
#define OTHER				3


/* Types */
#define VAR					10
#define INT					11
#define FLOAT				12
#define CHAR				13
#define STRING				14


/* Operators */
#define ASSIGN_OP			30
#define ADD_OP				31
#define SUB_OP				32
#define MULT_OP				33
#define DIV_OP				34
#define ADD_ASSIGN_OP		35
#define SUB_ASSIGN_OP		36
#define MULT_ASSIGN_OP		37
#define DIV_ASSIGN_OP		38
#define MAT_ADD_OP			39
#define MAT_MULT_OP			40
#define MAT_SUB_OP			41
#define MAT_DIV_OP			42


/* Grouping symbols */
#define LEFT_PAREN			60
#define	RIGHT_PAREN			61
#define LEFT_BRACKET		62
#define RIGHT_BRACKET		63
#define QUOTE				68
#define COMMA				69
#define COMMENT				70


/* End statement */
#define END_STATEMENT		99 


int_v tokens;
str_v lexemes;



int dummyFunc() {
	return ('=' == 1);		// experimenting with this, will throw a warning for now
}


void getChar() {
	/*if(directStringEnabled) {
		nextChar = 'd';
	}
	else {
		nextChar = getc(file_reader);
	}
	if(nextChar != EOF && nextChar != '\0') {*/		// taking out for fucky string shit
	if((nextChar = getc(file_reader)) != EOF) {
		//nextChar = getc(file_reader)
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
		//if(statementEnded)
			//error = -99;
		nextCharType = EOF;
	}
}

void addChar() {
	if (lexLength <= 98) {
		//printf("%c", nextChar);
		lexeme[lexLength++] = nextChar;
		lexeme[lexLength] = 0;
	}
	else {
		printf("Error: Maximum of 1000 chars per lexeme!\n");
		exit(-1);
	}
}

int lookupTable(char unkownChar) {
	switch(unkownChar) {
		case '(':			// Logic for function goes here
			addChar();		// Need to use a push down automata to check whether these things pair up
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

		case '/':				// Add Logic for the comments
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

		case '"': 				// needs to be some error checking here, also needs to know how to escape things like another quote
		{		
			addChar(); 			//still trying to decide if I want to include the quotes in the string value, 
								// this should be better abstracted later to include things like the length and stuff
			int strLen = 0;
			getChar();
			while(nextChar != '"' && nextChar != EOF) {
				if(nextChar == '\\') {
					strLen++;				
					getChar();
					addChar();
					getChar();
				}
				else {	
					strLen++;
					addChar();
					getChar();
				}
			}

			addChar();			// this adds the quote
		}	
			nextToken = STRING;
			break;

		case '\'':				// needs error checking and escape sequences
			addChar();	
			nextToken = COMMA; 		// do something with this later
			// maybe we should make the tokens be the errors if one does occur
			break;

		case '[':			// Logic for function goes here
			addChar();		// Need to use a push down automata to check whether these things pair up
			nextToken = LEFT_BRACKET;
			break;

		case ']':
			addChar();	
			nextToken = RIGHT_BRACKET;
			break;

		default:
			addChar();
			nextToken = EOF;		// just do this for now
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

		case DIGIT:				// Decimal might be able to go into other and the logic would be there
			addChar();
			getChar();
			nextToken = INT;
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
					else{
						nextToken = INT;
					}
						
				}
				addChar();
				getChar();
			}
			hasDecimal = 0;
			break;

		case DECIMAL:
			addChar();
			getChar();

			if(hasDecimal) {
				return -2;
			}
			else
				while(nextCharType == DIGIT) {			// need to add f for floats here
					addChar();
					getChar();
					if(nextChar == '.') {
						return -2;
					}
				}

			nextToken = FLOAT;
			break;

		case OTHER:
			lookupError = lookupTable(nextChar);
			//if(lookupError < 0) {
			//	return lookupError;
			//}
			getChar();
			break;

		case EOF:
			//if(statementEnded) {
				nextToken = EOF;
				lexeme[0] = 'E';
				lexeme[1] = 'O';
				lexeme[2] = 'F';
				lexeme[3] = '\0';
			/*}
			else {
				return -99;
			}*/

			

			break;

		default:
			printf("Syntax error");		// add some more shit here to tell the plebs w
										// here they went wrong and stuff
	}

	printf("Next token is: %d	Next lexeme is: %s\n", nextToken, lexeme);

	tokens.push_back(nextToken);

	printf("%s", lexeme);

	//std::string lexemeStr(lexeme, 3);
	//printf("this is the token %s", lexemeStr);
	lexemes.push_back(lexeme);

	if (lookupError == 0) {
		return nextToken;
	}
	else {
		return lookupError;
	}
}

int lexingFunction() {		// maybe this should return the error, idk
	getChar();
	//while(nextChar != EOF) {
	//	lex();
	//}
	do {
		int error = lex();			// make the erroring more consistent,
									// right now we can throw errors from anywhere
		// make this a switch later when we have more errors
		// we also should return the line atleast, possibly the char
		//printf("%d", error);

		switch(error) {
			case -2:
				printf("Syntax error: More than one decimal in float constant\n\n");
				return -2;
			case -3:
				printf("Syntax error: No matching left parenthesis for right parenthesis\n\n");
				return -3;
			case -4:
				printf("Syntax error: No matching right grouping operator for recognized left grouping operator before statement terminated\n\n");
				return -4;

			case -99:
				printf("Syntax error: Statement not terminated");
				return -99;
		}

		if(error == -2) {
			printf("Syntax error: More than one decimal in float constant\n\n");
			return -2;		// this should change, figure out a way to continue parsing 
							// and then collect all errors at the end and display those 
							// at the end
		}
		else if(error == -3) {
			printf("Syntax error: No matching left parenthesis for right parenthesis\n\n");
			return -3;
		}
	} while(nextChar != EOF);

	printf("\nLexing completed: no errors\n\n");

	return 0;
}

int main(int argc, char *argv[]) {

	printf("\n");
	// /printf("Statement being lexed: %s\n\n", (argv[1]));


	printf("\nStarting lexing\n\n");
	//printf("%d", isalpha('2'));
	//printf("%c\n", (argv[1][strlen(argv[1]) - 1]));

	//printf("this is the string thing %s", argv[2]);
	if(argc > 2) {
		// later when i feel like it we can make this shit work nice and have cool syntax for the command line arguments
		// we also need to check and make sure that the string length isnt 0 but im too lazy now
		//printf("%s", argv[2]);
		if(argv[2][0] == '1') {		// if its a single string in [ ] then just write it to a file like a pleb


			/*directStringEnabled = 1;										
			// take all this dynamic string shit out and just write it to a file and then reopen it; the easy way
			for(int i = 0; i < strlen(argv[1]); i++) {
				directStringLength++;
			}
			**directString = malloc(directStringLength * sizeof(char*));

			for(int i = 0; i < strlen(argv[1]); i++) {
				directString = ;
			}

			lexingFunction();

		*/
			file_writer = fopen("program", "w");

			fputs(argv[1], file_writer);

			fclose(file_writer);

			file_reader = fopen("program", "r");

			lexingFunction();
		}
		else {
			if((file_reader = fopen(argv[1], "r")) == NULL) {
				printf("Program \"%s\" does not exist\n\n", argv[1]);
			}
			else {
				lexingFunction();
			}
		}
	}
	else {
		printf("Not enough arguments; ./lexer [program_file_name] [interpret]\n");
		printf("i.e, ./lexer program 0\n\n");
	}


	printf("\nStarting parsing\n\n");

	for (int i = 0; i < lexemes.size(); i++) {
    	printf("%s ", lexemes[i]);
	}

	parse(tokens, lexemes);

}