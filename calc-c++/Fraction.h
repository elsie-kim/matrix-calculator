#ifndef _FRACTION_
#define _FRACTION

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

// Fraction object allows values to be stored in fraction form rather than as floating-point numbers
// Used to ensure minimal rounding errors
class Fraction 
{
		int GCD(int a, int b);	
		void set_print();
		void set_signs();

	public:
		int num;
		int denom;
		std::string print;

		void simplify();
		void multiply(Fraction that);
		void divide(Fraction that);
		void add(Fraction that);
		void subtract(Fraction that);
		
		Fraction(int num);	
		Fraction(int num, int denom);
		
};

#endif
