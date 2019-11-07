//A sample client for intal.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intal.h"

int intal_test(void* intal, const char* str) {
	char *str2;

	//intal2str always creates a new array of chars and returns that.
	//it's the responsibility of the client to free the string returned by intal2str()
	//intal2str() returns the string "NaN" when the intal is a null pointer.
	str2 = intal2str(intal);
	if(strcmp(str, str2)) {
		printf("FAILED for expected intal %s\n", str);
		free(str2);
		return -1;
	}
	free(str2);
	return 0;
}

int main(int argc, char const *argv[]) {
	char str1[100] = "4999";
	char str2[100] = "2001";
	char str3[100] = "0";
	char *str4;
	void *intal1;
	void *intal2;
	void *intal3;
	void *max;
	void *sum;
	void *diff;
	void *product;
	void *quotient;
	void *quotient2;
	void *exp;

	//In our test-cases we'll always give valid nonnegative integers as input for intal_create()
	intal1 = intal_create(str1); //4999
	intal_test(intal1, "4999");
	intal2 = intal_create(str2); //2001
	intal_test(intal2, "2001");
	intal3= intal_create(str3); //0
	intal_test(intal3,"0");

	//In our test-cases we'll never give null pointer as an argument for an intal
	intal1 = intal_increment(intal1); //5000
	intal2 = intal_decrement(intal2); //2000
	intal3 = intal_decrement(intal3); //0
	intal_test(intal1, "5000");
	intal_test(intal2, "2000");
	intal_test(intal3, "0");

	//Max of two intals: 5000
	//intal max is not a new object and it need not destroyed when we are done with it
	//In our test-cases, as we are not going to give null pointers as input, don't worry as that case for now
	max = (intal_compare(intal1, intal2) > 0) ? intal1 : intal2;
	intal_test(max,"5000");
		
	//Sum
	sum = intal_add(intal1, intal2); //7000
	intal_test(sum,"7000");

	//Diff
	diff = intal_diff(intal1, intal2); //3000
	intal_test(diff,"3000");

	//Product
	product = intal_multiply(intal1, intal2); //10000000
	intal_test(product,"10000000");

	//Quotient
	quotient = intal_divide(intal1, intal2); //2
	intal_test(quotient,"2");

	//Exponentiation
	exp = intal_pow(intal1, quotient); //5000^2 = 25000000
	intal_test(exp, "25000000");

	//Divide by zero
	intal_destroy(intal3);
	intal3 = intal_create(str3); //0
	quotient2 = intal_divide(intal1, intal3); // divide-by-zero, so NaN
	intal_test(quotient2, "NaN");

	//Make sure you destroy all the intals created.
	intal_destroy(sum);
	intal_destroy(diff);
	intal_destroy(product);
	intal_destroy(quotient);
	intal_destroy(quotient2);
	intal_destroy(exp);
	intal_destroy(intal1);	
	intal_destroy(intal2);
	intal_destroy(intal3);
	printf("Sanity check done. If you see any \"FAILED\" messages above, make sure you fix them and then submit your code.\n");
	return 0;
}
