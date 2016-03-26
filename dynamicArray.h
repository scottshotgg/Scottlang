// DynamicArray.h
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdlib.h>

// for now this only does ints
class DynamicArray {
	int len = 0;
	int *array;
	int index = 0;
	int expansionAmount = 10;
	// int type = ...;		might implement a ttemplate for types or something
	public:
		//dynamicArray(int lengthOfArray, int initializationValue)		// implement this later
		//DynamicArray();
		
	/*DynamicArray(int lengthOfArray) {
		array = (int *) malloc(lengthOfArray);
		len = lengthOfArray;
	}*/
	DynamicArray() {
		array = (int *) malloc(1);
		len = 1;
	}

	~DynamicArray() {
	}

	int  length();
	void push(int);
	void print();
	void expand();		// make this an int where we can epand standard amount or w/e is passed
};

#endif