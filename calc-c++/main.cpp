#include <iostream> 
#include <vector>
#include <type_traits>
#include "Calculator.h"

std::ostream& operator << (std::ostream& output, std::vector<int> v)
{
	std::string output_line = "(" + v[0];
	for (int i=1; i < v.size(); i++)
	{
		output_line += ", " + v[i];
	}
	output_line += ")";
    
	output << output_line;
	return output;
};

void print_vector(std::vector<std::vector<float>> v){
	std::string output = "";
	for (int i=0; i<v.size(); i++) {
		for (int j=0; j<v[0].size(); j++) {
			output += std::to_string(v[i][j]) + " ";
	
		}	
		output += "\n";
	}
	std::cout << output;	
}

// handles vector inputs (when "-v" is used)
std::vector<std::vector<float>> vector_handler(int argc, char* argv[])
{
	std::string x;
	std::vector<float> v1, v2;
	int a; 
	// put each component of vector 1 into vector v1
	for (int i=4; i < argc; i++)
        {
		x = argv[i];
		// collecting each component until the indicator for vector 2 appears
		if (x.compare("-v2") != 0)
		{
			// type case integer and add component to vector
			v1.push_back(std::stof(x));
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

		v2.push_back(std::stof(x));
        }
    
	return {v1, v2};
}

// organises string into 2D vectors to represent matrices
std::vector<std::vector<std::vector<float>>> matrix_handler(int argc, char* argv[])
{
	std::string x;
	std::vector<std::vector<float>> m1, m2;
	bool is_m2 = false;

	for (int i=3; i<argc; i++)
	{
		x = argv[i];

		if (x.compare("-m2") != 0 && !(is_m2)) {
			std::vector<float> row;
			int j = i+1;

			std::string y = argv[j];

			while (y.compare("-n") != 0 && y.compare("-m2") != 0)
			{
				row.push_back(std::stof(y));
				j++;
				y = argv[j];

			}

			m1.push_back(row);
			i = j-1;

		} else 
		{	
			is_m2 = true;
			std::vector <float> row;
			int j = x.compare("-m2") != 0 ? i+1 : i+2;

			std::string y = argv[j];


			while (y.compare("-n") != 0 && j < argc) {
				row.push_back(std::stof(y));

				j++;
				y = j < argc ? argv[j] : y;

			}
			m2.push_back(row);
			i = j-1;
		}
	}
	
	return {m1, m2};
}
	
int main(int argc, char* argv[])
{
	Calculator calc;
    	
	int operation = std::stoi(argv[2]); // user-specified operation

	std::string x = argv[1];
    
	// checking for "-v", which indicates vector operation
	if (x.compare("-v") == 0)
	{
		std::vector<std::vector<float>> vectors = vector_handler(argc, argv);
        
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
		std::vector<std::vector<std::vector<float>>> matrices = matrix_handler(argc, argv);
		print_vector(matrices[0]);
		print_vector(matrices[1]);

//		switch(operation) 
//		{
//			case 0:
//				std::cout << calc.multiplication(matrices[0], matrices[1]) << std::endl;
//				break;

		//}

	}	
    
}
