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
	std::string ans = "";
	std::vector<Fraction> b;
	
	// use the dot_product() method to find each component of the product
	for (std::vector<Fraction> a : m1) {
		for (int i=0; i<m2[0].size(); i++) {
			b.clear();	
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

// formats matrix vector to a printable form
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

// checks bottom row for zeros
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

// finds the next non-zero element in a row
int Calculator::find_next_column(std::vector<std::vector<Fraction>>& m, int current)
{
	for (int i=0; i < m[0].size(); i++)
	{
		if (m[current][i].print != "0")
			return i;
	}
	return -1;
}

// moves an all-zero or mostly-zero row to the bottom and shifts the other rows up
void Calculator::move_to_back(std::vector<std::vector<Fraction>>& m, int row)
{
	std::vector<Fraction> temp = m[row];
	
	for (int i=row; i < m.size()-1; i++)
	{
		m[i] = m[i+1];
	}

	m[m.size()-1] = temp;
}

// swaps rows to keep them in order
void Calculator::move_row(std::vector<std::vector<Fraction>>& m, int pivot)
{
	int col;
	// Move the next left-most non-zero element to current row
	for (int i=0; i < m.size(); i++)
	{	
		col = find_next_column(m, i);
		if (col < pivot && col != -1)
		{
			pivot = find_next_column(m, i);

			if (i > 0)
				swap(m[0], m[i]);

		} else if (col == -1) {
			if (i != m.size()-1)
				move_to_back(m, i);	
		} 
	}

}

// produces an augmented matrix in reduced row echelon form (if possible) using Gaussian elimination
// * returns result as a string
std::string Calculator::augmented_reduced_row_echelon(std::vector<std::vector<Fraction>>& m)
{
	int pivot = m[0].size()-2;

	int col;
	
	
	for (int i=0; i < m.size(); i++)
	{
		move_row(m, pivot);
		pivot = find_next_column(m, i);

		if (pivot != -1)
		{
			divide_row(m[i], m[i][pivot]);
		} else { // if the row is all 0s
			return format_matrix(m);
		}
		
		// eliminate rows below
		for (int j=i+1; j < m.size(); j++)
		{
			eliminate_row(m[j], m[i], m[j][pivot]);
		}
		
		// eliminate rows above
		if (i > 0)
		{
			for (int j=i-1; j >= 0; j--)
			{
				eliminate_row(m[j], m[i], m[j][pivot]);
			}
		}
		std::cout << format_matrix(m) << "\n";

	}

	return format_matrix(m);
}

// produces an augmented matrix in reduced row echelon form (if possible) using Gaussian elimination
// * returns result as a vector
std::vector<std::vector<Fraction>> Calculator::augmented_reduced_row_echelon_solve(std::vector<std::vector<Fraction>>& m)
{
	int pivot = m[0].size()-2;

	int col;
	
	
	for (int i=0; i < m.size(); i++)
	{
		move_row(m, pivot);
		pivot = find_next_column(m, i);

		if (pivot != -1)
		{
			divide_row(m[i], m[i][pivot]);
		} else { // if the row is all 0s
			return m;
		}
		
		// eliminate rows below
		for (int j=i+1; j < m.size(); j++)
		{
			eliminate_row(m[j], m[i], m[j][pivot]);
		}
		
		// eliminate rows above
		if (i > 0)
		{
			for (int j=i-1; j >= 0; j--)
			{
				eliminate_row(m[j], m[i], m[j][pivot]);
			}
		}
		std::cout << format_matrix(m) << "\n";

	}

	return m;
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
