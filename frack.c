//
//  frack.c
//  frack
//
//  Created by Carter Allen on 5/21/11.
//  Copyright 2011 Opt-6 Products, LLC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DENOMINATOR 1000

typedef struct {
	int numerator;
	int denominator;
} Fraction;

Fraction frackify(double input) {

	double tolerance = 0.0001;
	
	int intPart = floorf(input);
	double fracPart = input - intPart;
	
	Fraction result;
	
	result.numerator = input * MAX_DENOMINATOR;
	result.denominator = 1;
	
	for (result.denominator = 1; result.denominator < MAX_DENOMINATOR; result.denominator++) {
		if (fabs(result.denominator * fracPart - round(result.denominator * fracPart)) <= tolerance) {
			result.numerator = round(input * result.denominator);
			break;
		}
	}
	
	return result;
	
}

int main(int argc, const char * argv[]) {
	
	double input;
	
	if (argc == 1) {
		scanf("%lf", &input);
	}
	else if (argc == 2) {
		input = atof(argv[1]);
	}
	else {
		printf("Error: too many arguments.");
		return EXIT_FAILURE;
	}
	
	Fraction result = frackify(input);
	
	printf("%d/%d\n", result.numerator, result.denominator);
	
	return EXIT_SUCCESS;

}
