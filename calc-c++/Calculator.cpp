#include "Calculator.h"

// dot product of two vectors
std::string Calculator::dot_product(std::vector<Fraction>& v1, std::vector<Fraction>& v2)

{
	Fraction sum(0);
    
	for (int i=0; i < v1.size(); i++)
	{
		Fraction f = v1[i].multiply_val(v2[i]);
		sum.add(f);
	}
   
	return sum.print;
}

// cross product of two vectors --- only supports 3D vectors, might add 7D later
std::string Calculator::cross_product(std::vector<Fraction>&v1, std::vector<Fraction>& v2) 
{
	Fraction a_1 = v1[1].multiply_val(v2[2]);
	Fraction a_2 = v1[2].multiply_val(v2[1]);
	a_1.subtract(a_2);

	Fraction b_1 = v1[2].multiply_val(v2[0]);
	Fraction b_2 = v1[0].multiply_val(v2[2]);
	b_1.subtract(b_2);

	Fraction c_1 = v1[0].multiply_val(v2[1]);
	Fraction c_2 = v1[1].multiply_val(v2[0]);
	c_1.subtract(c_2);

	std::string ans = "(" + a_1.print + ", " + b_1.print + ", " + c_1.print + ")";
	
	return ans;
}

void Calculator::print_vector(std::vector<Fraction> v)
{
	//for (Fraction a : v) {
	//	std::cout << a << "\t";
	//}
	//std::cout << std::endl;

}

// multiplies two matrices
std::string Calculator::multiplication(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2) 
{
	std::string ans = "\n";

	// use the dot_product() method to find each component of the product
	for (std::vector<Fraction> a : m1) {
		for (int i=0; i<m2[0].size(); i++) {
			std::vector<Fraction> b;
			for (int j=0; j<m2.size(); j++) {
				b.push_back(m2[j][i]);
	
			}
			
			ans += dot_product(a, b) + " ";
		}

		ans += "\n";
	}

	return ans;

}

// swap two rows in a 2D vector
void Calculator::swap(std::vector<Fraction>& a, std::vector<Fraction>& b)
{
	a.swap(b);
}

// divide every element in a vector by val
void Calculator::divide_row(std::vector<Fraction>& a, Fraction val)
{	
	if (val.print != "0") {
		for (int i=0; i < a.size(); i++) 
		{	
			a[i].divide(val);
		}	
	}
}

// subtract every element in a vector by the corresponding pivot row value multiplied by val
void Calculator::eliminate_row(std::vector<Fraction>& a, std::vector<Fraction>& pivot, Fraction val) 
{
	for (int i=0; i<a.size(); i++)
	{
		Fraction b = pivot[i].multiply_val(val);
		a[i].subtract(b);
	}
}

std::string format_matrix(std::vector<std::vector<Fraction>>& m)
{
	// format answer
	std::string result = "";
	for (std::vector<Fraction> a : m) 
	{
		for (Fraction b  : a)
		{
			std::cout << b.print << " ";
		}
		
		std::cout << std::endl;
	}

	return result;
}

int check_bottom_row(std::vector<std::vector<Fraction>>& m)
{
	int rows = m.size()-1;
	int count = 0;

	for (int i=0; i < m[0].size(); i++)
	{
		if (m[rows][i].print == "0")
			count++;
	}

	if (count == m[0].size()) 
		return 1; // all zeros
	else if (count == m[0].size()-1 && m[rows][m[0].size()-1].print != "0")
		return 2; // all but right-most element are 0
	else
		return 0; // has more than one non-zero element and the last element is not 0
}

// produces an augmented matrix in reduced row echelon form (if possible) using Gaussian elimination
std::string Calculator::augmented_reduced_row_echelon(std::vector<std::vector<Fraction>>& m)
{
	std::cout << "hello\n";
	if (m.size() > m[0].size())
	{
		return "Check dimensions";
	}

	int count;

	for (int i=0; i < m.size(); i++)
	{
		// moving rows if the pivot element is 0
		if (m[i][i].print == "0")
		{
			// don't swap rows if this is the last row
			if (i == m.size()-1) 
			{
				int check = check_bottom_row(m);
				if (check == 1) return format_matrix(m);
				else if (check == 2) return "Inconsistent system";
				else break;

			} else swap(m[i], m[i+1]);

			std::cout << "swapped or last row\n" << format_matrix(m) << std::endl;
		}

		// divide row to make pivot element 1
		divide_row(m[i], m[i][i]);
		
		// makes corresponding elements in latter columns 0
		std::cout << "divided\n" << format_matrix(m) << std::endl;

		for (int j=i+1; j < m.size(); j++) 
		{
			eliminate_row(m[j], m[i], m[j][i]);

			std::cout << "1st elim\n" << format_matrix(m) << std::endl;
		}

		if (i > 0)
		{
			for (int j=i-1; j >= 0; j--)
			{
				eliminate_row(m[j], m[i], m[j][i]);

				std::cout << "2nd elim\n" << format_matrix(m) << std::endl;
			}
		}

	}


	return format_matrix(m);
}

// adds two matrices
std::string Calculator::addition(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2) 
{
	std::vector<std::vector<Fraction>> result;

	for (int i=0; i < m1.size(); i++)
	{
		std::vector<Fraction> v;

		for (int j=0; j < m1[0].size(); j++)
		{
			m1[i][j].add(m2[i][j]);
			v.push_back(m1[i][j]);
		}
		result.push_back(v);
	}

	return format_matrix(result);
}

// subtracts the second matrix from the first
std::string Calculator::subtraction(std::vector<std::vector<Fraction>>& m1, std::vector<std::vector<Fraction>>& m2) 
{
	std::vector<std::vector<Fraction>> result;

	for (int i=0; i < m1.size(); i++)
	{
		std::vector<Fraction> v;

		for (int j=0; j < m1[0].size(); j++)
		{
			m1[i][j].subtract(m2[i][j]);
			v.push_back(m1[i][j]);
		}
		result.push_back(v);
	}

	return format_matrix(result);
}
















