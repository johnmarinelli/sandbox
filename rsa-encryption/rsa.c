#include <stdlib.h>
#include <stdio.h>
#include "Array.h"

void primeFactorization(int n, int div, Array* array)
{
	if(n % div != 0){
		div += 1;
		return primeFactorization(n, div, array);
	}
	
	else if(div >= n){
		insertArray(array, div);
		printf("n: %d, div: %d\n", n, div);
	}
	
	else{
		n /= div;
		insertArray(array, div);
		printf("n: %d, div: %d\n", n, div);
		return primeFactorization(n, div, array);	
	}
}

/*
*  euler's totient function: computes # of ints less than n that are coprime
*  to n
*/
float totient(int n, Array* array)
{
	float totient = (float)n;

    for(int i = 0; i < array->mUsed; ++i){
		int primeFactor = array->mArray[i];
		float pf = (1.0 / primeFactor);
		totient *= (1.0 - pf);
	}

	return totient;
}

int main(int argc, char* args[])
{
	int p = 17;
	int q = 13;
	int n = p * q;

	printf("p: %d\n", p);
	printf("q: %d\n", q);
	printf("n: %d\n", n);

	Array array;
	initArray(&array, 10);

	primeFactorization(n, 2, &array);
	displayArray(&array);

	printf("totient: %g\n", totient(n, &array));

	return 0;
}
