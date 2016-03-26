#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dynamicArray.h>

FILE *file_reader, *fopen();
FILE *file_writer, *fopen();

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


int main() {

	/*
	int arrayLength = sizeof(token_name_array) / sizeof(char);

	for(int i = 0; i < arrayLength; i++) {
		printf("%c", token_name_array[i]);
	}
	*/

	DynamicArray mine = new DynamicArray();


	file_reader = fopen("tokens", "r");
	//file_writer = fopen("tokens", "w");
	char nextChar = getc(file_reader);

	do {

		if(nextChar != '\n') {
			token_name_array[token_name_count++] = nextChar;
			//printf("%c\n", nextChar);
		}
		else {
			//extractInt();
			printf("%d", atoi(token_name_array));
			token_name_count = 0;

			//int arrayLength = sizeof(token_name_array) / sizeof(char);

			for(int i = 0; i < 20; i++) {
				//printf("%c", token_name_array[i]);
				token_name_array[i] = '\0';
			}

			printf("\n\n");
		}

	} while((nextChar = getc(file_reader)) != EOF);

	printf("\n");

	return 0;
}