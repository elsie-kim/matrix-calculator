#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "Fraction.h"

// Calculator object contains vector operation methods (such as dot product)

class Calculator 
{
	void print_vector(std::vector<Fraction> v);
	void swap(std::vector<Fraction>& a, std::vector<Fraction>& b);
	void divide_row(std::vector<Fraction>& a, Fraction val);
	void eliminate_row(std::vector<Fraction>& a, std::vector<Fraction>& pivot, Fraction val);
	int find_next_column(std::vector<std::vector<Fraction>>& m, int current);
	void move_to_back(std::vector<std::vector<Fraction>>& m, int row);
	void move_row(std::vector<std::vector<Fraction>>& m, int pivot);

	public:
		std::string dot_product(std::vector<Fraction>& v, std::vector<Fraction>& v2);
		std::string cross_product(std::vector<Fraction>&v, std::vector<Fraction>& v2);
		
		std::string multiplication(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2);	
		std::string augmented_reduced_row_echelon(std::vector<std::vector<Fraction>>& m);
		std::vector<std::vector<Fraction>> augmented_reduced_row_echelon_solve(std::vector<std::vector<Fraction>>& m);
		std::string addition(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2);
		std::string subtraction(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2);

};

#endif
