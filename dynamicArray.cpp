// for now this only does ints
#include "dynamicArray.h"
#include <stdio.h>
#include <iostream>


void DynamicArray::push(int atom) {
	//printf("%d\t%d\n", index, len);
	if(index < len) {
		array[index++] = atom;
	}
	else {
		//printf("Full already!\nExpanding!");
		expand();

		//printf("%d\t%d\t%d", index, array[index], array[index + 1]);
		push(atom); 
		//printf("%d", array[index - 1]);
	}
}

int DynamicArray::length() {
	//return sizeof(array) / sizeof(int);
	return len;
}

void DynamicArray::print() {		// make a seperating symbol
	//printf("%d\n", len);

	printf("[");

	for(int i = 0; i < len; i++) {
		printf(" %d ", array[i]);
	}

	printf("]");
}

void DynamicArray::expand() {
	//int *arrayTempCopy = new int[len + expansionAmount];
	int *arrayTempCopy = (int *)realloc(array, (len + expansionAmount) * sizeof(int));
	
	//print();
	char me;

	//std::cin >> me;
	//std::memcpy(&arrayTempCopy, &array, len);
	//printf("starting\n");
	for(int i = 0; i < len; i++) {
		//printf("this is me %d \n", arrayTempCopy[i]);
		//arrayTempCopy[i] = array[i];
	}

	for(int i = len; i < len + expansionAmount; i++) {
		arrayTempCopy[i] = 0;
		//printf("this is me %d \n", arrayTempCopy[i]);
	}

	//print();


	len = len + expansionAmount;

	// dont use this shit, use realloc
	//free(array);
	//delete [] array;
	//array = (int *)realloc(arrayTempCopy, len * sizeof(int));
	array = (int *)realloc(arrayTempCopy, len * sizeof(int));
	//print();
	/*for(int i = 0; i < len; i++) {
		array[i] = arrayTempCopy[i];
	}*/
	//free(arrayTempCopy);

	//free(arrayTempCopy);
	//delete[] arrayTempCopy;
	//free(arrayTempCopy);

	//printf("Size: %lu", sizeof(array) / sizeof(int));

	//std::memcpy(&array, &arrayTempCopy, len + expansionAmount);
	printf("%d\n", len);

}