#include "Calculator.h"

// Calculates the dot product of two vectors v1 and v2

std::string Calculator::int_or_float(float x) {
	if (x == int(x)) {
		int y = int(x);
		return std::to_string(y);
	} else {
		return std::to_string(x);
	}
}

float Calculator::dot_product(std::vector<float>& v1, std::vector<float>& v2)
{
	float sum = 0;
    
	for (int i=0; i < v1.size(); i++)
	{
		sum += v1[i] * v2[i];
	}
    
	return sum;
}

std::string Calculator::cross_product(std::vector<float>&v1, std::vector<float>& v2) 
{
	std::string ans;

	float a = v1[1]*v2[2] - v1[2]*v2[1];
	float b = v1[2]*v2[0] - v1[0]*v2[2];
	float c = v1[0]*v2[1] - v1[1]*v2[0];

	ans = "(" + int_or_float(a) + ", " + int_or_float(b) + ", " + int_or_float(c) + ")";
	
	return ans;
}

