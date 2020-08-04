#include "Calculator.h"

// Calculates the dot product of two vectors v1 and v2

std::string Calculator::int_or_float(float x) {
	if (x == int(x)) {
		int y = int(x);
		return std::to_string(y);

	} else {
		return round_val(std::to_string(x));
	}
}

std::string Calculator::concatenate(std::string x) {
	std::string::size_type index = x.find('.');

	for (int i=x.length()-1; i>index; i--) {
		if (x[i] == '0' && x[i-1] != '0') {
			return x.substr(0, i);
		}
	}

	return x;
}

std::string Calculator::round_val(std::string x) {
	float y = std::stof(x);
	y *= 10000;
	y = round(y);

	if (std::to_string(y).find('.') != std::string::npos) {
		return concatenate(std::to_string(y/10000));
	} 

	return std::to_string(y/10000);
	
}

float Calculator::dot_product(std::vector<float>& v1, std::vector<float>& v2)
{
	float sum = 0;
    
	for (int i=0; i < v1.size(); i++)
	{
		sum += v1[i] * v2[i];
	}
   
	std::string s_str = std::to_string(sum);

	if (sum != int(sum) && s_str.rfind('0') == (s_str.size()-1)) {		
		std::string sum_string = std::to_string(sum);
		sum_string = round_val(sum_string);
		sum = std::stof(sum_string);
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

