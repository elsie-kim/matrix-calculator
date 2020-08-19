#include <iostream> 
#include <vector>
#include <type_traits>
#include "Calculator.h"

void print_vector(std::vector<Fraction> v){
	for (Fraction f : v) 
	{
		std::cout << f.print << " ";
	}
	std::cout << "\n";
	
}

void print_matrix(std::vector<std::vector<Fraction>> m)
{
	for (std::vector<Fraction> v : m)
	{
		print_vector(v);
	}
}

// handles vector inputs (when "-v" is used)
std::vector<std::vector<Fraction>> vector_handler(int argc, char* argv[])
{
	std::string x;
	std::vector<Fraction> v1, v2;
	int a; 
	// put each component of vector 1 into vector v1
	for (int i=4; i < argc; i++)
        {
		x = argv[i];
		
		// collecting each component until the indicator for vector 2 appears
		if (x.compare("-v2") != 0)
		{
			if (x.find("/") == std::string::npos)
			{
				Fraction fraction(std::stoi(x));
				v1.push_back(fraction);


			} else
			{
					int index = x.find("/");
					std::string num = x.substr(0, index);
					std::string denom = x.substr(index+1);

					Fraction fraction(std::stoi(num), std::stoi(denom));

					v1.push_back(fraction);
	
			}

		} else 
		{
			// a is the index of "-v2"
			a = i;
			break;
		}
        }
        
	// put each component of vector 2 into vector v2
	for (int i=a+1; i < argc; i++)
        {
		
		x = argv[i];
		if (x.find("/") == std::string::npos)		
		{
			Fraction fraction(std::stoi(x));
			v2.push_back(fraction);

		} else
		{
			int index = x.find("/");
			std::string num = x.substr(0, index);
			std::string denom = x.substr(index+1);

			Fraction fraction(std::stoi(num), std::stoi(denom));
			v2.push_back(fraction);
	
		}
        }
    
	return {v1, v2};
}

// organises string into 2D vectors to represent matrices
std::vector<std::vector<std::vector<Fraction>>> matrices_handler(int argc, char* argv[])
{
	std::string x;
	std::vector<std::vector<Fraction>> m1, m2;
	bool is_m2 = false;
	
	// start at first "-n"
	for (int i=4; i<argc; i++)
	{
		x = argv[i];
		
		if (x.compare("-m2") != 0 && !(is_m2)) {
			std::vector<Fraction> row;
			int j = i+1;

			std::string y = argv[j];

			while (y.compare("-n") != 0 && y.compare("-m2") != 0)
			{
				if (y.find("/") == std::string::npos)
				{
					Fraction fraction(std::stoi(y));
					row.push_back(fraction);
						
				} else 
				{
					int index = y.find("/");
					std::string num = y.substr(0, index);
					std::string denom = y.substr(index+1);

					Fraction fraction(std::stoi(num), std::stoi(denom));
					row.push_back(fraction);

				}
			
				j++;
				y = argv[j];
			}

			m1.push_back(row);
			i = j-1;

		} else 
		{	
			is_m2 = true;
			std::vector <Fraction> row;
			int j = x.compare("-m2") != 0 ? i+1 : i+2;

			std::string y = argv[j];


			while (y.compare("-n") != 0 && j < argc) 
			{
				if (y.find("/") == std::string::npos)	
				{
					Fraction fraction(std::stoi(y));
					row.push_back(fraction);

				} else
				{
					int index = y.find("/");
					std::string num = y.substr(0, index);
					std::string denom = y.substr(index+1);

					Fraction fraction(std::stoi(num), std::stoi(denom));
					row.push_back(fraction);
					
				}

				j++;
				y = j < argc ? argv[j] : y;

			}
			m2.push_back(row);
			i = j-1;
		}
	}
	
	return {m1, m2};
}

std::vector<std::vector<Fraction>> matrix_handler(int argc, char* argv[])
{
	std::string x = "";
	std::vector<std::vector<Fraction>> matrix;

	for (int i=3; i<argc; i++)
	{
		x = argv[i];

		if (x.compare("-n") == 0) 
		{
			int j = i+1;
			std::string y = argv[j];
			std::vector<Fraction> row;

			while (y.compare("-n") != 0 && j < argc) {
				if (y.find("/") == std::string::npos) 
				{
					Fraction fraction(std::stoi(y));
					row.push_back(fraction);

				} else
				{
					int index = y.find("/");
					std::string num = y.substr(0, index);
					std::string denom = y.substr(index+1);

					Fraction fraction(std::stoi(num), std::stoi(denom));
					row.push_back(fraction);
				}
				j++;
				y = j < argc ? argv[j] : "";
			
			}

			matrix.push_back(row);
			i = j-1; 
			
		}	
	}

	return matrix;
}
	
int main(int argc, char* argv[])
{
	Calculator calc;
    	
	int operation = std::stoi(argv[2]); // user-specified operation

	std::string x = argv[1];
    
	// checking for "-v", which indicates vector operation
	if (x.compare("-v") == 0)
	{
		std::vector<std::vector<Fraction>> vectors = vector_handler(argc, argv);
        	switch(operation) {
			case 0:
                		std::cout << calc.dot_product(vectors[0], vectors[1]) << std::endl;
				break;

			case 1:
				std::cout << calc.cross_product(vectors[0], vectors[1]) << std::endl;
				break;
        	}
        
    	} else // "-m" for matrix
	{
		
		std::vector<std::vector<std::vector<Fraction>>> matrices;
		std::vector<std::vector<Fraction>> matrix;

		switch(operation) 
		{
			case 0:
				matrices = matrices_handler(argc, argv);
				print_matrix(matrices[0]);
				//std::cout << calc.multiplication(matrices[0], matrices[1]) << std::endl;
				break;
			case 1:
				matrix = matrix_handler(argc, argv);
				print_matrix(matrix);
				//std::cout << calc.augmented_reduced_row_echelon(matrix);
				break;
			case 2:
				matrices = matrices_handler(argc, argv);
				//std::cout << calc.addition(matrices[0], matrices[1]);
				break;
			case 3:
				matrices = matrices_handler(argc, argv);
				//std::cout << calc.subtraction(matrices[0], matrices[1]);
				break;	

		}

	}	
    
}
