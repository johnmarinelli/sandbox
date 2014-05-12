#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Array.h"

#define bool int;
#define true 1;
#define false 0;

/*
*  Euclid's algorithm
*/
int greatestCommonDivisor(int a, int b)
{
	int remainder = a % b;
	int quotient = a / b;

	if(remainder == 0){
		return b;
	}
	else{
		return greatestCommonDivisor(b, remainder);
	}
}

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
*  Extended Euclidean algorithm
*/
int getMultiplicativeInv(int a, int n)
{
	int t = 0;
	int newt = 1;
	int r = n;
	int newr = a;

	while(newr != 0){
		int quotient = r / newr;
		t = newt;
		newt = t - quotient * newt;

		r = newr;
		newr = r - quotient * newr;
	}

	if(r > 1){
		return -1;
	}
	if(t < 0){
		t = t + n;
	}

	return t;
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

int getRandomCoprime(int min, int max, Array* primeFactors)
{
	if(min > max){
		return -1;
	}

	//trivial coprime
	//int e = max - 1;
	int e = rand() % (max - min) + min;
	int gcd = greatestCommonDivisor(e, max);
	
	if(gcd != 1){
		return getRandomCoprime(min, max, primeFactors);
	}
	else{
		printf("random coprime: %d\n", e);
		return e;
	}
}

int main(int argc, char* args[])
{
	srand(time(NULL));

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

	int tnt = totient(n, &array);

	printf("totient: %d\n", tnt);
	
	int e = getRandomCoprime(1, tnt, &array);

	int d = getMultiplicativeInv(e, tnt);
	printf("multinv: %d\n", d);

	return 0;
}
