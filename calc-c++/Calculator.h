#ifndef _CALCULATOR_
#define _CALCULATOR_

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

// Calculator object contains vector operation methods (such as dot product)

class Calculator 
{
    public:
        std::vector<std::string> operations = {"dot_product"};
	std::string int_or_float(float x);  
	std::string concatenate(std::string x);
	std::string round_val(std::string x);
	float dot_product(std::vector<float>& v, std::vector<float>& v2);
	std::string cross_product(std::vector<float>&v, std::vector<float>& v2);
	
	
	void print_vector(std::vector<float> v);
	void swap(std::vector<float>& a, std::vector<float>& b);
	void divide_row(std::vector<float>& a, float val);
	void eliminate_row(std::vector<float>& a, std::vector<float>& pivot, float val);

	std::string multiplication(std::vector<std::vector<float>>& m1, std::vector<std::vector<float>>& m2);	
	std::string reduced_row_echelon(std::vector<std::vector<float>>& m);
		
	
};

#endif
