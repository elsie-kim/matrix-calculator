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

};

#endif
