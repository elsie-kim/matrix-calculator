#include "Calculator.h"

// rounds based on whether "x" is actually an int or a float value
std::string Calculator::int_or_float(float x) {
	if (x == int(x)) {
		int y = int(x);
		return std::to_string(y);

	} else {
		return round_val(std::to_string(x));
	}
}

// concatenates trailing zeros on "x"
std::string Calculator::concatenate(std::string x) {
	std::string::size_type index = x.find('.');

	for (int i=x.length()-1; i>index; i--) {
		if (x[i] == '0' && x[i-1] != '0') {
			return x.substr(0, i);
		}
	}

	return x;
}

// rounds "x" to nearest ten thousandth --- will adjust to allow user to specify degree of accuracy
std::string Calculator::round_val(std::string x) { // improve rounding accuracy
	float y = std::stof(x);
	y *= 10000;
	y = round(y);

	if (std::to_string(y).find('.') != std::string::npos) {
		return concatenate(std::to_string(y/10000));
	} 

	return std::to_string(y/10000);
	
}

// dot product of two vectors
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

// cross product of two vectors --- only supports 3D vectors, might add 7D later
std::string Calculator::cross_product(std::vector<float>&v1, std::vector<float>& v2) 
{
	std::string ans;

	float a = v1[1]*v2[2] - v1[2]*v2[1];
	float b = v1[2]*v2[0] - v1[0]*v2[2];
	float c = v1[0]*v2[1] - v1[1]*v2[0];

	ans = "(" + int_or_float(a) + ", " + int_or_float(b) + ", " + int_or_float(c) + ")";

	return ans;
}

void Calculator::print_vector(std::vector<float> v)
{
	for (float a : v) {
		std::cout << a << "\t";
	}
	std::cout << std::endl;

}

// multiplies two matrices
std::string Calculator::multiplication(std::vector<std::vector<float>>& m1, std::vector<std::vector<float>>& m2) 
{
	std::string ans = "\n";
	
	// use the dot_product() method to find each component of the product
	for (std::vector<float> a : m1) {
		for (int i=0; i<m2[0].size(); i++) {
			std::vector<float> b;
			for (int j=0; j<m2.size(); j++) {
				b.push_back(m2[j][i]);
	
			}

			ans += int_or_float(dot_product(a, b)) + " ";
		}

		ans += "\n";
	}

	return ans;
}

// swap two rows in a 2D vector
void Calculator::swap(std::vector<float>& a, std::vector<float>& b)
{
	a.swap(b);
}

// divide every element in a vector by val
void Calculator::divide_row(std::vector<float>& a, float val)
{
	for (int i=0; i < a.size(); i++) 
	{	
		//std::string quotient = int_or_float(a[i] / val);// improve rounding	
		//a[i] = std::stof(quotient);
		a[i] = a[i] / val;
	}
}

// subtract every element in a vector by the corresponding pivot row value multiplied by val
void Calculator::eliminate_row(std::vector<float>& a, std::vector<float>& pivot, float val) 
{
	for (int i=0; i<a.size(); i++)
	{
		//std::string diff = int_or_float(a[i] -  (pivot[i] * val)); 
		//a[i] = std::stof(diff);
		a[i] = a[i] - (pivot[i] * val);
	}
}

// produces an augmented matrix in reduced row echelon form (if possible) using Gaussian elimination
std::string Calculator::reduced_row_echelon(std::vector<std::vector<float>>& m)
{
	if (m.size() > m[0].size())
		return "";
		
	int solution = 1, count;


	for (int i=0; i < m.size(); i++) 
	{	
		// moving rows if the pivot element is 0
		if (m[i][i] == 0) 
		{
			// don't swap row if this is the last row
			if (i == m.size()-1)
				break;
			else 
				swap(m[i], m[i+1]);
		}
		
		// divide row to make pivot element 1	
		divide_row(m[i], m[i][i]);
	
		// makes corresponding elements in latter columns 0 
		for (int j=i+1; j<m.size(); j++) 
		{
			eliminate_row(m[j], m[i], m[j][i]);
		}
		
		// if not the first row, start eliminating the above the row
		if (i > 0) 
		{
			for (int j=i-1; j >= 0; j--) 
			{
				eliminate_row(m[j], m[i], m[j][i]);
			}
		}
	}

	for (int i=0; i < m.size(); i++) {
		count = 0;

		for (int j=0; j < m[0].size()-1; j++) 
		{	
			if (m[i][j] == 0)
				count++;
		}
		
		// if there is no solution (all three elements of a row are 0)
		if (count == m[0].size()-1)
		{
			solution = 0;
			return "No solution (RREF not possible)\n";
			break;
		}
	}

	if (solution == 1)
	{
		for (int i=1; i < m.size(); i++) 
		{
			for (int j=i-1; j >= 0; j--)
			{
				eliminate_row(m[j], m[i], m[j][i]);
			}
		}
	}
	


	// format answer
	std::string result = "";
	result += "\n";
	for (std::vector<float> a : m) 
	{
		print_vector(a);	
	}
	return result;


}

















