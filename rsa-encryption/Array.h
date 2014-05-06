#include <stdlib.h>

typedef struct{
	int* mArray;
	size_t mSize;
	size_t mUsed;
} Array;

void initArray(Array* a, size_t initialSize)
{
	a->mArray = (int*)malloc(sizeof(int) * initialSize);
	a->mUsed = 0;
	a->mSize = initialSize;
}

void insertArray(Array* a, int n)
{
	if(a->mUsed == a->mSize){
		a->mSize *= 2;
		a->mArray = (int*)realloc(a->mArray, sizeof(int) * a->mSize);
	}
	
	a->mArray[a->mUsed++] = n;
}

void clearArray(Array* a)
{
	free(a->mArray);
	a->mArray = NULL;
	a->mUsed = a->mSize = 0;
}

void displayArray(Array* a)
{
	for(int i = 0; i < a->mUsed; ++i){
		printf("%d\n", a->mArray[i]);
	}
}
