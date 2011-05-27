//
//  frack.c
//  frack
//
//  The algorithm used by this program was outlined in
//  a paper by John Kennedy at the Santa Monica College.
//  http://homepage.smc.edu/kennedy_john/DEC2FRAC.PDF
//
//  Created by Carter Allen on 5/21/11.
//  Modified and perfected by Zach Fisher.
//  Copyright 2011 Opt-6 Products, LLC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 1e-6

int gcd(int m, int n) {
	int r;
	
	if (m < n) {
		return gcd(n, m);
	}
	
	r = m % n;
	
	if (r == 0) return n;
	else return gcd(n, r);
	
}

typedef struct {
	int numerator;
	unsigned int denominator; // Keep signs logical, denominator >= 0.
} Fraction;

Fraction frackify(double input) {
	
	float signOfInput = (input >= 0.0)? 1.0 : -1.0;
	input = input * signOfInput; // Make input positive.

	double z[2] = { 0, input }; // { zLast, zNow }
	int d[2] = { 0, 1 }; // { dLast, dNow }
	int n = 0;

	while ((fabs(z[1] - roundf(z[1])) > PRECISION && fabs(z[0] - z[1]) > PRECISION)) {
		double fracPart = (z[1] - floorf(z[1]));
		z[0] = z[1];
		z[1] = 1.0/fracPart;
		int intPart = floorf(z[1]);
		int oldD = d[1];
		d[1] = (d[1] * intPart) + d[0];
		d[0] = oldD;
		n = roundf(input * d[1]);
	} 
	
	int theGCD = gcd(n, d[1]);
	n = n/theGCD;
	d[1] = d[1]/theGCD;
	
	Fraction result;
	result.numerator = signOfInput * n;
	result.denominator = d[1];
	
	return result;
	
}

int main(int argc, const char * argv[]) {
	
	double input = 0.0;
	
	if (argc == 1) {
		scanf("%lf", &input);
	}
	else if (argc == 2) {
		input = atof(argv[1]);
	}
	else {
		printf("Usage: frack [decimal_number]");
		return EXIT_FAILURE;
	}
	
	Fraction result = frackify(input);
	
	if (((double)result.numerator/(double)result.denominator) != input) {
		fprintf(stderr, "Warning: fraction is not exactly equal to the input decimal.\n");
	}
	
	printf("%d/%d\n", result.numerator, result.denominator);
	
	return EXIT_SUCCESS;

}
