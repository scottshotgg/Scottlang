#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "dynamicArray.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <string>
#include <vector>
#include <typeinfo>

//FILE *file_reader, *fopen();
//FILE *file_writer, *fopen();

// this doesn't need to be dynamic, since the tokens aren't of 
// much length, and especially not longer that 20 chars
char token_name_array[20];
int token_name_count = 0;


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


// typedef this shit so we don't have to write a story everytime
 typedef std::vector<int> 	int_v;
 typedef std::vector<std::string> str_v;

// should use a template later to increase the generality of the function

template <typename T>
void print(T vector) {

	printf("[ ");

	for (int_v::const_iterator i = vector.begin(); i != vector.end(); ++i)
    	printf("%d ", *i);

    printf("]");
}

void strPrint(str_v vector) {

	printf("[ ");

	for (int i = 0; i < vector.size(); i++) {
    	printf("%s ", vector[i].c_str());
	}

    printf("]");
}

int switchTable(int token) {
	//switch(tokens[1])


}


int parse(int_v tokens, str_v lexemes) {


	printf("\n\n\n----------------------------------------------------------------");

	printf("\nStarting parsing\n\n");
	
	print(tokens);

	printf("\n\n");

	strPrint(lexemes);

	printf("\n\n");

	for(int i = 0; i < tokens.size(); i++) {
		switchTable(tokens[i]);
	}


	printf("----------------------------------------------------------------");

	return 0;
}

/*
int main() {

	/*
	int arrayLength = sizeof(token_name_array) / sizeof(char);

	for(int i = 0; i < arrayLength; i++) {
		printf("%c", token_name_array[i]);
	}
	int_v tokens;
	str_v lexems;
	//DynamicArray mine = DynamicArray();

	srand (time(NULL));


	//int me = mine.length();
	/*for(int i = 0; i < 10000; i++) {
		//mine.push(rand() % 1000 + 1);
		//mine.push(i);

	}
	//mine.print();

	printf("\n\n");

	//mine.print();

	//printf("\n\n");


	/*file_reader = fopen("tokens", "r");
	//file_writer = fopen("tokens", "w");
	char nextChar = getc(file_reader);

	do {

		if(nextChar != '\n') {
			token_name_array[token_name_count++] = nextChar;
			//printf("%c\n", nextChar);
		}
		else {
			//extractInt();
			//printf("%d", atoi(token_name_array));
			tokens.push_back(atoi(token_name_array));
			//mine.push(atoi(token_name_array));
			token_name_count = 0;

			//int arrayLength = sizeof(token_name_array) / sizeof(char);

			for(int i = 0; i < 20; i++) {
				//printf("%c", token_name_array[i]);
				token_name_array[i] = '\0';
			}

			//printf("\n\n");
		}

	} while((nextChar = getc(file_reader)) != EOF);

	//mine.print();

	print(tokens);

	printf("\n\n\n");

	return 0;
}*/