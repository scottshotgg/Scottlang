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
#include <sstream>

#include <iostream>

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


int 	lastToken 	 = -1;
int 	iterator 	 =  0;
int 	state 		 =  0;
int 	intLastSum 	 =  0;
float 	lastSum 	 =  0;
int_v	globalTokens;
str_v 	globalLexems;
float 	nextTokenVal = 0;

// should use a template later to increase the generality of the function

template <typename T>
void print(T vector) {

	printf("[ ");

	for (int_v::const_iterator i = vector.begin(); i != vector.end(); ++i)
    	printf("%d ", *i);

    printf("]");
}

// function converts a cstring to float value, if you need an int just cast it afterwards
float cstof(std::string strn) {
	std::stringstream convert;
	convert << strn;
	float number; 
	convert >> number;
	return number;
}

void strPrint(str_v vector) {

	printf("[ ");

	for (int i = 0; i < vector.size(); i++) {
    	printf("%s ", vector[i].c_str());
	}

    printf("]");
}

int factor() {
	
	return 0;			// just put this here for now
}

int term() {

	return 0;			// just put this here for now
}

int expr() {

	return term();
}

int var() {
	// set this equal to something 
	return expr();
}

// convert this to a state machine
int switchTable(int token) {
	switch(token) {
		case 10: {
			// here we would need to check if the var exists or not and then retrieve it, but not yet
			// assume that the var is 0
			break;
		}
		case 30: {
			if(lastToken != 10) {
				printf("invalid assignment operation");
			}
			break;
		}
		case 31: {
			if(lastToken == 10 || lastToken == 11 || lastToken == 12 || lastToken == 13 || lastToken == 14) {	
				// need to check the next token
				//printf("%d", globalTokens[iterator + 1]);
				//float lastTokenVal = 0;
				

				// make this more explicit
				/*if(lastToken != 10) {
					//lastTokenVal = atoi(globalLexems[iterator - 1]);
					lastTokenVal = cstof(globalLexems[iterator - 1]);
				}*/

				// make this more explicit
				if(nextTokenVal != 10) {
					//lastTokenVal = atoi(globalLexems[iterator + 1]);
					nextTokenVal = cstof(globalLexems[iterator + 1]);
				} 

				//printf("%f    %f\n", lastTokenVal, nextTokenVal);



				// just do everything in float and then convert at the end to the expected value, this might work
				lastSum += nextTokenVal;
				//printf("No type inherited or implicitly specified, non-conversion value: %f\n", lastSum);

				//std::string this_string(globalLexems[6], (sizeof(globalLexems[6])/sizeof(char)));
				//std::string this_string(globalLexems[6]);
				//printf("%s ", globalLexems[6].c_str());

				//maybe we can do something with this
				//printf("%d", atoi("45.677"));

				//std::stringstream convert;
				//convert << globalLexems[6];
				
				//float number = 0.0;

				//convert >> number;

				

				//std::string testString = "";
				//testString += "90";
				//printf("%s", testString);
				//printf("%d", atoi(this_string));

				iterator++;

			}
			break;
		}

		case 11: {
			printf("i got here");
			break;
		}

		case 32: {
			if(nextTokenVal != 10) {
				nextTokenVal = cstof(globalLexems[iterator + 1]);
			}
			lastSum -= nextTokenVal;
			//printf("No type inherited or implicitly specified, non-conversion value: %f\n", lastSum);
			break;
		}
		// could just make this the default
		case 99: {
			printf("END STATEMENT \nsum = %f\n\n", lastSum);
			break;
		}
	}

	lastToken = token;

	return 0;			// just put this here for now
}

/*int stateMachine(int token) {
	//case
}*/

int parse(int_v tokens, str_v lexemes) {


	printf("\n\n\n----------------------------------------------------------------");

	printf("\nStarting parsing\n\n");

	globalTokens = tokens;
	globalLexems = lexemes;
	
	print(tokens);

	printf("\n\n");

	strPrint(lexemes);

	printf("\n\n");

	for(iterator = 0; iterator < tokens.size(); iterator++) {
		//stateMachine(tokens[iterator]);
		switchTable(tokens[iterator]);
	}


	printf("----------------------------------------------------------------\n\n");

	return 0;
}

/*
int main() {

	int arrayLength = sizeof(token_name_array) / sizeof(char);

	for(int i = 0; i < arrayLength; i++) {
		printf("%c", token_name_array[i]);
	}
	int_v tokens;
	str_v lexems;
	//DynamicArray mine = DynamicArray();

	srand (time(NULL));


	//int me = mine.length();
	for(int i = 0; i < 10000; i++) {
		//mine.push(rand() % 1000 + 1);
		//mine.push(i);

	}
	//mine.print();

	printf("\n\n");

	//mine.print();

	//printf("\n\n");


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